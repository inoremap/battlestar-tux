/* PlanetButton.h
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


#ifndef PLANETBUTTON_H_
#define PLANETBUTTON_H_

#include <SDL_opengl.h>

#include "../../Game.h"

/* Button containing a rotating planet. */
class PlanetButton {
	public:
				PlanetButton( float radius, int precision, float torque, float rotX, float rotZ, Game* g );

				// Update planet button.
				void Update();

				// Draw planet button.
				void Draw();

	private:
				PlanetButton( const PlanetButton &planet );
				const PlanetButton & operator= ( const PlanetButton &planet );

				// Size of planet.
				float radius;

				// Subdivision of sphere.
				// Values 35 to 100 seem reasonable.
				int precision;

				// Current planet angle.
				float rotation;

				// Speed of planet rotation.
				float torque;

				// Planet's deviation from straight up.
				float offAxisX;
				float offAxisZ;

				GLuint texture;

				Game* game;
};


#endif /*PLANETBUTTON_H_*/
