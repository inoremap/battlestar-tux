/* SolarSystem.cpp
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
#include "SolarSystem.h"
#include "Simplex.h"
#include "Vector.h"


SolarSystem::SolarSystem( vec3 p ) {
	position = p;

	suns = new SpaceGroup();
	satellites = new SpaceGroup();

	// Determine how many planets will be in the system.
	int numPlanets = (int) floorf( simplexScaledNoise(2, 0.3, 1, 0, 20, logf(position[0]), logf(position[1]), logf(position[2])) );

	// Determine planet orbital radii.
	// In our solar system, Mercury is about 6 * 10^7 km out.  Neptune is 2.8 * 10^10 km.
	float planetOrbit = 0.0;
	float previousOrbit = simplexScaledNoise(2, 0.3, 1, 50000000000.0, 100000000000.0, logf(position[0]), logf(position[1]), logf(position[2]), 0.0 );
	for( int n=1; n <= numPlanets; n++ ) {
		// In our solar system, the orbital distance of each succeeding planet
		// is usually 1.4 to 2.0 times the distance of the previous planet.
		planetOrbit = previousOrbit * simplexScaledNoise(2, 0.3, 1, 1.2, 2.2, logf(position[0]), logf(position[1]), logf(position[2]), (float) n );
		Planet* planet = new Planet( this, planetOrbit );
		satellites->addObject( planet );

		previousOrbit = planetOrbit;
	}
}


SolarSystem::~SolarSystem() {
	SpaceObject* cur = (SpaceObject*) suns->getRoot();
	SpaceObject* next = 0;

	while( cur ) {
		next = (SpaceObject*) cur->getNext();
		delete cur;
		cur = next;
	}

	delete suns;


	cur = (SpaceObject*) satellites->getRoot();
	next = 0;

	while( cur ) {
		next = (SpaceObject*) cur->getNext();
		delete cur;
		cur = next;
	}

	delete satellites;
}


void SolarSystem::toXML( TiXmlElement* node ) {
	node->SetAttribute( "type", "solar_system" );

	TiXmlElement* sunNode = new TiXmlElement( "Suns" );
	suns->toXML( sunNode );
	node->LinkEndChild( sunNode );

	TiXmlElement* satNode = new TiXmlElement( "Satellites" );
	satellites->toXML( satNode );
	node->LinkEndChild( satNode );
}


void SolarSystem::Update() {
	suns->UpdateObjects();
	satellites->UpdateObjects();
}


void SolarSystem::Draw() {
	// Set star system OpenGL lighting requirements.
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	float lightPos[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDif[] = { 0.75, 0.75, 1.0, 1.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, lightPos );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, lightDif );

	// Use orthographic projection from above sun's ecliptic plane.
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
		glLoadIdentity();
		glOrtho( -750, 750, -750, 750, -100, 100 );

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
			glLoadIdentity();

			// Draw solar system.
			suns->DrawObjects();
			satellites->DrawObjects();

	// Return projection and modeliew matrices to their previous states.
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();

	// Return to standard OpenGL lighting settings.
	glDisable( GL_LIGHT0 );
	glDisable( GL_LIGHTING );
}


float SolarSystem::getCentralMass() {
	// Mass of Sol is 1.9891 * 10^30 kg.
	return 1989100000000000000000000000000.0;
}

