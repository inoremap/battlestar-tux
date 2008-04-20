/* HexCell.cpp
 *
 * Copyright 2007-2008 Eliot Eshelman
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
#include <assert.h>

#include "Fighter.h"
#include "HexCell.h"
#include "HexCellList.h"

// The collision shape will be created when it is requested.
btCylinderShapeZ* HexCell::hexCollisionShape = 0;

HexCell::HexCell( HexCellType type, const float m ) : Object( CELL, m ) {
	fighter = 0;
	game = Game::getGame();

	cellType = type;
	cellOffset = 0;
	cellPosition = 0;
}


HexCell::~HexCell() {}


void HexCell::Update( int speed ) {
	Object::Update( speed );
}


void HexCell::Draw() {
	drawHex( HEX_CELL_SIZE[0], HEX_CELL_SIZE[1], HEX_CELL_SIZE[2] );
}


void HexCell::mount( Fighter* f, const ivec2 &offset, const vec2 &position ) {
	fighter = f;
	cellOffset = offset;
	cellPosition = position;
}


void HexCell::unmount() {
	fighter = 0;
	cellOffset = 0;
	cellPosition = 0;
}


void HexCell::destroy() {
	assert( fighter );
	fighter->destroyCell( this );
}

ivec2 HexCell::getCellOffset() { return cellOffset; }
vec2 HexCell::getCellPosition() { return cellPosition; }
HexCellType HexCell::getCellType() { return cellType; }


vec3 HexCell::getPos() {
	assert( fighter );
	vec3 fighterPos = fighter->getPos();

	return vec3(
		fighterPos[0] + cellPosition[0],
		fighterPos[1] + cellPosition[1],
		fighterPos[2]
	);
}

vec3 HexCell::getVel() {
	assert( fighter );
	return fighter->getVel();
}

vec3 HexCell::getRot() {
	assert( fighter );
	return fighter->getRot();
}


void HexCell::drawHex( float innerWidth, float outerWidth, float height ) {
	// We'll add half to the top, and half to the bottom.
	height /= 2;

	// Draw top.
	glBegin( GL_TRIANGLE_STRIP );
		for( int i=0; i < 6; i+=2 ) {
			glTexCoord2f( 0, 1 );
			glVertex3f( HEX_VERTS[i][0] * outerWidth, HEX_VERTS[i][1] * outerWidth, height );
			glTexCoord2f( 0, 0 );
			glVertex3f( HEX_VERTS[i][0] * innerWidth, HEX_VERTS[i][1] * innerWidth, height );

			glTexCoord2f( 1, 1 );
			glVertex3f( HEX_VERTS[i+1][0] * outerWidth, HEX_VERTS[i+1][1] * outerWidth, height );
			glTexCoord2f( 1, 0 );
			glVertex3f( HEX_VERTS[i+1][0] * innerWidth, HEX_VERTS[i+1][1] * innerWidth, height );
		}
		glTexCoord2f( 0, 1 );
		glVertex3f( HEX_VERTS[0][0] * outerWidth, HEX_VERTS[0][1] * outerWidth, height );
		glTexCoord2f( 0, 0 );
		glVertex3f( HEX_VERTS[0][0] * innerWidth, HEX_VERTS[0][1] * innerWidth, height );
	glEnd();

	// Draw bottom.
	glBegin( GL_TRIANGLE_STRIP );
		for( int i=0; i < 6; i+=2 ) {
			glTexCoord2f( 0, 0 );
			glVertex3f( HEX_VERTS[i][0] * innerWidth, HEX_VERTS[i][1] * innerWidth, -height );
			glTexCoord2f( 0, 1 );
			glVertex3f( HEX_VERTS[i][0] * outerWidth, HEX_VERTS[i][1] * outerWidth, -height );

			glTexCoord2f( 1, 0 );
			glVertex3f( HEX_VERTS[i+1][0] * innerWidth, HEX_VERTS[i+1][1] * innerWidth, -height );
			glTexCoord2f( 1, 1 );
			glVertex3f( HEX_VERTS[i+1][0] * outerWidth, HEX_VERTS[i+1][1] * outerWidth, -height );
		}
		glTexCoord2f( 0, 0 );
		glVertex3f( HEX_VERTS[0][0] * innerWidth, HEX_VERTS[0][1] * innerWidth, -height );
		glTexCoord2f( 0, 1 );
		glVertex3f( HEX_VERTS[0][0] * outerWidth, HEX_VERTS[0][1] * outerWidth, -height );
	glEnd();

	// If innerWidth is 0, there won't be a hole in the middle.
	if( innerWidth > 0 ) {
		// Draw inner sides.
		glBegin( GL_TRIANGLE_STRIP );
			for( int i=0; i < 6; i+=2 ) {
				glTexCoord2f( 0, 1 );
				glVertex3f( HEX_VERTS[i][0] * innerWidth, HEX_VERTS[i][1] * innerWidth, height );
				glTexCoord2f( 0, 0 );
				glVertex3f( HEX_VERTS[i][0] * innerWidth, HEX_VERTS[i][1] * innerWidth, -height );
	
				glTexCoord2f( 1, 1 );
				glVertex3f( HEX_VERTS[i+1][0] * innerWidth, HEX_VERTS[i+1][1] * innerWidth, height );
				glTexCoord2f( 1, 0 );
				glVertex3f( HEX_VERTS[i+1][0] * innerWidth, HEX_VERTS[i+1][1] * innerWidth, -height );
			}
			glTexCoord2f( 0, 1 );
			glVertex3f( HEX_VERTS[0][0] * innerWidth, HEX_VERTS[0][1] * innerWidth, height );
			glTexCoord2f( 0, 0 );
			glVertex3f( HEX_VERTS[0][0] * innerWidth, HEX_VERTS[0][1] * innerWidth, -height );
		glEnd();
	}

	// Draw outer sides.
	glBegin( GL_TRIANGLE_STRIP );
		for( int i=0; i < 6; i+=2 ) {
			glTexCoord2f( 0, 1 );
			glVertex3f( HEX_VERTS[i][0] * outerWidth, HEX_VERTS[i][1] * outerWidth, height );
			glTexCoord2f( 0, 0 );
			glVertex3f( HEX_VERTS[i][0] * outerWidth, HEX_VERTS[i][1] * outerWidth, -height );

			glTexCoord2f( 1, 1 );
			glVertex3f( HEX_VERTS[i+1][0] * outerWidth, HEX_VERTS[i+1][1] * outerWidth, height );
			glTexCoord2f( 1, 0 );
			glVertex3f( HEX_VERTS[i+1][0] * outerWidth, HEX_VERTS[i+1][1] * outerWidth, -height );
		}
		glTexCoord2f( 0, 1 );
		glVertex3f( HEX_VERTS[0][0] * outerWidth, HEX_VERTS[0][1] * outerWidth, height );
		glTexCoord2f( 0, 0 );
		glVertex3f( HEX_VERTS[0][0] * outerWidth, HEX_VERTS[0][1] * outerWidth, -height );
	glEnd();
}


btCollisionShape* HexCell::getCollisionShape() {
	if( hexCollisionShape == 0 )
		hexCollisionShape = new btCylinderShapeZ(btVector3(HEX_CELL_SIZE[0], HEX_CELL_SIZE[1], HEX_CELL_SIZE[2]));

	return hexCollisionShape;
}

