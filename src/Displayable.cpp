/* Displayable.cpp
 *
 * Copyright 2005 Eliot Eshelman
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


#include "Displayable.h"

Displayable::Displayable( Game* g ) {
	game = g;

	size[0] = 100;
	size[1] = 100;

	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;

	vel[0] = 0;
	vel[1] = 0;
	vel[2] = 0;

	age = 0;
}


void Displayable::UpdatePos() {
	pos[0] = pos[0] + vel[0] * game->getGameSpeed();
	pos[1] = pos[1] + vel[1] * game->getGameSpeed();
	pos[2] = pos[2] + vel[2] * game->getGameSpeed();
}


void Displayable::Draw() {}


void Displayable::setSize( float w, float h ) {
	size[0] = w;
	size[1] = h;
}


void Displayable::setPos( float x, float y, float z ) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}

void Displayable::setVel( float x, float y, float z, float mag ) {
	vel[0] = x;
	vel[1] = y;
	vel[2] = z;
}

void Displayable::incrAge() { age++; }

float* Displayable::getSize() { return size; }
float* Displayable::getPos() { return pos; }
float* Displayable::getVel() { return vel; }
unsigned int Displayable::getAge() { return age; }
