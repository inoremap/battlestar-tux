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
	torque = vec3();

	size = 0;
	age = 0;
	mass = 1;
	health = 1;
	fullHealth = 1;
	type = t;
}


Object::~Object() {}


void Object::Update( int speed ) {
	pos += vel * speed;

	rot += torque * speed;

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


void Object::accel( const vec3 &force ) { vel += force / mass; }

