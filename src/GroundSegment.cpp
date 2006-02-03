/* GroundSegment.cpp
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


#include "SDL_opengl.h"

#include "GroundSegment.h"

GroundSegment::GroundSegment( GroundType type, Ground* gr, Game* ga ) : Displayable( GROUND, ga ) {
	groundType = type;
	ground = gr;
	texture = ground->getTexture();

	pos[2] = ground->zPos;

	// Set the proper velocity.
	vel[1] = 0.0 - game->getScrollSpeed();

	// Set the proper segment size.
	size[0] = ground->segSize;
	size[1] = ground->segSize;
}


void GroundSegment::Draw() {
	float my = size[1] / 2;
	float offset = 0.0;

	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin( GL_QUADS );
		glColor4f( color[0], color[1], color[2], color[3] );

		for( int i=0; i < ground->numSegX/2; i++ ) {
			offset = i * size[0];

			glTexCoord2f( 0, 0 );
			glVertex3f( pos[0] - offset - size[0], pos[1] - my, pos[2] );
			glTexCoord2f( 1, 0 );
			glVertex3f( pos[0] - offset, pos[1] - my, pos[2] );
			glTexCoord2f( 1, 1 );
			glVertex3f( pos[0] - offset, pos[1] + my, pos[2] );
			glTexCoord2f( 0, 1 );
			glVertex3f( pos[0] - offset - size[0], pos[1] + my, pos[2] );

			glTexCoord2f( 1, 0 );
			glVertex3f( pos[0] + offset, pos[1] - my, pos[2] );
			glTexCoord2f( 0, 0 );
			glVertex3f( pos[0] + offset + size[0], pos[1] - my, pos[2] );
			glTexCoord2f( 0, 1 );
			glVertex3f( pos[0] + offset + size[0], pos[1] + my, pos[2] );
			glTexCoord2f( 1, 1 );
			glVertex3f( pos[0] + offset, pos[1] + my, pos[2] );
		}
	glEnd();

/*	Draw a line grid over the ground.
	for( int i=0; i < 3; i++ ) {
		offset = i * size[0];

		glBegin( GL_LINE_LOOP );
			glColor3f( 0.0, 0.0, 0.0 );

			glVertex3f( pos[0] - offset - size[0], pos[1] - my, pos[2] );
			glVertex3f( pos[0] - offset, pos[1] - my, pos[2] );
			glVertex3f( pos[0] - offset, pos[1] + my, pos[2] );
			glVertex3f( pos[0] - offset - size[0], pos[1] + my, pos[2] );
		glEnd();

		glBegin( GL_LINE_LOOP );
			glColor3f( 0.0, 0.0, 0.0 );

			glVertex3f( pos[0] + offset, pos[1] - my, pos[2] );
			glVertex3f( pos[0] + offset + size[0], pos[1] - my, pos[2] );
			glVertex3f( pos[0] + offset + size[0], pos[1] + my, pos[2] );
			glVertex3f( pos[0] + offset, pos[1] + my, pos[2] );
		glEnd();
	}*/
}
