/* Particle.cpp
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


#include "Particle.h"

Particle::Particle( GLuint t ) : Displayable( EFFECT ) {
	sizePulse = new Pulse( DOUBLE_ZERO_PULSE, 1, 1 );
	alphaPulse = new Pulse( DOUBLE_ZERO_PULSE, 1, 1 );

	texture = t;
}


Particle::~Particle() {
	delete sizePulse;
	delete alphaPulse;
}


void Particle::Update( int speed ) {
	size = 0.1 * sizePulse->GetNextPulse();
	color[3] = alphaPulse->GetNextPulse();

	// Set Position and Rotation
	Displayable::Update( speed );
}


void Particle::Draw() {
	Displayable::Draw();

	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin( GL_TRIANGLE_STRIP );
		glTexCoord2f( 0, 0 );
		glVertex3f( -size, -size, 0 );
		glTexCoord2f( 0, 1 );
		glVertex3f( -size, size, 0 );
		glTexCoord2f( 1, 0 );
		glVertex3f( size, -size, 0 );
		glTexCoord2f( 1, 1 );
		glVertex3f( size, size, 0 );
	glEnd();
}

