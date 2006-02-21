/* Fighter.h
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


#ifndef FIGHTER_H_
#define FIGHTER_H_

#include "SDL_opengl.h"

#include "../Displayable.h"
#include "../Game.h"
#include "Shield.h"
#include "Weapon.h"
#include "WeaponSystem.h"
#include "Weapons/LightLaser.h"
#include "Weapons/MediumLaser.h"
#include "Weapons/HeavyLaser.h"
#include "Weapons/LightPlasma.h"
#include "Weapons/MediumPlasma.h"
#include "Weapons/HeavyPlasma.h"


enum FighterAlignment {
	HEROS_FIGHTER,		// Fighter flown by player
	ENEMY_FIGHTER		// Enemy fighter
};

enum FighterWeaponMounts {
	BASIC_FIGHTER_MOUNTS		= PRIMARY_WEAPON | SECONDARY_WEAPON_L | SECONDARY_WEAPON_R
};


/* A fighter aircraft. */
class Fighter : public Displayable {
	public:
				Fighter( FighterAlignment a, Game* g );
				virtual ~Fighter();

				void Draw();

				// Update fighter systems.
				void Update();

				// Weapons begin firing.
				void startFiring();

				// Weapons cease firing.
				void stopFiring();

				// Do 'damage' amount of damage to ship.
				void damage( float damage );

				float getHealth();
				float getHealthFull();
				Shield* getShield();
				float getShields();
				float getShieldsFull();
				int getAlignment();

	protected:
				// Constant Z position of the fighter.
				static const float zPos = -1.5;

				// Remaining ship armor
				float health;

				// Maximum ship armor
				float healthFull;

				// Is fighter currently firing?
				bool firing;

				Shield* shield;

				WeaponSystem* weaponSystem;

				FighterAlignment align;

				GLuint texture;

	private:
				Fighter( const Fighter &fighter );
				const Fighter & operator= ( const Fighter &fighter );
};


#endif /*FIGHTER_H_*/
