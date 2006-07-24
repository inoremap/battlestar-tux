/* Weapon.cpp
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

#include "Weapon.h"
#include "Fighter.h"
#include "../FighterAmmo.h"

Weapon::Weapon( WeaponSystem* w, Game* g ) {
	weaponSystem = w;
	align = w->getAlign();
	game = g;

	firing = false;

	mount = PRIMARY_WEAPON;

	type = LASER;

	rechargeTime = 10.0;
	chargingTime = 0.0;

	velocity = 1.0;

	damage = 100.0;
	penetration = 0.0;

	offset = new float[2];
	offset[0] = 0.0;
	offset[1] = 0.0;
}


Weapon::~Weapon() {
	delete[] offset;
}


void Weapon::Charge() { chargingTime = rechargeTime; }


bool Weapon::Recharged() {
	// Still charging from last shot.
	if( chargingTime ) {
		if( game->getGameSpeed() == 1 ) {
			chargingTime -= 1;
			return false;
		}

		// Frames were skipped, the weapon may have finished recharging
		// during one of the skipped frames.
		else if( chargingTime > game->getGameSpeed() ) {
			chargingTime -= game->getGameSpeed();
			return false;
		}

		else
			chargingTime = 0;
	}

	return true;
}


FighterAmmo* Weapon::NewAmmo() {
	FighterAmmo* ammo = new FighterAmmo( type, damage, penetration, game->getHeroAmmoList()->getTexture(type), game );
	float* fighterPos = weaponSystem->getPos();
	float* fighterVel = weaponSystem->getVel();
	float fighterRot = weaponSystem->getRot();

	// Set position of ammo - offset depends on rotation of fighter.
	// OpenGL Rotations are counter-clockwise.
	float angle = 0.0;
	float length = 0.0;
	float offsetx = 0.0;
	float offsety = 0.0;
	if( offset[0] != 0 ) {
		angle = -atanf( offset[1] / offset[0] ) * (180/M_PI);
		length = sqrtf( offset[0]*offset[0] + offset[1]*offset[1] );
	}
	else {
		if( offset[1] > 0 )
			angle = 0;
		else
			angle = 180;
		length = offset[1];
	}
	offsetx = -sinf( (fighterRot + angle) * (M_PI/180) ) * length;
	offsety = cosf( (fighterRot + angle) * (M_PI/180) ) * length;
	ammo->setPos( offsetx + fighterPos[0], offsety + fighterPos[1] );

	// Set rotation of ammo.
	ammo->setRot( fighterRot );

	// Set velocity of ammo - heading depends on rotation of fighter.
	// OpenGL Rotations are counter-clockwise.
	float velx = 0.0;
	float vely = 0.0;
	velx = -sinf( fighterRot * (M_PI/180) ) * velocity;
	vely = cosf( fighterRot * (M_PI/180) ) * velocity;
	ammo->setVel( velx + fighterVel[0], vely + fighterVel[1], 0.0 );

	// Specify a hero or enemy ammo.
	if( align == HEROS_FIGHTER )
		ammo->setType( HEROS_AMMO );
	else
		ammo->setType( ENEMY_AMMO );

	return ammo;
}


void Weapon::Update() {
	if( ! Recharged() )
		return;

	if( firing ) {
		// Create ammo object and add to the list of ammo.
		if( align == HEROS_FIGHTER )
			game->getHeroAmmoList()->addObject( NewAmmo() );
		else
			game->getEnemyAmmoList()->addObject( NewAmmo() );

		// Weapon will need to recharge.
		Charge();
	}
}


void Weapon::Fire( bool f ) { firing = f; }


void Weapon::setOffset( float o[] ) {
	offset[0] = o[0];
	offset[1] = o[1];
}


int Weapon::getMount() { return mount; }
float Weapon::getVelocity() { return velocity; }
float Weapon::getDamage() { return damage; }
float Weapon::getPenetration() { return penetration; }
char* Weapon::getName() { return "::Weapon::"; }
