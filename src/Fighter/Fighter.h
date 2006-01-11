/* Fighter.h
 *
 * Copyright 2005 Eliot Eshelman
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


#ifndef FIGHTER_H_
#define FIGHTER_H_

#include "SDL_opengl.h"

#include "../Displayable.h"
#include "../Game.h"
#include "Weapon.h"
#include "WeaponSystem.h"


enum FighterType {
	BASIC_FIGHTER		// Default fighter
};


enum FighterWeaponMounts {
	BASIC_FIGHTER_MOUNTS		= PRIMARY_WEAPON | SECONDARY_WEAPON_L | SECONDARY_WEAPON_R
};


/* The fighter ship controlled by the player. */
class Fighter : public Displayable {
	public:
				Fighter( FighterType f, Game* g );
				~Fighter();

				void Draw();

				// Update fighter systems.
				void Update();

				// Weapons begin firing.
				void startFiring();

				// Weapons cease firing.
				void stopFiring();

				void damage( float damage );
				float getHealth();
				float getHealthFull();
				float getShields();
				float getShieldsFull();

	private:
				// Constant Z position of the fighter.
				static const float zPos = -1.5;

				// Remaining ship armor
				float health;

				// Maximum ship armor
				float healthFull;

				// Remaining shield strength
				float shields;

				// Maximum shield strength
				float shieldsFull;

				// Is fighter currently firing?
				bool firing;

				WeaponSystem* weaponSystem;

				FighterType type;

				GLuint texture;
};


#endif /*FIGHTER_H_*/
