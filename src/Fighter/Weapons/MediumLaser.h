/* MediumLaser.h
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


#ifndef MEDIUMLASER_H_
#define MEDIUMLASER_H_

#include "../../Game.h"
#include "../../FighterAmmoList.h"
#include "../Weapon.h"
#include "../WeaponSystem.h"

/* Medium laser weapon. */
class MediumLaser : public Weapon {
	public:
				MediumLaser( WeaponSystem* w, Game* g );

				char* getName();

	private:
				MediumLaser( const MediumLaser &laser );
				const MediumLaser & operator= ( const MediumLaser &laser );
};


#endif /*MEDIUMLASER_H_*/
