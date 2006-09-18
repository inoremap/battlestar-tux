/* Laser.h
 *
 * Copyright 2005 Eliot Eshelman
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


#ifndef LASER_H_
#define LASER_H_

#include <string>

#include "FighterAmmoList.h"
#include "Game.h"
#include "Weapon.h"
#include "WeaponSystem.h"

/* Laser weapon. */
class Laser : public Weapon {
	public:
				Laser( WeaponSystem* w, Game* g );

				std::string getName();

	private:
				Laser( const Laser &laser );
				const Laser & operator= ( const Laser &laser );
};


#endif /*LASER_H_*/
