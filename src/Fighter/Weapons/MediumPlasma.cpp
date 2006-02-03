/* MediumPlasma.cpp
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


#include "MediumPlasma.h"
#include "../../FighterAmmo.h"

MediumPlasma::MediumPlasma( WeaponSystem* w, Game* g ) : Weapon( w, g ) {
	mount = PRIMARY_WEAPON | SECONDARY_WEAPON_L | SECONDARY_WEAPON_R;

	type = MEDIUM_PLASMA;

	rechargeTime = 25.0;

	velocity = 0.5;
	damage = 300.0;
	penetration = 0.0;
}

char* MediumPlasma::getName() { return "Medium Plasma"; }
