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

FighterAmmo::FighterAmmo( FighterAmmoType f, float d, GLuint t, Game* g ) : Object( AMMO ) {
	ammoType = f;
	damage = d;
	texture = t;

	pos[2] = zPos;

	switch( ammoType ) {
		default:
		case LASER:
			size = 1;
			break;

		case PLASMA:
			size = 0.75;
			break;
	}
}


void FighterAmmo::Draw() {
	glPushMatrix();

	// Set ammo position, rotation and velocity.
	Object::Draw();
	glBindTexture( GL_TEXTURE_2D, texture );

	// Set the color of the ammo.
	glColor4f( 1.0, 1.0, 1.0, 1.0 );

	float halfSize = size / 2;
	glBegin( GL_QUADS );
		glTexCoord2f( 0, 0 );
		glVertex3f( -halfSize, -halfSize, 0 );
		glTexCoord2f( 1, 0 );
		glVertex3f( halfSize, -halfSize, 0 );
		glTexCoord2f( 1, 1 );
		glVertex3f( halfSize, halfSize, 0 );
		glTexCoord2f( 0, 1 );
		glVertex3f( -halfSize, halfSize, 0 );
	glEnd();

	glPopMatrix();
}

