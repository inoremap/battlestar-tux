/* FighterAmmoList.cpp
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


#include <math.h>

#include "FighterAmmo.h"
#include "FighterAmmoList.h"
#include "GfxUtils.h"

FighterAmmoList::FighterAmmoList( Game* g ) : DisplayableList( g ) {
	// Load all ammo textures.
	textures[0] = loadTexture( "data/gfx/laser_0001-64.png" );		// LIGHT_LASER
	textures[1] = loadTexture( "data/gfx/laser_0001-64.png" );		// MEDIUM_LASER
	textures[2] = loadTexture( "data/gfx/laser_0001-64.png" );		// HEAVY_LASER
	textures[3] = loadTexture( "data/gfx/plasma_0001-32.png" );		// LIGHT_PLASMA
	textures[4] = loadTexture( "data/gfx/plasma_0001-32.png" );		// MEDIUM_PLASMA
	textures[5] = loadTexture( "data/gfx/plasma_0001-32.png" );		// HEAVY_PLASMA
}


FighterAmmoList::~FighterAmmoList() {
	glDeleteTextures( numFighterAmmo, textures );

	for( int i=0; i < numFighterAmmo; i++ )
		textures[i] = 0;
}


GLuint FighterAmmoList::getTexture( int index ) { return textures[index]; }
