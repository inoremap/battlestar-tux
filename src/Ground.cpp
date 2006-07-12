/* Ground.cpp
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


#include <math.h>

#include "Ground.h"
#include "TextureManager.h"

Ground::Ground( GroundType type, Game* g ) {
	groundType = type;
	game = g;
	texture = game->getTextureManager()->loadTexture( "data/gfx/ground_0001-256.png" );

	position = 0.0;
	offset = 0.0;
	velocity = -0.05;
	segmentSize = 10;
}


Ground::~Ground() {
	game->getTextureManager()->freeTextures( 1, &texture );
}


void Ground::Update() {
	int speed = game->getGameSpeed();
	position += velocity * speed;
	offset += velocity * speed;
	offset = fmodf( offset, segmentSize );
}


void Ground::Draw() {
	float* bounds = game->getBounds();
	int numSegmentsX = (int) ceil( bounds[0]/segmentSize );
	int numSegmentsY = (int) ceil( bounds[1]/segmentSize );
	float texCoords[4][2] = {
		{ 0, 1 },
		{ 0, 0 },
		{ 1, 1 },
		{ 1, 0 }
	};

	glPushMatrix();
	glLoadIdentity();

	glTranslatef( 0, offset, 0 );

	// Draw horizontal strips across the screen, starting at the bottom.
	glBindTexture( GL_TEXTURE_2D, texture );
	for( int y=-numSegmentsY; y < numSegmentsY; y++ ) {
		int tex = 0;

		glBegin( GL_TRIANGLE_STRIP );
			glColor4f( 1.0, 1.0, 1.0, 1.0 );

			// Draw one horizontal strip at given y position.
			for( int x=-numSegmentsX; x < numSegmentsX; x++ ) {
				if( tex >= 4 )
					tex = 0;

				glTexCoord2fv( texCoords[tex] );
				glVertex3f( x * segmentSize, (y + 1) * segmentSize, sinf(offset + (y + 1) * segmentSize)/2 );
				tex++;
				glTexCoord2fv( texCoords[tex] );
				glVertex3f( x * segmentSize, y * segmentSize, sinf(offset + y * segmentSize)/2 );
				tex++;
			}
		glEnd();
	}

	glPopMatrix();
}


GroundType Ground::getType() { return groundType; }
GLuint Ground::getTexture() { return texture; }
