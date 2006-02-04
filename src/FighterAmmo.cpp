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

	switch( ammoType ) {
		default:
		case LIGHT_LASER:
			size[0] = 0.2;
			size[1] = 4;
		
			color[0] = 0.0;
			color[1] = 1.0;
			color[2] = 0.2;
			color[3] = 0.7;
			break;

		case MEDIUM_LASER:
			size[0] = 0.3;
			size[1] = 4;
		
			color[0] = 0.0;
			color[1] = 1.0;
			color[2] = 0.2;
			color[3] = 0.6;
			break;

		case HEAVY_LASER:
			size[0] = 0.4;
			size[1] = 4;
		
			color[0] = 0.0;
			color[1] = 1.0;
			color[2] = 0.2;
			color[3] = 0.5;
			break;

		case LIGHT_PLASMA:
			size[0] = 1;
			size[1] = 1;
		
			color[0] = 1.0;
			color[1] = 1.0;
			color[2] = 1.0;
			color[3] = 0.9;
			break;

		case MEDIUM_PLASMA:
			size[0] = 1.5;
			size[1] = 1.5;
		
			color[0] = 1.0;
			color[1] = 1.0;
			color[2] = 1.0;
			color[3] = 0.9;
			break;

		case HEAVY_PLASMA:
			size[0] = 2;
			size[1] = 2;
		
			color[0] = 1.0;
			color[1] = 1.0;
			color[2] = 1.0;
			color[3] = 0.9;
			break;
	}
}


void FighterAmmo::Draw() {
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


float FighterAmmo::getDamage() { return damage; }
float FighterAmmo::getPenetration() { return penetration; }
