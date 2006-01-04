/* Displayable.h
 *
 * Copyright 2005 Eliot Eshelman
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


#ifndef DISPLAYABLE_H_
#define DISPLAYABLE_H_

#include "Game.h"

/* Any item which appears on the screen is Displayable. */
class Displayable {
	public:
				Displayable( Game* g );
				virtual ~Displayable();

				// Move object to its new position.
				virtual void UpdatePos();

				// Draw the object to the screen.
				virtual void Draw();

				void setSize( float w, float h );

				// Some (all?) objects have a set Z position.
				// In this case, just set X and Y positions.
				void setPos( float x, float y );
				void setPos( float x, float y, float z );

				void setVel( float x, float y, float z );

				void setColor( float r, float g, float b, float a );

				void incrAge();

				void setStayOnScreen( bool stay );

				float* getSize();
				float* getPos();
				float* getVel();
				float* getColor();
				unsigned int getAge();
				bool getStayOnScreen();

	protected:
				// Size (width and height) of object.
				float size[2];

				// Position (X, Y, Z) at center of object.
				float pos[3];

				// Velocity (X, Y, Z)
				// Number of units to move in each direction each frame.
				// Remember that the game runs at 50 FPS, regardless of what the
				// user's screen is actually displaying.
				float vel[3];

				// Color (Red, Green, Blue, Alpha)
				float color[4];

				// Age of item in frames
				unsigned int age;

				// Must the object remain on the screen at all times?
				bool stayOnScreen;

				Game* game;
};


#endif /*DISPLAYABLE_H_*/
