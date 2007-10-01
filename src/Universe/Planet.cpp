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

	// The real values can be too big for Simplex.
	float logRadius = logf( orbitalRadius );
	systemPos[0] = logf( systemPos[0] );
	systemPos[1] = logf( systemPos[1] );
	systemPos[2] = logf( systemPos[2] );

	// When generating the following values, we don't want them to all be based
	// on the same noise value.  By altering the parameters to each,
	// we can be certain that each returned value will be different.

	// Radius may be somewhat correlated with orbital radius -
	// in our solar system, the largest planets are far out from the sun.
	// Mercury's equatorial radius is 2440 km, Jupiter's is 71492 km.
	radius = simplexScaledNoise(2, 0.3, 100, 1000000.0, 90000000.0, systemPos[0], systemPos[0], systemPos[0], logRadius );

	// Mass is not always entirely correlated with a planet's radius - some planets
	// have denser make-ups than others.  The density of earth-like planets is usually
	// 5.5 kg/m^3, while gas giants are closer to 1.6 kg/m^3.
	mass = (4/3) * M_PI * radius * radius * radius * simplexScaledNoise(2, 0.3, 100, 1400, 5700, systemPos[0], systemPos[0], systemPos[1], logRadius );

	// Rotation velocity seems to be uncorrelated with orbital radius.
	// The fastest planets will complete a revolution in 20 seconds.
	rotationVelocity = simplexScaledNoise(2, 0.3, 100, -0.36, 0.36, systemPos[0], systemPos[0], systemPos[2], logRadius );

	// Axial tilt is not correlated with orbital radius.
	axialTilt = simplexScaledNoise(2, 0.3, 100, -70, 70, systemPos[0], systemPos[1], systemPos[0], logRadius );

	// Large orbital eccentricity is usually only possible for large orbital radii. Always positive and less than 1.
	orbitalEccentricity = simplexScaledNoise(2, 0.3, 100, 0, 0.5, systemPos[0], systemPos[1], systemPos[1], logRadius );

	// Orbital inclination is not correlated with orbital radius.
	orbitalInclination = simplexScaledNoise(2, 0.3, 100, -10, 10, systemPos[0], systemPos[1], systemPos[2], logRadius );

	rotationPosition = 0.0;
	orbitalPosition = 0.0;
	currentOrbitalRadius = orbitalRadius;

	// Orbital offset should be essentially random. Always positive.
	orbitalOffset = simplexScaledNoise(2, 0.3, 100, 0, 360, systemPos[0], systemPos[2], systemPos[0], logRadius );

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
		rotationPosition = fmodf( rotationPosition, 360 );

	// According to Kepler's laws of planetary motion, the velocity of an object
	// is determined by the masses and distance between the objects.
	//
	// http://en.wikipedia.org/wiki/Elliptic_orbit
	orbitalPosition += sqrtf( SpaceObject::GRAVITATIONAL_CONSTANT * ( mass + solarSystem->getCentralMass() ) *
			( 2 / (currentOrbitalRadius / 1000) - 1 / (orbitalRadius / 1000) ) )  // velocity of planet at this point
		/ (orbitalRadius * 2 * M_PI)  // approx. circumference of the orbit
		* 360  // number of degrees in the circumference
		/ 50   // number of frames per second
		* SpaceObject::UNIVERSE_SPEED;
	if( orbitalPosition >= 360 )
		orbitalPosition = fmodf( orbitalPosition, 360 );

	satellites->UpdateObjects();
}


void Planet::Draw() {
	// We need to keep the radii of planets within displayable bounds.
	float logRadius = radius / 10000000;

	glPushMatrix();

	glRotatef( orbitalOffset, 0.0, 0.0, 1.0 );
	glRotatef( orbitalInclination, 1.0, 0.0, 0.0 );


	// Outline the orbit of the planet.
	glColor4f( 1.0, 1.0, 1.0, 1.0 );
	glBegin( GL_LINE_LOOP );
		for( float i = 1.0; i < 360; i++ ) {
			float lineRadius = ( orbitalRadius * (1 - orbitalEccentricity * orbitalEccentricity) ) /
				( 1 + orbitalEccentricity * cosf(i * M_PI/180) );
			vec3 coords;
			coords[0] = lineRadius * sinf( i * M_PI/180 );
			coords[1] = lineRadius * cosf( i * M_PI/180 );

			// We need to keep the distances between planets within displayable bounds.
			coords /= 10000000000.0;
			glVertex3f( coords[0], coords[1], coords[2] );
		}
	glEnd();


	glRotatef( orbitalPosition, 0.0, 0.0, 1.0 );

	// According to Kepler's laws of planetary motion, all objects orbit the
	// sun (or the system's center of gravity) at one of the foci of their
	// elliptical orbit.  We are translating from that foci out.
	//
	// http://en.wikipedia.org/wiki/Kepler%27s_laws_of_planetary_motion
	currentOrbitalRadius = ( orbitalRadius * (1 - orbitalEccentricity * orbitalEccentricity) ) /
		( 1 + orbitalEccentricity * cosf(orbitalPosition * M_PI/180) );
	// We need to keep the distances between planets within displayable bounds.
	glTranslatef( 0.0, currentOrbitalRadius / 10000000000.0, 0.0 );

	// axial tilt

	glRotatef( rotationPosition, 0.0, 0.0, 1.0 );


	// Draw planet as sphere.
	// http://local.wasp.uwa.edu.au/~pbourke/modelling/openglsphere/
	const float TWOPI = M_PI * 2;
	const float PITWO = M_PI / 2;
	float theta1 = 0.0;
	float theta2 = 0.0;
	float theta3 = 0.0;

	// The subdivision of the sphere should probably depend on its size.
	int precision = 16;

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
				px = cx + logRadius * nx; 
				py = cy + logRadius * ny; 
				pz = cz + logRadius * nz; 

				glNormal3f( nx, ny, nz );
				glTexCoord2f( i/(float)precision, 2*(j+1)/(float)precision );
				glVertex3f( px, py, pz );

				nx = cosf( theta1 ) * cosf( theta3 );
				ny = sinf( theta1 );
				nz = cosf( theta1 ) * sinf( theta3 );
				px = cx + logRadius * nx; 
				py = cy + logRadius * ny; 
				pz = cz + logRadius * nz; 
	
				glNormal3f( nx, ny, nz );
				glTexCoord2f( i/(float)precision, 2*j/(float)precision );
				glVertex3f( px, py, pz );
			}
		glEnd();
	}

	glPopMatrix();

	satellites->DrawObjects();
}

