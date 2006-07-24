/* Turret.h
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


#ifndef TURRET_H_
#define TURRET_H_

#include "../Weapon.h"

/* Turret for mounting/targetting weapons. */
class Turret : public Weapon {
	public:
				Turret( WeaponSystem* w, Game* g );

				// Equip weapon in slot.
				bool Equip( Weapon* w );

				// UnEquip weapon from slot.
				bool UnEquip();

				// Charge the weapon - it was just fired.
				void Charge();

				// Is weapon recharged and ready to fire?
				bool Recharged();

				// Create a new ammo object.
				FighterAmmo* NewAmmo();

				// Update turret status.
				void Update();

				void setOffset( float o[] );

				virtual char* getName();

	private:
				Turret( const Turret &turret );
				const Turret & operator= ( const Turret &turret );

				// Current turret position.
				float turretHeading;

				// Tracking speed - how quickly the turret can lock on a target.
				float trackingSpeed;

				// Weapon mounted on turret.
				Weapon* weapon;
};


#endif /*TURRET_H_*/
