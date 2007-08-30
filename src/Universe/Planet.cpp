/* Planet.cpp
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


#include <math.h>
#include <SDL_opengl.h>

#include "Planet.h"
#include "Simplex.h"
#include "SpaceObject.h"
#include "Vector.h"


Planet::Planet( SolarSystem* system, float oRadius ) {
	solarSystem = system;
	orbitalRadius = oRadius;

	vec3 systemPos = solarSystem->getPos(); 

	// Radius is somewhat correlated with orbital radius. Always positive.
	radius = fabsf( orbitalRadius * 0.1 * simplexRawNoise(systemPos[0], systemPos[1], systemPos[2], orbitalRadius) );

	// Rotation velocity seems to be uncorrelated with orbital radius.
	rotationVelocity =
		simplexRawNoise( systemPos[0], systemPos[1], systemPos[2], orbitalRadius ) *
		simplexRawNoise( orbitalRadius, systemPos[0], systemPos[1], systemPos[2] );

	// Axial tilt is not correlated with orbital radius.
	axialTilt = 70 *
		simplexRawNoise( systemPos[0], systemPos[1], systemPos[2], orbitalRadius ) *
		simplexRawNoise( orbitalRadius, systemPos[0], systemPos[1], systemPos[2] );

	// Large orbital eccentricity is only possible for large orbital radii. Always positive and less than 1.
	orbitalEccentricity = fabsf( 0.05 * orbitalRadius * simplexRawNoise(systemPos[0], systemPos[1], systemPos[2], orbitalRadius) );

	// Orbital inclination is not correlated with orbital radius.
	orbitalInclination = 10 * simplexRawNoise( systemPos[0], systemPos[1], systemPos[2], orbitalRadius );

	rotationPosition = 0.0;
	orbitalPosition = 0.0;

	// Orbital offset should be essentially random. Always positive.
	orbitalOffset = fabsf( 350 * simplexRawNoise(systemPos[0], systemPos[1], systemPos[2], orbitalRadius) );

	// Create any satellites, such as moons and rings.
	satellites = new SpaceGroup();
}


Planet::~Planet() {
	SpaceObject* cur = (SpaceObject*) satellites->getRoot();
	SpaceObject* next = 0;

	while( cur ) {
		next = (SpaceObject*) cur->getNext();
		delete cur;
		cur = next;
	}

	delete satellites;
}


void Planet::toXML( TiXmlElement* node ) {
	node->SetAttribute( "type", "planet" );
	node->SetDoubleAttribute( "mass", mass );
	node->SetDoubleAttribute( "radius", radius );
	node->SetDoubleAttribute( "rotational_velocity", rotationVelocity );
	node->SetDoubleAttribute( "axial_tilt", axialTilt );
	node->SetDoubleAttribute( "orbital_radius", orbitalRadius );
	node->SetDoubleAttribute( "orbital_eccentricity", orbitalEccentricity );
	node->SetDoubleAttribute( "orbital_inclination", orbitalInclination );
	node->SetDoubleAttribute( "orbital_offset", orbitalOffset );
	node->SetDoubleAttribute( "rotational_position", rotationPosition );
	node->SetDoubleAttribute( "orbital_position", orbitalPosition );

	TiXmlElement* sats = new TiXmlElement( "Satellites" );
	satellites->toXML( sats );

	node->LinkEndChild( sats );
}


void Planet::Update() {
	rotationPosition += rotationVelocity * SpaceObject::UNIVERSE_SPEED;
	if( rotationPosition >= 360 )
		rotationPosition -= 360;

	float orbitalDistance =
		( orbitalRadius * (1 - orbitalEccentricity * orbitalEccentricity) ) /
		( 1 + orbitalEccentricity * cosf(orbitalPosition * M_PI/180) );
	orbitalPosition += sqrtf(
			SpaceObject::GRAVITATIONAL_CONSTANT * ( mass + solarSystem->getCentralMass() ) *
			( 2 / (orbitalDistance * SpaceObject::DISTANCE_SCALE) - 1 / (orbitalRadius * SpaceObject::DISTANCE_SCALE) )
		) * SpaceObject::UNIVERSE_SPEED;
	if( orbitalPosition >= 360 )
		orbitalPosition -= 360;

	satellites->UpdateObjects();
}


void Planet::Draw() {
	glRotatef( orbitalOffset, 0.0, 0.0, 1.0 );
	glRotatef( orbitalInclination, 1.0, 0.0, 0.0 );

	glRotatef( orbitalPosition, 0.0, 0.0, 1.0 );

	// According to Kepler's laws of planetary motion, all objects orbit the
	// sun (or the system's center of gravity) at one of the foci of their
	// elliptical orbit.  We are translating from that foci out.
	//
	// http://en.wikipedia.org/wiki/Kepler%27s_laws_of_planetary_motion
	glTranslatef(
		0.0,
		( orbitalRadius * (1 - orbitalEccentricity * orbitalEccentricity) ) /
		( 1 + orbitalEccentricity * cosf(orbitalPosition * M_PI/180) ),
		0.0
	);

	// axial tilt

	glRotatef( rotationPosition, 0.0, 0.0, 1.0 );


	// Draw planet as sphere.
	// http://local.wasp.uwa.edu.au/~pbourke/modelling/openglsphere/
	const float TWOPI = M_PI * 2;
	const float PITWO = M_PI / 2;
	float theta1 = 0.0;
	float theta2 = 0.0;
	float theta3 = 0.0;

	// The subdivision of the sphere depends on its size.
	int precision = (int) radius * 3;

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

	glBindTexture( GL_TEXTURE_2D, 0 );
	glColor4f( 1.0, 1.0, 1.0, 1.0 );

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


	satellites->DrawObjects();
}

