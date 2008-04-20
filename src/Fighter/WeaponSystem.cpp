/* WeaponSystem.cpp
 *
 * Copyright 2007-2008 Eliot Eshelman
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

WeaponSystem::WeaponSystem( Fighter* f ) : Displayable( HUD ) {
	fireAll = true;
	primaryFiring = false;
	secondaryFiring = false;

	primaryWeapons = std::vector<WeaponCell*>();
	secondaryWeapons = std::vector<WeaponCell*>();

	fighter = f;
	game = Game::getGame();

	texture = game->getTextureManager()->loadTexture( "data/gfx/crosshairs_0001-32.png" );
}


WeaponSystem::~WeaponSystem() {
	game->getTextureManager()->freeTextures( 1, &texture );
}


void WeaponSystem::Update( int speed ) {
	Displayable::Update( speed );

	// The rotation and position of the crosshairs should match the fighter.
	pos = fighter->getPos();
	pos[1] += 5;
	rot[2] = fighter->getRot()[2];

	// The weapon cell status is updated by the fighter, not here.
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

	// Update primary weapons.
	std::vector<WeaponCell*>::iterator iter;
	for( iter = primaryWeapons.begin(); iter != primaryWeapons.end(); iter++ ) {
		(*iter)->Fire( primaryFiring );
	}
}


void WeaponSystem::FireSecondary( bool fire ) {
	secondaryFiring = fire;

	// Update secondary weapons.
	std::vector<WeaponCell*>::iterator iter;
	for( iter = secondaryWeapons.begin(); iter != secondaryWeapons.end(); iter++ ) {
		(*iter)->Fire( secondaryFiring );
	}
}


void WeaponSystem::addPrimaryWeapon( WeaponCell* w )	{ addWeapon(primaryWeapons, w); }
void WeaponSystem::addSecondaryWeapon( WeaponCell* w )	{ addWeapon(secondaryWeapons, w); }
void WeaponSystem::remPrimaryWeapon( WeaponCell* w )	{ remWeapon(primaryWeapons, w); }
void WeaponSystem::remSecondaryWeapon( WeaponCell* w )	{ remWeapon(secondaryWeapons, w); }


void WeaponSystem::addWeapon( std::vector<WeaponCell*> & cells, WeaponCell* w ) {
	cells.push_back( w );
}


void WeaponSystem::remWeapon( std::vector<WeaponCell*> & cells, WeaponCell* w ) {
	std::vector<WeaponCell*>::iterator iter;

	// Find the weapon cell and remove it.
	for( iter = cells.begin(); iter != cells.end(); iter++ ) {
		if( *iter == w )
			cells.erase( iter );
	}
}

