/* DisplayableList.cpp
 *
 * Copyright 2005-2006 Eliot Eshelman
 * eliot@6by9.net
 *
 *
 *  This file is part of Battlestar Tux.
 *
 *  Battlestar Tux is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  Battlestar Tux is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Battlestar Tux; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#include <math.h>
#include <stdio.h>

#include "Displayable.h"
#include "DisplayableList.h"
#include "EnemyFighterList.h"
#include "FighterAmmo.h"
#include "Fighter/Fighter.h"

DisplayableList::DisplayableList( Game* g ) {
	rootObj = 0;
	game = g;
}


DisplayableList::~DisplayableList() {}


void DisplayableList::Update() {
	Displayable* cur = rootObj;

	while( cur ) {
		cur->Update();
		cur = (Displayable*) cur->getNext();
	}
}


void DisplayableList::DrawObjects() {
	Displayable* cur = rootObj;
	Displayable* next = 0;

	while( cur ) {
		next = (Displayable*) cur->getNext();

		cur->Draw();
		cur = next;
	}
}


void DisplayableList::CheckCollisions( DisplayableList* objectList ) {
	Displayable* cur = objectList->getRoot();
	Displayable* next = 0;

	while( cur ) {
		next = (Displayable*) cur->getNext();

		CheckCollisions( cur );
		cur = next;
	}
}


void DisplayableList::CheckCollisions( Displayable* object ) {
	Displayable* cur = rootObj;
	Displayable* next = 0;
	bool objColl = false;

	float* sizeA = object->getSize();
	float* posA = object->getPos();
	float rightA = posA[0] + sizeA[0]/2;
	float leftA = posA[0] - sizeA[0]/2;
	float topA = posA[1] + sizeA[1]/2;
	float bottomA = posA[1] - sizeA[1]/2;

	while( cur ) {
		next = (Displayable*) cur->getNext();

		// Do a 'rough estimate' collision detection.
		// Determine if the objects bounding boxes intersect.
		float* sizeB = cur->getSize();
		float* posB = cur->getPos();
		float rightB = posB[0] + sizeB[0]/2;
		float leftB = posB[0] - sizeB[0]/2;
		float topB = posB[1] + sizeB[1]/2;
		float bottomB = posB[1] - sizeB[1]/2;

		if( rightB > leftA && rightA > leftB && topB > bottomA && topA > bottomB ) {
			// Accurate collision detection.
			float mx = posA[0] - posB[0];
			float my = posA[1] - posB[1];
			float dist = sqrtf( mx*mx + my*my );
			float minDist = (sizeA[0] + sizeA[1] + sizeB[0] + sizeB[1]) / 4;

			// Collision detected.
			if( dist < minDist ) {
				ResolveCollision( object, cur );
			}
		}

		cur = next;
	}
}


void DisplayableList::ResolveCollision( Displayable* a, Displayable* b ) {
	// Two ammos are colliding
	if( a->getType() & AMMO && b->getType() & AMMO ) {
		printf( "Ammo collision.\n" );
	}

	// An ammo and an airframe are colliding.
	else if( a->getType() & AMMO || b->getType() & AMMO ) {
		FighterAmmo* ammo;
		Fighter* airframe;

		if( a->getType() & AMMO ) {
			ammo = (FighterAmmo*) a;
			airframe = (Fighter*) b;
		}
		else {
			ammo = (FighterAmmo*) b;
			airframe = (Fighter*) a;
		}

		airframe->damage( ammo->getDamage() );

		// Does ammo penetrate airframe?
		if( ammo->getPenetration() > 0 ) {
			// Let ammo pass - some ships should probably stop it.
		}
		else {
			if( ammo->getType() & HEROS_AMMO ) {
				game->getHeroAmmoList()->remObject( ammo );
				ammo = 0;
			}
			else {
				game->getEnemyAmmoList()->remObject( ammo );
				ammo = 0;
			}
		}

		// Is the airframe dead?
		if( airframe->getHealth() <= 0 ) {
			if( airframe->getAlignment() == ENEMY_FIGHTER ) {
				game->getEnemyFighterList()->remObject( airframe );
				airframe = 0;
			}
			else {
				// Game over!!!
				printf( "Game over!!!!  Player is dead.\n" );
			}
		}
	}

	// Two airframes are colliding.
	else {
		printf( "Aircraft collision.\n" );
	}
}


void DisplayableList::CullObjects( objectCulling cull ) {
	float* bounds = game->getBounds();
	Displayable* cur = rootObj;
	Displayable* rem = 0;

	while( cur ) {
		float* pos = cur->getPos();
		float* size = cur->getSize();

		// Top of screen.
		if( cull & CULL_TOP && (pos[1] - size[1] / 2) > bounds[1] ) {
			rem = cur;
	 		cur = (Displayable*) cur->getNext();

			remObject( rem );
			continue;
		}

		// Bottom of screen.
		if( cull & CULL_BOTTOM && (pos[1] + size[1] / 2) < (0.0 - bounds[1]) ) {
			rem = cur;
	 		cur = (Displayable*) cur->getNext();

			remObject( rem );
			continue;
		}

		// Left of screen.
		if( cull & CULL_LEFT && (pos[0] + size[0] / 2) < (0.0 - bounds[0]) ) {
			rem = cur;
	 		cur = (Displayable*) cur->getNext();

			remObject( rem );
			continue;
		}

		// Right of screen.
		if( cull & CULL_RIGHT && (pos[0] - size[0] / 2) > bounds[0] ) {
			rem = cur;
	 		cur = (Displayable*) cur->getNext();

			remObject( rem );
			continue;
		}

		cur = (Displayable*) cur->getNext();
	}
}


void DisplayableList::addObject( Displayable* obj ) {
	Displayable* first = rootObj;

	if( !first )
		rootObj = obj;
	else {
		first->setPrev( (Displayable*) obj );
		obj->setNext( (Displayable*) first );
		rootObj = obj;
	}
}


void DisplayableList::remObject( Displayable* obj ) {
	// obj is rootObj
	if( !obj->getPrev() )
		rootObj = (Displayable*) obj->getNext();
	else
		obj->getPrev()->setNext( (Displayable*) obj->getNext() );

	if( obj->getNext() )
		obj->getNext()->setPrev( (Displayable*) obj->getPrev() );

	delete obj;
}


Displayable* DisplayableList::getRoot() { return rootObj; }


void DisplayableList::printList() {
	Displayable* cur = rootObj;
	int count = 0;

	printf( "---List------------------\n" );

	while( cur ) {
		if( count < 10 ) {
			printf( " Object: 0x%x", cur );
			printf( "\tx: %12f\ty: %12f\n", cur->getPos()[0], cur->getPos()[1] );
		}

		count++;
		cur = (Displayable*) cur->getNext();
	}

	if( count >= 10 )
		printf( " more...%i total\n", count );

	printf( "---List------------------\n\n" );
}
