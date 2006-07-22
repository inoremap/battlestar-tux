/* WeaponSystem.cpp
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


#include <stdio.h>

#include "WeaponSystem.h"
#include "Fighter.h"
#include "Weapon.h"

WeaponSystem::WeaponSystem( int allMounts, float allOffsets[][2], Fighter* f ) {
	mount_points = allMounts;
	fighter = f;

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
}


WeaponSystem::~WeaponSystem() {
	delete[] mountTypes;
	delete[] weapons;

	for( int i=0; i < numMounts; i++ )
		delete[] offsets[i];
	delete[] offsets;
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
		printf( "Unable to mount weapon (%i) on this mount point (%i): %i.\n", weapon->getMount(), point, weapon->getMount() & point );
		return false;
	}

	for( int i=0; i < numMounts; i++ ) {
		// Find WeaponMount point.
		if( mountTypes[i] == point ) {
			// A weapon is already equiped here.
			if( weapons[i] ) {
				printf( "There is already a weapon mounted here.\n" );
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


int WeaponSystem::getMounts() { return mount_points; }


float* WeaponSystem::getPos() { return fighter->getPos(); }


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

