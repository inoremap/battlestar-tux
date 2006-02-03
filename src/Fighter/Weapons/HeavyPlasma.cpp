/* HeavyPlasma.cpp
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


#include "HeavyPlasma.h"
#include "../../FighterAmmo.h"

HeavyPlasma::HeavyPlasma( WeaponSystem* w, Game* g ) : Weapon( w, g ) {
	mount = PRIMARY_WEAPON;

	type = HEAVY_PLASMA;

	rechargeTime = 50.0;

	velocity = 0.3;
	damage = 800.0;
	penetration = 0.0;
}

char* HeavyPlasma::getName() { return "Heavy Plasma"; }
