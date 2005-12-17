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

	size[0] = 10;
	size[1] = 10;

	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;

	vel[0] = 0;
	vel[1] = 0;
	vel[2] = 0;

	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;
	color[3] = 1.0;

	age = 0;

	stayOnScreen = false;
}


Displayable::~Displayable() {}


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


void Displayable::setPos( float x, float y ) { setPos( x, y, pos[2] ); }
void Displayable::setPos( float x, float y, float z ) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;

	if( stayOnScreen ) {
		float mx = size[0] / 2;
		float my = size[1] / 2;

		if( (pos[0] + mx) > game->getBounds()[0] )
			pos[0] = game->getBounds()[0] - mx;
		if( (pos[0] - mx) < 0.0 - game->getBounds()[0] )
			pos[0] = 0.0 - game->getBounds()[0] + mx;
		if( (pos[1] + my) > game->getBounds()[1] )
			pos[1] = game->getBounds()[1] - my;
		if( (pos[1] - my) < 0.0 - game->getBounds()[1] )
			pos[1] = 0.0 - game->getBounds()[1] + my;
	}
}

void Displayable::setVel( float x, float y, float z ) {
	vel[0] = x;
	vel[1] = y;
	vel[2] = z;
}

void Displayable::setColor( float r, float g, float b, float a ) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
}

void Displayable::incrAge() { age++; }


void Displayable::setStayOnScreen( bool stay ) { stayOnScreen = stay; }


float* Displayable::getSize() { return size; }
float* Displayable::getPos() { return pos; }
float* Displayable::getVel() { return vel; }
float* Displayable::getColor() { return color; }
unsigned int Displayable::getAge() { return age; }
bool Displayable::getStayOnScreen() { return stayOnScreen; }
