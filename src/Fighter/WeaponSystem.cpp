/* WeaponSystem.cpp
 *
 * Copyright 2005-2006 Eliot Eshelman
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


#include "Fighter.h"
#include "TextureManager.h"
#include "Weapon.h"
#include "WeaponSystem.h"

WeaponSystem::WeaponSystem( int allMounts, float allOffsets[][2], Fighter* f, Game* g ) {
	mount_points = allMounts;
	fighter = f;
	game = g;

	// Determine number of mounts.
	numMounts = 0;
	for( int i=0, n=1; i < 8; i++ ) {
		if( n & mount_points )
			numMounts++;
		n *= 2;
	}

	mountTypes = new WeaponMount[numMounts];
	weapons = new Weapon*[numMounts];
	offsets = new float*[numMounts];

	// Set mount offsets.
	for( int i=0; i < numMounts; i++ ) {
		weapons[i] = 0;

		offsets[i] = new float[2];
		offsets[i][0] = allOffsets[i][0];
		offsets[i][1] = allOffsets[i][1];
	}

	// Set each type of mount.
	for( int i=0, n=1, j=0; i < 8; i++ ) {
		if( n & mount_points ) {
			mountTypes[j] = (WeaponMount) n;
			j++;
		}
		n *= 2;
	}

	targetHeading = 0.0;

	texture = game->getTextureManager()->loadTexture( "data/gfx/crosshairs_0001-32.png" );
}


WeaponSystem::~WeaponSystem() {
	delete[] mountTypes;
	delete[] weapons;

	for( int i=0; i < numMounts; i++ )
		delete[] offsets[i];
	delete[] offsets;
}


void WeaponSystem::Update() {
	for( int i=0; i < numMounts; i++ ) {
		if( weapons[i] )
			weapons[i]->Update();
	}
}


void WeaponSystem::Draw() {
	glPushMatrix();

	float mx = 1.2;
	float my = 1.2;
	float* pos = fighter->getPos();

	glTranslatef( pos[0], pos[1], pos[2] );
	glRotatef( targetHeading, 0.0, 0.0, 1.0 );
	glTranslatef( 0.0, 10.0, 0.0 );

	// Why does this need to be flipped vertically?
	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin( GL_TRIANGLE_STRIP );
		glColor4f( 1.0, 1.0, 1.0, 0.5 );
		glTexCoord2f( 0, 0 );
		glVertex3f( -mx, my, 0.0 );
		glTexCoord2f( 0, 1 );
		glVertex3f( -mx, -my, 0.0 );
		glTexCoord2f( 1, 0 );
		glVertex3f( mx, my, 0.0 );
		glTexCoord2f( 1, 1 );
		glVertex3f( mx, -my, 0.0 );
	glEnd();

	glPopMatrix();
}


void WeaponSystem::Fire( bool firing ) {
	for( int i=0; i < numMounts; i++ ) {
		if( weapons[i] )
			weapons[i]->Fire( firing );
	}
}


bool WeaponSystem::Equip( Weapon* weapon, WeaponMount point ) {
	// Ensure weapon can be mounted at this point.
	if( (weapon->getMount() & point) == 0 ) {
		std::cout	<< "Unable to mount weapon (" << weapon->getMount() << ") on this mount point ("
					<< point << "): " << (weapon->getMount() & point) << ".\n";
		return false;
	}

	for( int i=0; i < numMounts; i++ ) {
		// Find WeaponMount point.
		if( mountTypes[i] == point ) {
			// A weapon is already equiped here.
			if( weapons[i] ) {
				std::cout << "There is already a weapon mounted here.\n";
				return false;
			}
			// Equip the weapon.
			else {
				weapons[i] = weapon;
				weapon->setOffset( offsets[i] );
				return true;
			}
		}
	}

	return false;
}


bool WeaponSystem::UnEquip( Weapon* weapon ) {
	for( int i=0; i < numMounts; i++ ) {
		// Find Weapon.
		if( weapons[i] == weapon ) {
			// UnEquip weapon
			weapons[i] = 0;
			return true;
		}
	}

	return false;
}


void WeaponSystem::SetTarget( float angle ) { targetHeading = angle; }


// OpenGL rotations are counter-clockwise.
void WeaponSystem::TargetCW() { targetHeading -= 1; }
void WeaponSystem::TargetCCW() { targetHeading += 1; }


int WeaponSystem::getMounts() { return mount_points; }
float WeaponSystem::getTarget() { return targetHeading; }
float* WeaponSystem::getPos() { return fighter->getPos(); }
float* WeaponSystem::getVel() { return fighter->getVel(); }
float WeaponSystem::getRot() { return fighter->getRot(); }
int WeaponSystem::getAlign() { return fighter->getAlignment(); }


bool WeaponSystem::equipable( int weapon ) {
	// This system can equip weapon.
	if( weapon & mount_points )
		return true;
	// This system can't equip weapon.
	else
		return false;
}

