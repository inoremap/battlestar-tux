/* Object.cpp
 *
 * Copyright 2005-2007 Eliot Eshelman
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


#include "Object.h"


Object::Object( ObjectType t ) {
	pos = vec3();
	vel = vec3();
	rot = vec3();
	torq = vec3();

	size = 0;
	age = 0;
	mass = 1;
	health = 1;
	fullHealth = 1;
	type = t;
}


Object::~Object() {}


void Object::Update( int speed ) {
	// If the object has no health, it has been destroyed.
	if( health <= 0 )
		destroy();

	pos += vel * speed;

	rot += torq * speed;
	if( rot[0] >= 360 )
		rot[0] = fmodf( rot[0], 360.0 );
	if( rot[1] >= 360 )
		rot[1] = fmodf( rot[1], 360.0 );
	if( rot[2] >= 360 )
		rot[2] = fmodf( rot[2], 360.0 );

	age += speed;
}


void Object::Draw() {
	// The rotations are probably not what we want,
	// but they at least offer some motion for now.
	glTranslatef( pos[0], pos[1], pos[2] );
	glRotatef( rot[2], 0.0, 0.0, 1.0 );
	glRotatef( rot[1], 0.0, 1.0, 0.0 );
	glRotatef( rot[0], 1.0, 0.0, 0.0 );
}


float Object::damage( float damage ) {
	if( damage >= health ) {
		damage -= health;
		health = 0;

		return damage;
	}
	else {
		health -= damage;
		return 0;
	}
}


void Object::destroy() { delete this; }


void Object::accel( const vec3 &force ) { vel += force / mass; }


void Object::torque( const vec3 &t ) { torq += t / mass; } 

