/* SolarSystem.h
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


#ifndef SOLARSYSTEM_H_
#define SOLARSYSTEM_H_

#include "SpaceGroup.h"
#include "SpaceObject.h"
#include "tinyxml.h"
#include "Vector.h"


/* Solar system contains suns, planets, moons and other objects.
 *
 * The SolarSystem's particulars are procedurally generated at creation.
 */
class SolarSystem : public SpaceObject {
	public:
				SolarSystem( vec3 );
				~SolarSystem();

				// Add the solar system configuration to the given XML node.
				void toXML( TiXmlElement* );

				void Update();

				void Draw();

				// Return the magnitude of the center of mass of the solar
				// system (Kg).  If there are multiple suns, that center of mass
				// will be somewhere between the suns.
				//
				// When the solar system is drawn, this point will be at (0, 0).
				float getCentralMass();
				inline float getMass() { return getCentralMass(); }

				vec3 getPos() { return position; }

	private:
				SolarSystem( const SolarSystem & );
				const SolarSystem & operator= ( const SolarSystem & );

				// Position of the solar system in the galaxy.
				vec3 position;

				// Sun(s) in the solar system.
				SpaceGroup* suns;

				// Planets/Planetoids/Comets/Asteroids in this solar system.
				SpaceGroup* satellites;
};


#endif /*SOLARSYSTEM_H_*/
