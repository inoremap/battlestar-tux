/* Turret.cpp
 *
 * Copyright 2006 Eliot Eshelman
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

#include "Turret.h"
#include "../../FighterAmmo.h"

Turret::Turret( WeaponSystem* w, Game* g ) : Weapon( w, g ) {
	heading = 0.0;
	weapon = NULL;

	mount = PRIMARY_WEAPON | SECONDARY_WEAPON_L | SECONDARY_WEAPON_R | UNDERBELLY_WEAPON_F | UNDERBELLY_WEAPON_R;
	velocity = 0.0;
}


bool Turret::Equip( Weapon* w ) {
	if( ! weapon ) {
		weapon = w;
		velocity = weapon->getVelocity();
		return true;
	}
	else
		return false;
}


bool Turret::UnEquip() {
	if( weapon ) {
		weapon = NULL;
		velocity = 0.0;
		return true;
	}
	else
		return false;
}


// OpenGL Rotations are counter-clockwise.
void Turret::RotateCW() { heading -= 1; }
void Turret::RotateCCW() { heading += 1; }
void Turret::SetTarget( float angle ) { heading = angle; }


FighterAmmo* Turret::NewAmmo() {
	FighterAmmo* ammo = weapon->NewAmmo();
	float* fighterVel = weaponSystem->getVel();

	// Update rotation of ammo to include turret rotation.
	float fighterRot = weaponSystem->getRot() + heading;
	ammo->setRot( fighterRot );

	// Update heading of ammo to include turret rotation.
	// OpenGL Rotations are counter-clockwise.
	float velx = 0.0;
	float vely = 0.0;
	velx = -sinf( fighterRot * (M_PI/180) ) * velocity;
	vely = cosf( fighterRot * (M_PI/180) ) * velocity;
	ammo->setVel( velx + fighterVel[0], vely + fighterVel[1], 0.0 );

	return ammo;
}


bool Turret::Recharged() {
	if( weapon )
		return weapon->Recharged();
	else
		return false;
}


char* Turret::getName() { return "::Turret::"; }
