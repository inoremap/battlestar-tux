/* GroundSegment.cpp
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


#include "SDL_opengl.h"

#include "GroundSegment.h"

GroundSegment::GroundSegment( GroundType type, Ground* gr, Game* ga ) : Displayable( ga ) {
	groundType = type;
	ground = gr;
	game = ga;
	prev = next = 0;

	// Set the proper velocity.
	vel[1] = 0.0 - game->getScrollSpeed();

	// Set the proper segment size.
	size[0] = ground->segSize;
	size[1] = ground->segSize;
}


void GroundSegment::Draw() {
	float my = size[1] / 2;
	float offset = 0.0;

	glBegin( GL_QUADS );
		glColor3f( 0.3, 0.3, 0.0 );

		for( int i=0; i < ground->numSegX/2; i++ ) {
			offset = i * size[0];

			glVertex3f( pos[0] - offset - size[0], pos[1] - my, pos[2] );
			glVertex3f( pos[0] - offset, pos[1] - my, pos[2] );
			glVertex3f( pos[0] - offset, pos[1] + my, pos[2] );
			glVertex3f( pos[0] - offset - size[0], pos[1] + my, pos[2] );

			glVertex3f( pos[0] + offset, pos[1] - my, pos[2] );
			glVertex3f( pos[0] + offset + size[0], pos[1] - my, pos[2] );
			glVertex3f( pos[0] + offset + size[0], pos[1] + my, pos[2] );
			glVertex3f( pos[0] + offset, pos[1] + my, pos[2] );
		}
	glEnd();

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
	}
}


GroundSegment* GroundSegment::getPrev() { return prev; }
GroundSegment* GroundSegment::getNext() { return next; }


void GroundSegment::setPrev( GroundSegment* seg ) { prev = seg; }
void GroundSegment::setNext( GroundSegment* seg ) { next = seg; }
