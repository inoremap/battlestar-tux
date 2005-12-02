/* Screen.h
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


#include "SDL.h"
#include "SDL_opengl.h"

#ifndef SCREEN_H_
#define SCREEN_H_

/* Represents screen application will draw on. */
class Screen {
	public:
				// Creates a screen in a new window.
				Screen();

				// Returns true if the SDL screen hasn't been created.
				bool isNull();

				// Call when the window size changes to resize the viewport
				void Resize( int width, int height );

	private:
				SDL_Surface* screen;
				int height;
				int width;
};


#endif /*SCREEN_H_*/
