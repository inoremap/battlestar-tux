/* HexCell.cpp
 *
 * Copyright 2007 Eliot Eshelman
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


#include <SDL_opengl.h>

#include "Fighter.h"
#include "HexCell.h"
#include "HexCellList.h"

HexCell::HexCell( Fighter* f, HexCellType t, const vec2 &p  ) : Object( CELL ) {
	fighter = f;

	cellType = t;

	cellOffset = p;
}


HexCell::~HexCell() {}


void HexCell::Update( int speed ) {
	Object::Update( speed );
}


void HexCell::Draw() {
	glPushMatrix();

	// The matrices have already been transformed for
	// the position of the fighter - we just need to
	// translate to the position of this cell in the fighter.
	glTranslatef( cellOffset[0], cellOffset[1], 0 );

	drawHex( 0.5, 0.65, .2 );

	glPopMatrix();
}


vec2 HexCell::getCellPosition() { return cellOffset; }
HexCellType HexCell::getCellType() { return cellType; }


void HexCell::drawHex( float innerWidth, float outerWidth, float height ) {
	// We'll add half to the top, and half to the bottom.
	height /= 2;

	// Draw top.
	glBegin( GL_TRIANGLE_STRIP );
		for( int i=0; i < 7; i+=2 ) {
			glTexCoord2f( 0, 1 );
			glVertex3f( HEX_VERTS[i][0] * outerWidth, HEX_VERTS[i][1] * outerWidth, height );
			glTexCoord2f( 0, 0 );
			glVertex3f( HEX_VERTS[i][0] * innerWidth, HEX_VERTS[i][1] * innerWidth, height );

			glTexCoord2f( 1, 1 );
			glVertex3f( HEX_VERTS[i+1][0] * outerWidth, HEX_VERTS[i+1][1] * outerWidth, height );
			glTexCoord2f( 1, 0 );
			glVertex3f( HEX_VERTS[i+1][0] * innerWidth, HEX_VERTS[i+1][1] * innerWidth, height );
		}
	glEnd();

	// Draw bottom.
	glBegin( GL_TRIANGLE_STRIP );
		for( int i=0; i < 7; i+=2 ) {
			glTexCoord2f( 0, 0 );
			glVertex3f( HEX_VERTS[i][0] * innerWidth, HEX_VERTS[i][1] * innerWidth, -height );
			glTexCoord2f( 0, 1 );
			glVertex3f( HEX_VERTS[i][0] * outerWidth, HEX_VERTS[i][1] * outerWidth, -height );

			glTexCoord2f( 1, 0 );
			glVertex3f( HEX_VERTS[i+1][0] * innerWidth, HEX_VERTS[i+1][1] * innerWidth, -height );
			glTexCoord2f( 1, 1 );
			glVertex3f( HEX_VERTS[i+1][0] * outerWidth, HEX_VERTS[i+1][1] * outerWidth, -height );
		}
	glEnd();

	// If innerWidth is 0, there won't be a hole in the middle.
	if( innerWidth > 0 ) {
		// Draw inner sides.
		glBegin( GL_TRIANGLE_STRIP );
			for( int i=0; i < 7; i+=2 ) {
				glTexCoord2f( 0, 1 );
				glVertex3f( HEX_VERTS[i][0] * innerWidth, HEX_VERTS[i][1] * innerWidth, height );
				glTexCoord2f( 0, 0 );
				glVertex3f( HEX_VERTS[i][0] * innerWidth, HEX_VERTS[i][1] * innerWidth, -height );
	
				glTexCoord2f( 1, 1 );
				glVertex3f( HEX_VERTS[i+1][0] * innerWidth, HEX_VERTS[i+1][1] * innerWidth, height );
				glTexCoord2f( 1, 0 );
				glVertex3f( HEX_VERTS[i+1][0] * innerWidth, HEX_VERTS[i+1][1] * innerWidth, -height );
			}
		glEnd();
	}

	// Draw outer sides.
	glBegin( GL_TRIANGLE_STRIP );
		for( int i=0; i < 7; i+=2 ) {
			glTexCoord2f( 0, 1 );
			glVertex3f( HEX_VERTS[i][0] * outerWidth, HEX_VERTS[i][1] * outerWidth, height );
			glTexCoord2f( 0, 0 );
			glVertex3f( HEX_VERTS[i][0] * outerWidth, HEX_VERTS[i][1] * outerWidth, -height );

			glTexCoord2f( 1, 1 );
			glVertex3f( HEX_VERTS[i+1][0] * outerWidth, HEX_VERTS[i+1][1] * outerWidth, height );
			glTexCoord2f( 1, 0 );
			glVertex3f( HEX_VERTS[i+1][0] * outerWidth, HEX_VERTS[i+1][1] * outerWidth, -height );
		}
	glEnd();
}

