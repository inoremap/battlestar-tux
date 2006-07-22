/* FighterAmmo.cpp
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


#include "FighterAmmo.h"
#include "FighterAmmoList.h"

FighterAmmo::FighterAmmo( FighterAmmoType f, float d, float p, GLuint t, Game* g ) : Displayable( AMMO, g ) {
	ammoType = f;
	damage = d;
	penetration = p;
	texture = t;

	pos[2] = zPos;

	float points[4][2] = {
		{0.0, 0.0},
		{0.0, 0.0},
		{0.0, 0.0},
		{0.0, 0.0}
	};

	switch( ammoType ) {
		default:
		case LASER:
			size[0] = 0.2;
			size[1] = 4;
		
			color[0] = 0.0;
			color[1] = 1.0;
			color[2] = 0.2;
			color[3] = 0.7;

			points[0][0] = -size[0]/2;
			points[0][1] = size[1]/2;
			points[1][0] = -size[0]/2;
			points[1][1] = -size[1]/2;
			points[2][0] = size[0]/2;
			points[2][1] = -size[1]/2;
			points[3][0] = size[0]/2;
			points[3][1] = size[1]/2;
			setPolygon( 4, points );
			circular = false;
			break;

		case PLASMA:
			size[0] = 1;
			size[1] = 1;
		
			color[0] = 1.0;
			color[1] = 1.0;
			color[2] = 1.0;
			color[3] = 0.9;
			break;
	}
}


void FighterAmmo::Draw() {
	glBindTexture( GL_TEXTURE_2D, texture );
	Displayable::Draw();
}


float FighterAmmo::getDamage() { return damage; }
float FighterAmmo::getPenetration() { return penetration; }
