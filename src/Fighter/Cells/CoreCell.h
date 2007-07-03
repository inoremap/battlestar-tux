/* CoreCell.h
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


#ifndef CORECELL_H_
#define CORECELL_H_

#include "HexCell.h"


// Central cell of the fighter.  All is lost when this cell is destroyed.
class CoreCell : public HexCell {
	public:
				CoreCell( Fighter*, TextureManager*, const ivec2 & );
				~CoreCell();

				void Update( int );

				void Draw();


	private:
				CoreCell( const CoreCell & );
				const CoreCell & operator= ( const CoreCell & );
};


#endif /*CORECELL_H_*/
