/* FighterAmmoList.cpp
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


#include <math.h>

#include "FighterAmmo.h"
#include "FighterAmmoList.h"
#include "TextureManager.h"

FighterAmmoList::FighterAmmoList( Game* g ) : ObjectList( g ) {
	TextureManager* t = game->getTextureManager();

	// Load all ammo textures.
	textures[0] = t->loadTexture( "data/gfx/laser_0001-64.png" );		// LASER
	textures[1] = t->loadTexture( "data/gfx/plasma_0001-32.png" );		// PLASMA
}


FighterAmmoList::~FighterAmmoList() {
	game->getTextureManager()->freeTextures( numFighterAmmo, textures );

	for( int i=0; i < numFighterAmmo; i++ )
		textures[i] = 0;
}


GLuint FighterAmmoList::getTexture( int index ) { return textures[index]; }
