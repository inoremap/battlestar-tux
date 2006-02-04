/* Fighter.cpp
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


#include "Fighter.h"

Fighter::Fighter( FighterAlignment a, Game* g ) : Displayable( FIGHTER, g ) {
	align = a;

	texture = 0;

	pos[2] = zPos;

	size[0] = 3;
	size[1] = 3;

	firing = false;
}


Fighter::~Fighter() {
	delete weaponSystem;
}


void Fighter::Draw() {
	float mx = size[0] / 2;
	float my = size[1] / 2;

	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin( GL_QUADS );
		glColor4f( color[0], color[1], color[2], color[3] );
		glTexCoord2f( 0, 1 );
		glVertex3f( pos[0] - mx, pos[1] - my, pos[2] );
		glTexCoord2f( 1, 1 );
		glVertex3f( pos[0] + mx, pos[1] - my, pos[2] );
		glTexCoord2f( 1, 0 );
		glVertex3f( pos[0] + mx, pos[1] + my, pos[2] );
		glTexCoord2f( 0, 0 );
		glVertex3f( pos[0] - mx, pos[1] + my, pos[2] );
	glEnd();
}


void Fighter::Update() {
	weaponSystem->Fire( firing );

	Displayable::Update();
}


void Fighter::startFiring() { firing = true; }
void Fighter::stopFiring() { firing = false; }


void Fighter::damage( float damage ) {
	if( (damage - shields) > 0 ) {
		shields = 0;
		health -= (damage - shields);
	}
	else {
		shields -= damage;
	}

	if( health < 0 )
		health = 0;
}


float Fighter::getHealth() { return health; }
float Fighter::getHealthFull() { return healthFull; }
float Fighter::getShields() { return shields; }
float Fighter::getShieldsFull() { return shieldsFull; }
int Fighter::getAlignment() { return align; }
