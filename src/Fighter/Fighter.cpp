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

	shield = 0;
	weaponSystem = 0;
}


Fighter::~Fighter() {
	delete shield;
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
	if( shield )
		damage = shield->damage( damage );

	health -= damage;


	if( health < 0 )
		health = 0;
}


float Fighter::getHealth() { return health; }
float Fighter::getHealthFull() { return healthFull; }

Shield* Fighter::getShield() { return shield; }

float Fighter::getShields() {
	if( shield )
		return shield->getShields();
	else
		return 0;
}

float Fighter::getShieldsFull() {
	if( shield )
		return shield->getShieldsFull();
	else
		return 0;
}

int Fighter::getAlignment() { return align; }
