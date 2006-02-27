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


#include "Weapon.h"
#include "Fighter.h"
#include "../FighterAmmo.h"

Weapon::Weapon( WeaponSystem* w, Game* g ) {
	weaponSystem = w;
	align = w->getAlign();
	game = g;

	mount = PRIMARY_WEAPON;

	type = LIGHT_LASER;

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


void Weapon::Fire( bool firing ) {
	if( ! Recharged() )
		return;

	if( firing ) {
		// Create ammo object and add to the list of ammo.
		FighterAmmo* ammo;
		if( align == HEROS_FIGHTER )  {
			ammo = new FighterAmmo( type, damage, penetration, game->getHeroAmmoList()->getTexture(type), game );
			ammo->setType( HEROS_AMMO );

			float* fighterPos = weaponSystem->getPos();
			ammo->setPos( offset[0] + fighterPos[0], offset[1] + fighterPos[1] );
			ammo->setVel( 0.0, velocity, 0.0 );

			game->getHeroAmmoList()->addObject( ammo );
		}
		else {
			ammo = new FighterAmmo( type, damage, penetration, game->getEnemyAmmoList()->getTexture(type), game );
			ammo->setType( ENEMY_AMMO );

			float* fighterPos = weaponSystem->getPos();
			ammo->setPos( offset[0] + fighterPos[0], offset[1] + fighterPos[1] );
			ammo->setVel( 0.0, -velocity, 0.0 );

			game->getEnemyAmmoList()->addObject( ammo );
		}

		// Weapon will need to recharge.
		chargingTime = rechargeTime;
	}
}


void Weapon::setOffset( float o[] ) {
	offset[0] = o[0];
	offset[1] = o[1];
}


int Weapon::getMount() { return mount; }
float Weapon::getDamage() { return damage; }
float Weapon::getPenetration() { return penetration; }
char* Weapon::getName() { return "::Weapon::"; }
