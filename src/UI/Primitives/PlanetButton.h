/* PlanetButton.h
 *
 * Copyright 2006 Eliot Eshelman
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


#ifndef PLANETBUTTON_H_
#define PLANETBUTTON_H_

#include <SDL_opengl.h>
#include <string>

#include "ButtonClickGenerator.h"
#include "Game.h"
#include "Widget.h"

/* Button containing a rotating planet. */
class PlanetButton : public Widget, public ButtonClickGenerator {
	public:
				PlanetButton( Game* g, GUI* gui, std::string s, W_HAlignment h, W_VAlignment v, float r, int p, float t, float rotX, float rotZ );

				// Draw GUI objects that don't want lighting.
				void Draw();

				// Draw GUI objects that require lighting.
				void SecondDraw();

				void Update( int x, int y, int state );

	private:
				PlanetButton( const PlanetButton &planet );
				const PlanetButton & operator= ( const PlanetButton &planet );

				std::string buttonText;

				// Width of the text in the button.
				int textWidth;

				// Height of the text in the button.
				int textHeight;

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
