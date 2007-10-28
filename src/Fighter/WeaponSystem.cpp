/* WeaponSystem.cpp
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


#include <SDL_opengl.h>

#include "Screen.h"
#include "TextureManager.h"
#include "WeaponCell.h"
#include "WeaponSystem.h"

WeaponSystem::WeaponSystem( Fighter* f, Game* g ) : Displayable( HUD ) {
	fireAll = true;
	primaryFiring = false;
	secondaryFiring = false;

	fighter = f;
	game = g;

	texture = game->getTextureManager()->loadTexture( "data/gfx/crosshairs_0001-32.png" );

	pos = fighter->getPos();
	pos[1] += 5;
}


WeaponSystem::~WeaponSystem() {
	game->getTextureManager()->freeTextures( 1, &texture );
}


void WeaponSystem::Update( int speed ) {
	Displayable::Update( speed );
}


void WeaponSystem::Draw() {
	glPushMatrix();

	// Set crosshair position, rotation and color.
	Displayable::Draw();
	glBindTexture( GL_TEXTURE_2D, texture );

	glBegin( GL_QUADS );
		glTexCoord2f( 0, 0 );
		glVertex3f( -1, -1, 0 );
		glTexCoord2f( 1, 0 );
		glVertex3f( 1, -1, 0 );
		glTexCoord2f( 1, 1 );
		glVertex3f( 1, 1, 0 );
		glTexCoord2f( 0, 1 );
		glVertex3f( -1, 1, 0 );
	glEnd();

	glPopMatrix();
}


void WeaponSystem::FirePrimary( bool fire ) {
	primaryFiring = fire;
}


void WeaponSystem::FireSecondary( bool fire ) {
	secondaryFiring = fire;
}

