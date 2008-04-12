/* HUD.h
 *
 * Copyright 2005-2008 Eliot Eshelman
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


#ifndef HUD_H_
#define HUD_H_

#include <SDL_opengl.h>

#include "Game.h"

/* Heads Up Display - Character info/health. */
class HUD {
	public:
				HUD();
				~HUD();

				// Draw the HUD
				void Draw();

	private:
				HUD( const HUD &hud );
				const HUD & operator= ( const HUD &hud );

				Game* game;

				GLuint healthTexture;
				GLuint shieldsTexture;
};


#endif /*HUD_H_*/
