/* Ground.cpp
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


#include <math.h>

#include "Ground.h"
#include "TextureManager.h"

Ground::Ground( GroundType type, Game* g ) {
	groundType = type;
	game = g;
	texture = game->getTextureManager()->loadTexture( "data/gfx/ground_0001-256.png" );

	segmentSize = 10;
}


Ground::~Ground() {
	game->getTextureManager()->freeTextures( 1, &texture );
}


void Ground::Update() {}


void Ground::Draw() {
	float* pos = game->getPos();
	float* bounds = game->getBounds();

	float texCoords[4][2] = {
		{ 0, 1 },
		{ 0, 0 },
		{ 1, 1 },
		{ 1, 0 }
	};

	glPushMatrix();

	// Draw horizontal strips across the screen, starting at the bottom.
	glBindTexture( GL_TEXTURE_2D, texture );
	for( float y = findLowerMultiple(-bounds[1] + pos[1]); y <= findUpperMultiple(bounds[1] + pos[1]); y+=segmentSize ) {
		int tex = 0;

		glBegin( GL_TRIANGLE_STRIP );
			glColor4f( 1.0, 1.0, 1.0, 1.0 );

			// Draw one horizontal strip at given y position.
			for( float x = findLowerMultiple(-bounds[0] + pos[0]); x <= findUpperMultiple(bounds[0] + pos[0]); x+=segmentSize ) {
				if( tex >= 4 )
					tex = 0;

				glTexCoord2fv( texCoords[tex] );
				glVertex3f( x, y + segmentSize, 1 );
				tex++;
				glTexCoord2fv( texCoords[tex] );
				glVertex3f( x, y, 1 );
				tex++;
			}
		glEnd();

	}

	glPopMatrix();
}


GroundType Ground::getType() { return groundType; }
GLuint Ground::getTexture() { return texture; }


float Ground::findLowerMultiple( const float n ) {
	return n - fmodf( n, segmentSize );
}


float Ground::findUpperMultiple( const float n ) {
	return n + ( segmentSize - fmodf(n, segmentSize) );
}
