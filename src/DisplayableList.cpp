/* DisplayableList.cpp
 *
 * Copyright 2005-2006 Eliot Eshelman
 * battlestartux@6by9.net
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
#include <iostream>

#include "Config.h"
#include "Displayable.h"
#include "DisplayableList.h"
#include "EnemyFighterList.h"
#include "ExplosionList.h"
#include "Fighter.h"
#include "FighterAmmo.h"

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

			// Polygon/Circle collision detection.
			else if( cur->getCircular() || object->getCircular() ) {
				Displayable* circle;
				Displayable* polygon;

				// Determine which object is a circle and which is a polygon.
				if( cur->getCircular() ) {
					circle = cur;
					polygon = object;
				}
				else {
					circle = object;
					polygon = cur;
				}

				// Check for a collision.
				// We might need to first ensure the circle isn't inside the polygon.
				// http://astronomy.swin.edu.au/~pbourke/geometry/sphereline/
				int numSegments = polygon->getNumPolygonPoints();
				float** constPoints = polygon->getPolygon();
				float** polygonPoints = new float*[numSegments];
				float* polygonPos = polygon->getPos();
				float rotation = polygon->getRot() * (M_PI / 180);

				float cosRot = cosf( rotation );
				float sinRot = sinf( rotation );

				// Calculate position and rotation of polygon.
				for( int i=0; i < numSegments; i++ ) {
					polygonPoints[i] = new float[2];
					polygonPoints[i][0] = polygonPos[0] +
					                      cosRot * constPoints[i][0] + sinRot * constPoints[i][1];
					polygonPoints[i][1] = polygonPos[1] -
					                      sinRot * constPoints[i][0] + cosRot * constPoints[i][1];
				}

				float* p1 = 0;
				float* p2 = 0;
				float* p3 = circle->getPos();
				float r = circle->getSize()[0] / 2;
				for( int i=0; i < numSegments; i++ ) {
					// Retrieve the line to collide.
					if( i == (numSegments - 1) ) {
						p1 = polygonPoints[i];
						p2 = polygonPoints[0];
					}
					else {
						p1 = polygonPoints[i];
						p2 = polygonPoints[i+1];
					}

					float a = (p2[0] - p1[0]) * (p2[0] - p1[0]) + (p2[1] - p1[1]) * (p2[1] - p1[1]);
					float b = 2 * ( (p2[0] - p1[0]) * (p1[0] - p3[0]) + (p2[1] - p1[1]) * (p1[1] - p3[1]) );
					float c =	p3[0]*p3[0] + p3[1]*p3[1] + p1[0]*p1[0] + p1[1]*p1[1] -
								2 * (p3[0] * p1[0] + p3[1] * p1[1] ) - r*r;
					float uroot = b * b - 4 * a * c;
					float u1 = 0;
					float u2 = 0;

					// No collision
					if( uroot < 0 )
						continue;
					else if( uroot == 0 )
						u1 = u2 = -b / (2 * a);
					else {
						u1 = (-b + sqrtf( uroot )) / (2 * a);
						u2 = (-b - sqrtf( uroot )) / (2 * a);
					}

					// Location of first collision.
					float coll1[2] = { 0, 0 };
					// Location of second collision.
					float coll2[2] = { 0, 0 };

					coll1[0] = p1[0] + u1 * (p2[0] - p1[0]);
					coll1[1] = p1[1] + u1 * (p2[1] - p1[1]);
					coll2[0] = p1[0] + u2 * (p2[0] - p1[0]);
					coll2[1] = p1[1] + u2 * (p2[1] - p1[1]);

					// The two collision points are along the line through p1 and p2.
					// The collisions might not be in the line segment from p1 to p2, though.
					//
					// If the circle and line are perfectly next to each other, the two
					// collision points will be identical.
					//
					bool valid1 = false;
					bool valid2 = false;
					// Check first collision.
					if( p1[0] <= coll1[0] && coll1[0] <= p2[0] ||
					    p2[0] <= coll1[0] && coll1[0] <= p1[0] ) {
						if( p1[1] <= coll1[1] && coll1[1] <= p2[1] ||
						    p2[1] <= coll1[1] && coll1[1] <= p1[1] )
							valid1 = true;
					}
					// Check second collision.
					if( p1[0] <= coll2[0] && coll2[0] <= p2[0] ||
					    p2[0] <= coll2[0] && coll2[0] <= p1[0] ) {
						if( p1[1] <= coll2[1] && coll2[1] <= p2[1] ||
						    p2[1] <= coll2[1] && coll2[1] <= p1[1] )
							valid2 = true;
					}

					// Both collisions are on segment.
					if( valid1 && valid2 ) {
					    	point[0] = ( coll1[0] + coll2[0] ) / 2;
					    	point[1] = ( coll1[1] + coll2[1] ) / 2;
					}
					// First collision is on segment.
					else if( valid1 ) {
						point[0] = coll1[0];
						point[1] = coll1[1];
					}
					// Second collision is on segment
					else if( valid2 ) {
						point[0] = coll2[0];
						point[1] = coll2[1];
					}
					// Neither collision is on segment!
					// Execution reaches here when the bounding boxes
					// are colliding but the line segment and circle aren't.
					else
						continue;

					collision = true;
					break;
				}

				for( int i=0; i < numSegments; i++ )
					delete[] polygonPoints[i];
				delete[] polygonPoints;
			}

			// Polygon collision detection.
			else {
				collision = false;
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
			game->getExplosionList()->AddExplosion( p );

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
				game->getExplosionList()->AddExplosion( p );
				game->getEnemyFighterList()->remObject( a );
				a = 0;
			}
			else {
				// Game over!!!
				if( game->getConfig()->getDebug() )
					std::cout << "Game over!!!!  Player is dead.\n";
			}
		}
	}

	// An ammo and a shield are colliding.
	else if( a->getType() & SHIELD && b->getType() & AMMO ) {
		// We know that a is the shield and b is the ammo.
		game->getExplosionList()->AddExplosion( p );

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
			std::cout << "Ammo collision.\n";
	}

	// Two shields are colliding.
	else if( a->getType() & SHIELD && b->getType() & SHIELD ) {
		if( game->getConfig()->getDebug() )
			std::cout << "Aircraft shield collision.\n";
	}

	// Two airframes are colliding.
	else {
		if( game->getConfig()->getDebug() )
			std::cout << "Aircraft collision.\n";
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
