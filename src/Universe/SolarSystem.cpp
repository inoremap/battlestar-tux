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

#include "Planet.h"
#include "SolarSystem.h"
#include "Simplex.h"
#include "Vector.h"


SolarSystem::SolarSystem( vec3 p ) {
	position = p;

	suns = new SpaceGroup();
	satellites = new SpaceGroup();

	// Determine how many planets will be in the system.
	int numPlanets = (int) ceilf( 15 * fabsf( simplexRawNoise(position[0], position[1], position[2]) ) );

	for( int n=1; n <= numPlanets; n++ ) {
		float planetOrbit = fabsf( n * simplexRawNoise(position[0], position[1], position[2], (float) n) );
		Planet* planet = new Planet( this, planetOrbit );
		satellites->addObject( planet );
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


	SpaceObject* cur = (SpaceObject*) satellites->getRoot();
	SpaceObject* next = 0;

	while( cur ) {
		next = (SpaceObject*) cur->getNext();
		delete cur;
		cur = next;
	}

	delete satellites;
}


void SolarSystem::Update() {
	suns->UpdateObjects();
	satellites->UpdateObjects();
}


void SolarSystem::Draw() {
	suns->DrawObjects();
	satellites->DrawObjects();
}


float SolarSystem::getCentralMass() {
	// Mass of Sol is 1.9891 * 10^30
	return 1989100000000000000000000000000;
}

