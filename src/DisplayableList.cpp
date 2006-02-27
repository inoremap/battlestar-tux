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

#include "Config.h"
#include "Displayable.h"
#include "DisplayableList.h"
#include "EnemyFighterList.h"
#include "FighterAmmo.h"
#include "Fighter/Fighter.h"

DisplayableList::DisplayableList( Game* g ) {
	game = g;
}


DisplayableList::~DisplayableList() {}


void DisplayableList::UpdateObjects() {
	Displayable* cur = (Displayable*) rootObj;

	while( cur ) {
		cur->Update();
		cur = (Displayable*) cur->getNext();
	}
}


void DisplayableList::DrawObjects() {
	Displayable* cur = (Displayable*) rootObj;
	Displayable* next = 0;

	while( cur ) {
		next = (Displayable*) cur->getNext();
		cur->Draw();
		cur = next;
	}
}


void DisplayableList::CheckCollisions( DisplayableList* objectList ) {
	Displayable* cur = (Displayable*) objectList->getRoot();
	Displayable* next = 0;

	while( cur ) {
		next = (Displayable*) cur->getNext();

		CheckCollisions( cur );
		cur = next;
	}
}


void DisplayableList::CheckCollisions( Displayable* object ) {
	Displayable* cur = (Displayable*) rootObj;
	Displayable* next = 0;
	bool objColl = false;

	float* sizeA = object->getSize();
	float* posA = object->getPos();
	float rightA = posA[0] + sizeA[0]/2;
	float leftA = posA[0] - sizeA[0]/2;
	float topA = posA[1] + sizeA[1]/2;
	float bottomA = posA[1] - sizeA[1]/2;

	while( cur && object ) {
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
				if( object->getType() & AMMO && cur->getType() & FIGHTER )
					ResolveCollision( cur, object );
				else
					ResolveCollision( object, cur );
			}
		}

		cur = next;
	}
}


void DisplayableList::ResolveCollision( Displayable* &a, Displayable* &b ) {
	// An ammo and an airframe are colliding.
	if( a->getType() & FIGHTER && b->getType() & AMMO ) {
		// We know that a is the fighter and b is the ammo.

		((Fighter*) a)->damage( ((FighterAmmo*) b)->getDamage() );

		// Does ammo penetrate airframe?
		if( ((FighterAmmo*) b)->getPenetration() > 0 ) {
			// Let ammo pass - some ships should probably stop it.
		}
		else {
			if( b->getType() == HEROS_AMMO ) {
				game->getHeroAmmoList()->remObject( b );
			}
			else {
				game->getEnemyAmmoList()->remObject( b );
			}

			b = 0;
		}

		// Is the airframe dead?
		if( ((Fighter*) a)->getHealth() <= 0 ) {
			if( ((Fighter*) a)->getAlignment() == ENEMY_FIGHTER ) {
				game->getEnemyFighterList()->remObject( a );
				a = 0;
			}
			else {
				// Game over!!!
				if( game->getConfig()->getDebug() )
					printf( "Game over!!!!  Player is dead.\n" );
			}
		}
	}

	// Two ammos are colliding
	else if( a->getType() & AMMO && b->getType() & AMMO ) {
		if( game->getConfig()->getDebug() )
			printf( "Ammo collision.\n" );
	}

	// Two airframes are colliding.
	else {
		if( game->getConfig()->getDebug() )
			printf( "Aircraft collision.\n" );
	}
}


void DisplayableList::CullObjects( objectCulling cull ) {
	float* bounds = game->getBounds();
	Displayable* cur = (Displayable*) rootObj;
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
