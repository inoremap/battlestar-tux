/* HexCellList.cpp
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


#include "HexCell.h"
#include "HexCellList.h"

HexCellList::HexCellList( Game* g ) : ObjectList( g ) {}


HexCellList::~HexCellList() {
}


void HexCellList::DrawObjects() {
	HexCell* cur = (HexCell*) rootObj;

	while( cur ) {
		glPushMatrix();
		// The matrices have already been transformed for
		// the position of the fighter - we just need to
		// translate to the position of this cell in the fighter.
		vec2 translation = cur->getCellPosition();
		glTranslatef( translation[0], translation[1], 0 );
		cur->Draw();
		glPopMatrix();

		cur = (HexCell*) cur->getNext();
	}
}

