/* Fighter.cpp
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


#include "Fighter.h"

Fighter::Fighter( FighterAlignment a, Game* g ) : Displayable( FIGHTER, g ) {
	align = a;

	texture = 0;

	pos[2] = zPos;

	size[0] = 3;
	size[1] = 3;

	shield = 0;
	weaponSystem = 0;
}


Fighter::~Fighter() {
	delete shield;
	delete weaponSystem;
}


void Fighter::Draw() {
	glBindTexture( GL_TEXTURE_2D, texture );
	Displayable::Draw();

	if( shield )
		shield->Draw();
}


void Fighter::Update() {
	weaponSystem->Update();

	if( shield )
		shield->Update();

	Displayable::Update();
}


void Fighter::startFiring() { weaponSystem->Fire( true ); }
void Fighter::stopFiring() { weaponSystem->Fire( false ); }


void Fighter::damage( float damage, float* point ) {
	health -= damage;

	if( health < 0 )
		health = 0;
}


float Fighter::getHealth() { return health; }
float Fighter::getHealthFull() { return healthFull; }


Shield* Fighter::getShield() { return shield; }


WeaponSystem* Fighter::getWeaponSystem() { return weaponSystem; }


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
