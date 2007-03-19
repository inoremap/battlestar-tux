/* FighterAmmo.cpp
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


#include "FighterAmmo.h"
#include "FighterAmmoList.h"

FighterAmmo::FighterAmmo( FighterAmmoType f, float d, float p, GLuint t, Game* g ) : Object( AMMO ) {
	ammoType = f;
	damage = d;
	penetration = p;
	texture = t;

	pos[2] = zPos;

	switch( ammoType ) {
		default:
		case LASER:
			size = 4;
			break;

		case PLASMA:
			size = 1;
			break;
	}
}


void FighterAmmo::Draw() {
	glBindTexture( GL_TEXTURE_2D, texture );
	Object::Draw();
}


float FighterAmmo::getDamage() { return damage; }
float FighterAmmo::getPenetration() { return penetration; }
