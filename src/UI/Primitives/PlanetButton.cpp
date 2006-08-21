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

PlanetButton::PlanetButton( Game* g, GUI* gui, std::string s, W_Alignment h, float r, int p, float t, float rotX, float rotZ ) : Widget( gui ) {
	// Button needs to be drawn twice.
	secondDraw = true;

	game = g;

	radius = r;
	precision = p;
	rotation = 0.0;
	torque = t;
	offAxisX = rotX;
	offAxisZ = rotZ;

	texture = game->getTextureManager()->loadTexture( "data/gfx/planet_0001-256.png" );


	buttonText = s;
	hAlign = h;

	float llx = 0.0;
	float lly = 0.0;
	float llz = 0.0;
	float urx = 0.0;
	float ury = 0.0;
	float urz = 0.0;
	float descender = font->Descender();
	float ascender = font->Ascender();
	font->BBox( buttonText.c_str(), llx, lly, llz, urx, ury, urz );

	textWidth = urx - llx;
	textHeight = ascender + (-descender);

	if( radius * 2 > textWidth )
		preferredSize[0] = size[0] = ceilf( radius * 2 + W_HORIZ_PAD * 2 );
	else
		preferredSize[0] = size[0] = ceilf( textWidth + W_HORIZ_PAD * 2 );
	preferredSize[1] = size[1] = ceilf( textHeight + radius * 2 + W_VERTI_PAD );
}


void PlanetButton::Update( int x, int y, int state ) {
	rotation += torque * game->getGameSpeed();

	// Avoid accumulation errors.
	if( rotation >= 360 )
		rotation -= 360;

	Widget::Update( x, y, state );
}


void PlanetButton::Draw() {
	// Translate to object position.
	glTranslatef( pos[0], pos[1], 0.0 );

	// Draw background.
/*	if( hover && clicked )
		glColor4fv( W_BG_CLICKED );
	else if( hover )
		glColor4fv( W_BG_HOVER );
	else
		glColor4fv( W_BG );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glBegin( GL_POLYGON );
		glVertex3f( 0.0, 0.0, 0.0 );
		glVertex3f( size[0] - W_EDGE_OFFSET, 0.0, 0.0 );
		glVertex3f( size[0], W_EDGE_OFFSET, 0.0 );
		glVertex3f( size[0], size[1], 0.0 );
		glVertex3f( W_EDGE_OFFSET, size[1], 0.0 );
		glVertex3f( 0.0, size[1] - W_EDGE_OFFSET, 0.0 );
	glEnd();*/

	// Draw text.
	glPushMatrix();
		switch( hAlign ) {
			case HORIZ_LEFT:
				glTranslatef( W_HORIZ_PAD, -font->Descender(), 0.0 );
				break;

			case HORIZ_CENTER:
				glTranslatef( (size[0] - textWidth)/2, -font->Descender(), 0.0 );
				break;

			case HORIZ_RIGHT:
			default:
				glTranslatef( size[0] - textWidth - W_HORIZ_PAD, -font->Descender(), 0.0 );
				break;
		}

/*		if( hover && clicked )
			glColor4fv( W_FG_CLICKED );
		else if( hover )
			glColor4fv( W_FG_HOVER );
		else*/
			glColor4fv( W_FG );
		font->Render( buttonText.c_str() );
	glPopMatrix();

	// Draw edge.
/*	if( hover && clicked )
		glColor4fv( W_EDGE_CLICKED );
	else if( hover )
		glColor4fv( W_EDGE_HOVER );
	else
		glColor4fv( W_EDGE );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glBegin( GL_LINE_LOOP );
		glVertex3f( 0.0, 0.0, 0.0 );
		glVertex3f( size[0] - W_EDGE_OFFSET, 0.0, 0.0 );
		glVertex3f( size[0], W_EDGE_OFFSET, 0.0 );
		glVertex3f( size[0], size[1], 0.0 );
		glVertex3f( W_EDGE_OFFSET, size[1], 0.0 );
		glVertex3f( 0.0, size[1] - W_EDGE_OFFSET, 0.0 );
	glEnd();*/
}


void PlanetButton::SecondDraw() {
	// Draw planet.
	glBindTexture( GL_TEXTURE_2D, texture );

	// Translate to center of planet.
	glTranslatef( pos[0] + radius + W_HORIZ_PAD, pos[1] + radius + textHeight + (size[1] - preferredSize[1])/2, 0.0 );

	glRotatef( offAxisX, 1.0, 0.0, 0.0 );
	glRotatef( offAxisZ, 0.0, 0.0, 1.0 );
	glRotatef( rotation, 0.0, 1.0, 0.0 );

	float matAmb[] = { 0.1, 0.1, 0.1, 1.0 };
	float matDif[] = { 0.90, 0.90, 0.90, 1.0 };

	if( hover ) {
		matAmb[0] = matAmb[1] = matAmb[2] = 0.9;
		matDif[0] = matDif[1] = matDif[2] = 1.0;
	}

	glMaterialfv( GL_FRONT, GL_AMBIENT, matAmb );
	glMaterialfv( GL_FRONT, GL_DIFFUSE, matDif );
	glColor4f( 1.0, 1.0, 1.0, 1.0 );

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
