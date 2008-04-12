/* WeaponSystem.h
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


#ifndef WEAPONSYSTEM_H_
#define WEAPONSYSTEM_H_

#include <vector>

#include "Displayable.h"
#include "Fighter.h"
#include "Game.h"

class WeaponCell;


/* Each fighter has a weapon system to handle targetting and weapons fire.
 * All weapons are controlled from here, and all targets are stored and
 * tracked here.
 */
class WeaponSystem : public Displayable {
	public:
				WeaponSystem( Fighter* );
				~WeaponSystem();

				void Update( int );

				void Draw();

				void FirePrimary( bool );
				void FireSecondary( bool );

				void addPrimaryWeapon( WeaponCell* );
				void addSecondaryWeapon( WeaponCell* );
				void remPrimaryWeapon( WeaponCell* );
				void remSecondaryWeapon( WeaponCell* );

				inline void setTarget( vec3 target ) { pos = target; }
				inline const vec3 getTarget() { return pos; }

				inline void setFireAll( bool a ) { fireAll = a; }
				inline const bool getFireAll() { return fireAll; } 

	private:
				WeaponSystem( const WeaponSystem & );
				const WeaponSystem & operator= ( const WeaponSystem & );

				void addWeapon( std::vector<WeaponCell*> &, WeaponCell* );
				void remWeapon( std::vector<WeaponCell*> &, WeaponCell* );

				// All weapons will attempt to target the location of this object.
				// The vec3 pos holds the position of the object.

				// Fire all weapons, even when the desired target is out of range.
				bool fireAll;

				// Primary weapons are currently firing
				bool primaryFiring;

				// Secondary weapons are currently firing
				bool secondaryFiring;

				// List of weapons in primary group.
				std::vector<WeaponCell*> primaryWeapons;

				// List of weapons in secondary group.
				std::vector<WeaponCell*> secondaryWeapons;

				// The fighter that uses this weapon system.
				Fighter* fighter;

				Game* game;

				GLuint texture;
};


#endif /*WEAPONSYSTEM_H_*/
