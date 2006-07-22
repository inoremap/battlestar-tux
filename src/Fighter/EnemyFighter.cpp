/* EnemyFighter.cpp
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


#include "EnemyFighter.h"

EnemyFighter::EnemyFighter( EnemyFighterType f, EnemyFighterList* l, Game* g ) : Fighter( ENEMY_FIGHTER, g ) {
	fighterType = f;
	texture = l->getTexture( fighterType );

	switch( fighterType ) {
		case BASIC_ENEMY_FIGHTER:
		default:
			size[0] = 4;
			size[1] = 4;
			health = healthFull = 1000;
			float offsets[3][2] = {
				{ 0.0, 0.0 },
				{ -0.75, 1.0 },
				{ 0.75, 1.0 }
			};
			weaponSystem = new WeaponSystem( BASIC_FIGHTER_MOUNTS, offsets, this );
			Laser* primary = new Laser( weaponSystem, game );
			Plasma* left = new Plasma( weaponSystem, game );
			Plasma* right = new Plasma( weaponSystem, game );
			weaponSystem->Equip( primary, PRIMARY_WEAPON );
			weaponSystem->Equip( left, SECONDARY_WEAPON_L );
			weaponSystem->Equip( right, SECONDARY_WEAPON_R );
			break;
	}
}


EnemyFighter::~EnemyFighter() {}


int EnemyFighter::getFighterType() { return fighterType; }
