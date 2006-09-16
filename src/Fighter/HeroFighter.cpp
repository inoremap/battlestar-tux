/* HeroFighter.cpp
 *
 * Copyright 2005-2006 Eliot Eshelman
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


#include "HeroFighter.h"
#include "Shield.h"
#include "../TextureManager.h"

HeroFighter::HeroFighter( HeroFighterType f, Game* g ) : Fighter( HEROS_FIGHTER, g ) {
	fighterType = f;
	texture = game->getTextureManager()->loadTexture( "data/gfx/fighter_0001-64.png" );

	stayOnScreen = true;

	switch( fighterType ) {
		case BASIC_FIGHTER:
		default:
			size[0] = 6;
			size[1] = 6;
			health = healthFull = 10000;
			shield = new Shield( this, 50000, game );
			float offsets[3][2] = {
				{ 0.0, 3.0 },
				{ -1.0, 1.0 },
				{ 1.0, 1.0 }
			};
			weaponSystem = new WeaponSystem( BASIC_FIGHTER_MOUNTS, offsets, this, g );
			Laser* primary = new Laser( weaponSystem, game );
			Plasma* left = new Plasma( weaponSystem, game );
			Plasma* right = new Plasma( weaponSystem, game );
			Turret* turret = new Turret( weaponSystem, game );
			turret->Equip( primary );
			weaponSystem->Equip( turret, PRIMARY_WEAPON );
			turret = new Turret( weaponSystem, game );
			turret->Equip( left );
			weaponSystem->Equip( turret, SECONDARY_WEAPON_L );
			turret = new Turret( weaponSystem, game );
			turret->Equip( right );
			weaponSystem->Equip( turret, SECONDARY_WEAPON_R );
			break;
	}
}


HeroFighter::~HeroFighter() {
	game->getTextureManager()->freeTextures( 1, &texture );
}


void HeroFighter::Draw() {
	weaponSystem->Draw();
	Fighter::Draw();
}


int HeroFighter::getFighterType() { return fighterType; }
