/* Screen.h
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


#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>
#include <SDL_opengl.h>

#include "Game.h"
#include "IntegerVector.h"
#include "Vector.h"

/* Represents screen application will draw on. */
class Screen {
	public:
				// Creates a screen in a new window.
				Screen( Game* );

				// Returns true if the SDL screen hasn't been created.
				const bool isNull();

				// Call when the window size changes to resize the viewport
				void Resize( const int, const int );

				// Change the field-of-view (FOV).  Essentially, the zoom.
				void setFOVY( const float );

				// Return the position of the cursor on the screen.
				const ivec2 getCursorPos();

				const int getWidth();
				const int getHeight();
				const float getFOVY();

	private:
				Screen( const Screen & );
				const Screen & operator= ( const Screen & );

				SDL_Surface* screen;
				int height;
				int width;
				float fovy;
};


#endif /*SCREEN_H_*/
