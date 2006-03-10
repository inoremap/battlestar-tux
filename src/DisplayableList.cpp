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
	bool collision = false;
	float point[2] = { 0, 0 };
	
	// If object is a fighter, it may be protected by a shield.
	// Collisions will occur on the shield, not the fighter.
	if( object->getType() == FIGHTER ) {
		if( ((Fighter*) object)->getShield() && ((Fighter*) object)->getShield()->getShields() )
			object = ((Fighter*) object)->getShield();
	}

	float* sizeA = object->getSize();
	float* posA = object->getPos();
	float rightA = posA[0] + sizeA[0]/2;
	float leftA = posA[0] - sizeA[0]/2;
	float topA = posA[1] + sizeA[1]/2;
	float bottomA = posA[1] - sizeA[1]/2;

	while( cur && object ) {
		next = (Displayable*) cur->getNext();

		// If cur is a fighter, it may be protected by a shield.
		// Collisions will occur on the shield, not the fighter.
		if( cur->getType() == FIGHTER ) {
			if( ((Fighter*) cur)->getShield() && ((Fighter*) cur)->getShield()->getShields() )
				cur = ((Fighter*) cur)->getShield();
		}

		// Do a 'rough estimate' rectangular collision detection.
		// Determine if the objects' bounding boxes intersect.
		float* sizeB = cur->getSize();
		float* posB = cur->getPos();
		float rightB = posB[0] + sizeB[0]/2;
		float leftB = posB[0] - sizeB[0]/2;
		float topB = posB[1] + sizeB[1]/2;
		float bottomB = posB[1] - sizeB[1]/2;

		// Bounding boxes intersect - this doesn't guarantee collision.
		if( rightB > leftA && rightA > leftB && topB > bottomA && topA > bottomB ) {
			collision = false;

			// Circular collision detection.
			if( cur->getCircular() && object->getCircular() ) {
				float mx = posA[0] - posB[0];
				float my = posA[1] - posB[1];
				float dist = sqrtf( mx*mx + my*my );
				float minDist = (sizeA[0] + sizeB[0]) / 2;

				// Collision detected.
				if( dist < minDist ) {
					// Calculate collision point.
					// http://astronomy.swin.edu.au/~pbourke/geometry/2circle/
					float* p0 = posA;
					float* p1 = posB;
					float r0 = sizeA[0] / 2;
					float r1 = sizeB[0] / 2;
					float a = (r0*r0 - r1*r1 + dist*dist) / (2 * dist);
					float h = sqrtf( r0*r0 - a*a );
					float p2[2] = { 0, 0 };

					// Location of first collision.
					float p3[2] = { 0, 0 };
					// Location of second collision.
					float p4[2] = { 0, 0 };

					p2[0] = p0[0] + a * (p1[0] - p0[0]) / dist;
					p2[1] = p0[1] + a * (p1[1] - p0[1]) / dist;
					p3[0] = p2[0] + h * (p1[1] - p0[1]) / dist;
					p4[0] = p2[0] - h * (p1[1] - p0[1]) / dist;
					p3[1] = p2[1] + h * (p1[0] - p0[0]) / dist;
					p4[1] = p2[1] - h * (p1[0] - p0[0]) / dist;

					// Count collision as the midpoint between the two collisions.
					// If the circles are perfectly next to each other, the two
					// collision points will be identical.
					point[0] = (p3[0] + p4[0]) / 2;
					point[1] = (p3[1] + p4[1]) / 2;

					collision = true;
				}
			}

			// Polygon collision detection.
			else {
				collision = true;
			}

			// Handle collision.
			if( collision ) {
				if( object->getType() & AMMO && (cur->getType() & FIGHTER || cur->getType() & SHIELD) )
					ResolveCollision( cur, object, point );
				else
					ResolveCollision( object, cur, point );
			}
		}

		cur = next;
	}
}


void DisplayableList::ResolveCollision( Displayable* &a, Displayable* &b, float* p ) {
	// An ammo and an airframe are colliding.
	if( a->getType() & FIGHTER && b->getType() & AMMO ) {
		// We know that a is the fighter and b is the ammo.

		((Fighter*) a)->damage( ((FighterAmmo*) b)->getDamage(), p );

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

	// An ammo and a shield are colliding.
	else if( a->getType() & SHIELD && b->getType() & AMMO ) {
		// We know that a is the shield and b is the ammo.

		// Penetration weapons do more damage.
		float remainder = ((Shield*) a)->damage(
			((FighterAmmo*) b)->getDamage() *
			( ((FighterAmmo*) b)->getPenetration() + 1 ),
			p
		);

		if( remainder == 0 ) {
			// The ammo was blocked by the shield.
			if( b->getType() == HEROS_AMMO ) {
				game->getHeroAmmoList()->remObject( b );
			}
			else {
				game->getEnemyAmmoList()->remObject( b );
			}

			b = 0;
		}
	}

	// Two ammos are colliding
	else if( a->getType() & AMMO && b->getType() & AMMO ) {
		if( game->getConfig()->getDebug() )
			printf( "Ammo collision.\n" );
	}

	// Two shields are colliding.
	else if( a->getType() & SHIELD && b->getType() & SHIELD ) {
		if( game->getConfig()->getDebug() )
			printf( "Aircraft shield collision.\n" );
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
