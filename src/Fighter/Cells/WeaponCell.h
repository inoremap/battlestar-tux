/* WeaponCell.h
 *
 * Copyright 2007 Eliot Eshelman
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


#ifndef WEAPONCELL_H_
#define WEAPONCELL_H_

#include "HexCell.h"
#include "Vector.h"


// Creates projectiles to damage other units.
class WeaponCell : public HexCell {
	public:
				WeaponCell( Fighter*, Game*, const ivec2 & );
				~WeaponCell();

				void Update( int );

				void Draw();

	private:
				WeaponCell( const WeaponCell & );
				const WeaponCell & operator= ( const WeaponCell & );

				GLuint texture;
};


#endif /*WEAPONCELL_H_*/
