/* FighterAmmoList.h
 *
 * Copyright 2005-2006 Eliot Eshelman
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


#ifndef FIGHTERAMMOLIST_H_
#define FIGHTERAMMOLIST_H_

#include "SDL_opengl.h"

#include "Displayable.h"
#include "DisplayableList.h"

class FighterAmmo;


enum FighterAmmoType {
	LIGHT_LASER,			// Light laser beam
	MEDIUM_LASER,			// Medium laser beam
	HEAVY_LASER,			// Heavy laser beam
	LIGHT_PLASMA,			// Light plasma bolt
	MEDIUM_PLASMA,			// Medium plasma bolt
	HEAVY_PLASMA			// Heavy plasma bolt
};
static const int numFighterAmmo = 6;


/* Holds, updates and draws the fighter's shots. */
class FighterAmmoList : public DisplayableList {
	public:
				FighterAmmoList( Game* g );
				~FighterAmmoList();
				// Get a texture ID.
				GLuint getTexture( int index );

	private:
				// Texture for each type of ammo.
				GLuint textures[numFighterAmmo];
};


#endif /*FIGHTERAMMOLIST_H_*/
