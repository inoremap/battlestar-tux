/* Planet.h
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


#ifndef PLANET_H_
#define PLANET_H_

#include <iostream>

#include "SolarSystem.h"
#include "SpaceGroup.h"
#include "SpaceObject.h"
#include "tinyxml.h"


/* Planets are usually part of a solar system, but they may wander.
 *
 * The planet's particulars are procedurally generated at creation.
 */
class Planet : public SpaceObject {
	public:
				Planet( SolarSystem*, float );
				~Planet();

				// Add the planet configuration to the given XML node.
				void toXML( TiXmlElement* );

				void Update();

				void Draw();

				float getRadius() { return radius; }

	private:
				Planet( const Planet & );
				const Planet & operator= ( const Planet & );

				// See http://en.wikipedia.org/wiki/Planet for vocabulary.
				float radius;
				float rotationVelocity;
				float axialTilt;
				// If the orbit is an ellipse, this is the semi-major axis.
				float orbitalRadius;
				float orbitalEccentricity;
				float orbitalInclination;
				// The orbital velocity will be dynamically calculated.

				// The current rotational positions of the planet - updated each frame.
				float rotationPosition;
				float orbitalPosition;
				// As the planet orbits the sun, this is the current distance.
				float currentOrbitalRadius;

				// The angular 'starting point' of the planet as it orbits the solar system.
				float orbitalOffset;

				// Solar system that contains this planet.
				SolarSystem* solarSystem;

				// Any objects which orbit this planet.
				SpaceGroup* satellites;
};


#endif /*PLANET_H_*/
