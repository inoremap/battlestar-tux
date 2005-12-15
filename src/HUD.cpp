/* HUD.cpp
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


#include "SDL.h"
#include "SDL_opengl.h"

#include "HUD.h"

HUD::HUD() {
	
}


void HUD::Draw() {
	// Use orthographic projection for HUD
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
		glLoadIdentity();
		glOrtho( -10, 10, -10, 10, -1000, 1000 );

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
			glLoadIdentity();
			glBegin( GL_QUAD_STRIP );
				glColor4f( 0.0, 1.0, 0.0, 0.3 );
				glVertex3f( -1.0/2, -1.0, 0.0 );
				glVertex3f( -1.0/2, 1.0, 0.0 );
				glVertex3f( 0.0, -1.0, 1.0/2 );
				glVertex3f( 0.0, 1.0, 1.0/2 );
				glVertex3f( 1.0/2, -1.0, 0.0 );
				glVertex3f( 1.0/2, 1.0, 0.0 );
				glVertex3f( 0.0, -1.0, -1.0/2 );
				glVertex3f( 0.0, 1.0, -1.0/2 );
				glVertex3f( -1.0/2, -1.0, 0.0 );
				glVertex3f( -1.0/2, 1.0, 0.0 );
			glEnd();
		glPopMatrix();

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
}
