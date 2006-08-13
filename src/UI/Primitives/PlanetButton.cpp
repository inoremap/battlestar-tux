/* Planet.cpp
 *
 * Copyright 2006 Eliot Eshelman
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

#include "PlanetButton.h"
#include "../../TextureManager.h"

PlanetButton::PlanetButton( float r, int p, float t, float rotX, float rotZ, Game* g ) {
	radius = r;
	precision = p;
	rotation = 0.0;
	torque = t;
	offAxisX = rotX;
	offAxisZ = rotZ;

	game = g;

	texture = game->getTextureManager()->loadTexture( "data/gfx/planet_0001-256.png" );
}


void PlanetButton::Update() {
	rotation += torque * game->getGameSpeed();

	// Avoid accumulation errors.
	if( rotation >= 360 )
		rotation -= 360;
}


void PlanetButton::Draw() {
	glBindTexture( GL_TEXTURE_2D, texture );

	glRotatef( offAxisX, 1.0, 0.0, 0.0 );
	glRotatef( offAxisZ, 0.0, 0.0, 1.0 );
	glRotatef( rotation, 0.0, 1.0, 0.0 );

	float matAmb[] = { 0.1, 0.1, 0.1, 1.0 };
	float matDif[] = { 0.95, 0.95, 0.95, 1.0 };
	glMaterialfv( GL_FRONT, GL_AMBIENT, matAmb );
	glMaterialfv( GL_FRONT, GL_DIFFUSE, matDif );

	// Draw planet as sphere.
	// http://local.wasp.uwa.edu.au/~pbourke/modelling/openglsphere/
	const float TWOPI = M_PI * 2;
	const float PITWO = M_PI / 2;
	float theta1 = 0.0;
	float theta2 = 0.0;
	float theta3 = 0.0;

	// Center of polygon.
	float cx = 0.0;
	float cy = 0.0;
	float cz = 0.0;

	// Face of polygon.
	float px = 0.0;
	float py = 0.0;
	float pz = 0.0;

	// Normal of polygon.
	float nx = 0.0;
	float ny = 0.0;
	float nz = 0.0;

	for( int j = 0; j < precision/2; ++j ) {
		theta1 = j * TWOPI / precision - PITWO; 
		theta2 = (j + 1) * TWOPI / precision - PITWO; 

		glBegin( GL_QUAD_STRIP );
			for( int i = 0; i <= precision; ++i ) {
				theta3 = i * TWOPI / precision;

				nx = cosf( theta2 ) * cosf( theta3 );
				ny = sinf( theta2 );
				nz = cosf( theta2 ) * sinf( theta3 );
				px = cx + radius * nx; 
				py = cy + radius * ny; 
				pz = cz + radius * nz; 

				glNormal3f( nx, ny, nz );
				glTexCoord2f( i/(float)precision, 2*(j+1)/(float)precision );
				glVertex3f( px, py, pz );

				nx = cosf( theta1 ) * cosf( theta3 );
				ny = sinf( theta1 );
				nz = cosf( theta1 ) * sinf( theta3 );
				px = cx + radius * nx; 
				py = cy + radius * ny; 
				pz = cz + radius * nz; 
	
				glNormal3f( nx, ny, nz );
				glTexCoord2f( i/(float)precision, 2*j/(float)precision );
				glVertex3f( px, py, pz );
			}
		glEnd();
	}
}
