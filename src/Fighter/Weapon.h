/* Weapon.h
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


#ifndef WEAPON_H_
#define WEAPON_H_

#include <string>

#include "../Game.h"
#include "../FighterAmmoList.h"
#include "WeaponSystem.h"


/* Fighter weapon. */
class Weapon {
	public:
				Weapon( WeaponSystem* w, Game* g );
				virtual ~Weapon();

				// Charge the weapon - it was just fired.
				virtual void Charge();

				// Is weapon recharged and ready to fire?
				virtual bool Recharged();

				// Create a new ammo object.
				virtual FighterAmmo* NewAmmo();

				// Update weapon status.
				virtual void Update();

				// Fire weapon.
				virtual void Fire( bool f );

				virtual void setOffset( float o[] );

				int getMount();
				float getVelocity();
				float getDamage();
				float getPenetration();
				virtual std::string getName();

	protected:
				Weapon( const Weapon &weapon );
				const Weapon & operator= ( const Weapon &weapon );

				// Is weapon firing?
				bool firing;

				// Where the weapon can be mounted.
				int mount;

				// Required recharge time between shots.
				float rechargeTime;

				// Time before another shot may be fired.
				float chargingTime;

				// Type of ammo fired by the weapon.
				FighterAmmoType type;

				// Maximum velocity of a piece of ammo.
				float velocity;

				// Amount of damage dealt by one piece of ammo.
				float damage;

				// Amount of penetration by one piece of ammo.
				// Penetration varies from 0.0 to 1.0;
				// 0.0 means the ammo stops after the first collision.
				// 1.0 means the ammo will pass through any object with resistance less than 1.0.
				float penetration;

				// Position of weapon relative to fighter position.
				float* offset;

				// Is weapon mounted on player's or enemy's ship?
				int align;

				// Weapon system controlling the weapon.
				WeaponSystem* weaponSystem;

				Game* game;
};


#endif /*WEAPON_H_*/
