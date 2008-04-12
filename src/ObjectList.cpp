/* ObjectList.cpp
 *
 * Copyright 2005-2008 Eliot Eshelman
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
#include "Object.h"
#include "ObjectList.h"

ObjectList::ObjectList() {
	game = Game::getGame();
}


ObjectList::~ObjectList() {}


void ObjectList::UpdateObjects() {
	int speed = game->getGameSpeed();


	Object* cur = (Object*) rootObj;

	while( cur ) {
		cur->Update( speed );
		cur = (Object*) cur->getNext();
	}
}


void ObjectList::DrawObjects() {
	Object* cur = (Object*) rootObj;

	while( cur ) {
		cur->Draw();
		cur = (Object*) cur->getNext();
	}
}


void ObjectList::CheckCollisions( ObjectList* objectList ) {
	Object* cur = (Object*) objectList->getRoot();
	Object* next = 0;

	while( cur ) {
		next = (Object*) cur->getNext();

		CheckCollisions( cur );
		cur = next;
	}
}


void ObjectList::CheckCollisions( Object* object ) {
	Object* cur = (Object*) getRoot();
	Object* next = 0;

	while( cur ) {
		next = (Object*) cur->getNext();

		CheckCollisions( cur, object );
		cur = next;
	}
}


void ObjectList::CheckCollisions( ObjectList* objectList, Object* object ) {
	Object* cur = (Object*) objectList->getRoot();
	Object* next = 0;

	while( cur ) {
		next = (Object*) cur->getNext();

		CheckCollisions( cur, object );
		cur = next;
	}
}


void ObjectList::CheckCollisions( Object* object1, Object* object2 ) {

	if( DetermineCollision(object1, object2) ) {
		// An object can consist of multiple sub-objects.  If that is the case,
		// we need to check each of them - not just the "container" object.
		if( object1->hasComponents() )
			CheckCollisions( object1->getComponents(), object2 );
		// If both objects have components, the first is broken down here and the
		// second will be broken down in the recursive call.
		else if( object2->hasComponents() )
			CheckCollisions( object2->getComponents(), object1 );

		std::cout << "Collision..." << std::endl;
	}
}


bool ObjectList::DetermineCollision( Object* object1, Object* object2 ) {
	// We can quickly determine if the bounding spheres of the objects intersect.
	// Adapted from code written by Oleg Dopertchouk:
	// http://www.gamedev.net/reference/programming/features/boundingsphere/

	// Relative velocity
	vec3 dv = object2->getVel() - object1->getVel();

	// Relative position
	vec3 dp = object2->getPos() - object1->getPos();

	// Minimal distance squared
	float r = object1->getSize() + object2->getSize();

	// dP^2-r^2
	float pp = dp[0] * dp[0] + dp[1] * dp[1] + dp[2] * dp[2] - r * r;

	// (1) Check if the spheres are already intersecting
	if ( pp < 0 )
		return true;

	// dP*dV
	float pv = dp[0] * dv[0] + dp[1] * dv[1] + dp[2] * dv[2];

	// (2) Check if the spheres are moving away from each other
	if ( pv >= 0 )
		return false;

	// dV^2
	float vv = dv[0] * dv[0] + dv[1] * dv[1] + dv[2] * dv[2];

	// (3) Check if the spheres can intersect within 1 frame
	if ( (pv + vv) <= 0 && (vv + 2 * pv + pp) >= 0 )
		return false;

	// tmin = -dP*dV/dV*2 
	// The time when the distance between the spheres is minimal
	float tmin = -pv / vv;

	// Discriminant/(4*dV^2) = -(dp^2-r^2+dP*dV*tmin)
	return ( pp + pv * tmin > 0 );
}


void ObjectList::ResolveCollision( Object* &a, Object* &b, float* p ) {
}

