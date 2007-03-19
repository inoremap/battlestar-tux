/* Displayable.cpp
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


#include "Displayable.h"

Displayable::Displayable( DisplayableType t, Game* g ) {
	game = g;

	size = 10;

	pos = 0;

	// The default vertical position is as close to the
	// screen as possible.  Most objects will be drawn
	// at a greater distance.
	pos[2] = -1.0;

	vel = 0;

	rot = 0;
	torque = 0;

	color[0] = 1.0;
	color[1] = 1.0;
	color[2] = 1.0;
	color[3] = 1.0;

	age = 0;

	type = t;

	circular = true;

	polygon = 0;
	numPolygonPoints = 0;

	stayOnScreen = false;
}


Displayable::~Displayable() {
	for( int i=0; i < numPolygonPoints; i++ )
		delete[] polygon[i];
	delete[] polygon;
}


void Displayable::Update() {
	int speed = game->getGameSpeed();

	pos += vel * speed;

	rot += torque * speed;

	age += speed;
}


void Displayable::Draw() {
	glPushMatrix();

	float mx = size[0] / 2;
	float my = size[1] / 2;

	glTranslatef( pos[0], pos[1], pos[2] );
	glRotatef( rot, 0.0, 0.0, 1.0 );

	// Why does this need to be flipped vertically?
	glBegin( GL_TRIANGLE_STRIP );
		glColor4f( color[0], color[1], color[2], color[3] );
		glTexCoord2f( 0, 0 );
		glVertex3f( -mx, my, 0.0 );
		glTexCoord2f( 0, 1 );
		glVertex3f( -mx, -my, 0.0 );
		glTexCoord2f( 1, 0 );
		glVertex3f( mx, my, 0.0 );
		glTexCoord2f( 1, 1 );
		glVertex3f( mx, -my, 0.0 );
	glEnd();

	glPopMatrix();
}


void Displayable::setSize( vec2 &v ) { size = v; }


void Displayable::setPos( vec2 &v ) {
	pos[0] = v[0];
	pos[1] = v[0];

	if( stayOnScreen ) {
		float mx = size[0] / 2;
		float my = size[1] / 2;
	
		if( (pos[0] + mx) > game->getBounds()[0] )
			pos[0] = game->getBounds()[0] - mx;
		if( (pos[0] - mx) < 0.0 - game->getBounds()[0] )
			pos[0] = 0.0 - game->getBounds()[0] + mx;
		if( (pos[1] + my) > game->getBounds()[1] )
			pos[1] = game->getBounds()[1] - my;
		if( (pos[1] - my) < 0.0 - game->getBounds()[1] )
			pos[1] = 0.0 - game->getBounds()[1] + my;
	}
}
void Displayable::setPos( vec3 &v ) {
	pos = v;

	if( stayOnScreen ) {
		float mx = size[0] / 2;
		float my = size[1] / 2;
	
		if( (pos[0] + mx) > game->getBounds()[0] )
			pos[0] = game->getBounds()[0] - mx;
		if( (pos[0] - mx) < 0.0 - game->getBounds()[0] )
			pos[0] = 0.0 - game->getBounds()[0] + mx;
		if( (pos[1] + my) > game->getBounds()[1] )
			pos[1] = game->getBounds()[1] - my;
		if( (pos[1] - my) < 0.0 - game->getBounds()[1] )
			pos[1] = 0.0 - game->getBounds()[1] + my;
	}
}

void Displayable::setVel( vec3 &v ) { vel = v; }

void Displayable::setRot( float r ) { rot = r; }
void Displayable::setTorque( float t ) { torque = t; }

void Displayable::setColor( float r, float g, float b, float a ) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
}

void Displayable::incrAge() { age++; }

void Displayable::setType( int t ) { type = t; }

void Displayable::setCircular( bool circle ) { circular = circle; }

void Displayable::setPolygon( int numPoints, float points[][2] ) {
	polygon = new float*[numPoints];
	numPolygonPoints = numPoints;

	for( int i=0; i < numPolygonPoints; i++ ) {
		polygon[i] = new float[2];
		polygon[i][0] = points[i][0];
		polygon[i][1] = points[i][1];
	}
}

void Displayable::setStayOnScreen( bool stay ) { stayOnScreen = stay; }


vec2 & Displayable::getSize() { return size; }
vec3 & Displayable::getPos() { return pos; }
vec3 & Displayable::getVel() { return vel; }
float Displayable::getRot() { return rot; }
float Displayable::getTorque() { return torque; }
float* Displayable::getColor() { return color; }
unsigned int Displayable::getAge() { return age; }
int Displayable::getType() { return type; }
bool Displayable::getCircular() { return circular; }
float** Displayable::getPolygon() { return polygon; }
int Displayable::getNumPolygonPoints() { return numPolygonPoints; }
bool Displayable::getStayOnScreen() { return stayOnScreen; }
