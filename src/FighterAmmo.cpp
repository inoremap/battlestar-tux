/* FighterAmmo.cpp
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


#include "FighterAmmo.h"
#include "GfxUtils.h"

FighterAmmo::FighterAmmo( FighterAmmoType f, Game* g ) : Displayable( g ) {
	type = f;
	texture = loadTexture( "data/gfx/laser_0001-64.png" );
	game = g;

	pos[2] = zPos;

	size[0] = 0.5;
	size[1] = 4;

	color[0] = 0.0;
	color[1] = 1.0;
	color[2] = 0.2;
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
