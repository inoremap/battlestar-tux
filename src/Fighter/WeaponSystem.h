/* WeaponSystem.h
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


#ifndef WEAPONSYSTEM_H_
#define WEAPONSYSTEM_H_

class Fighter;
class Weapon;


enum WeaponMount {
	PRIMARY_WEAPON			= 0x0001,
	SECONDARY_WEAPON_L		= 0x0002,
	SECONDARY_WEAPON_R		= 0x0004,
	UNDERBELLY_WEAPON_F		= 0x0008,
	UNDERBELLY_WEAPON_R		= 0x0010,
	WING_WEAPON_L			= 0x0020,
	WING_WEAPON_R			= 0x0040
};


/* Weapons systems on the fighter. */
class WeaponSystem {
	public:
				WeaponSystem( int allMounts, float allOffsets[][2], Fighter* f );
				~WeaponSystem();

				// Update system status.
				void Update();

				// Fire weapons.
				void Fire( bool firing );

				// Equip weapon in slot.
				bool Equip( Weapon* weapon, WeaponMount point );

				// UnEquip weapon from slot.
				bool UnEquip( Weapon* weapon );

				// Target a particular direction.
				void SetTarget( float angle );

				// Change target direction.
				void TargetCW();
				void TargetCCW();

				int getMounts();
				float getTarget();
				float* getPos();
				float* getVel();
				float getRot();
				int getAlign();
				bool equipable( int weapon );

	private:
				WeaponSystem( const WeaponSystem &system );
				const WeaponSystem & operator= ( const WeaponSystem &system );

				// Available weapon mounts on the system.
				int mount_points;

				// Weapon positions relative to the fighter.
				float** offsets;

				// Number of mounts on the system.
				int numMounts;

				// Types of mounts.
				WeaponMount* mountTypes;

				// Weapons mounted on the system.
				Weapon** weapons;

				// Current turret position.
				float targetHeading;

				// Fighter the weapon system is on.
				Fighter* fighter;
};


#endif /*WEAPONSYSTEM_H_*/
