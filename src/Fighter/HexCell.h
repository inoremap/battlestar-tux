/* HexCell.h
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


#ifndef HEXCELL_H_
#define HEXCELL_H_

#include "IntegerVector.h"
#include "Object.h"
#include "Vector.h"

class Fighter;

// Different possible cell functions.
enum HexCellType {
	CORE_CELL,			// Central unit in the fighter
	ARMOR_CELL,			// Protective armor on the hull
	GENERATION_CELL,	// Energy generation
	STORAGE_CELL,		// Energy storage
	CAPTURE_CELL,		// Energy capture/attraction
	PROPULSION_CELL,	// Propulsion of the fighter
	SHIELD_CELL,		// Shield generator
	WEAPON_CELL			// Weaponry
};


// Each fighter is composed of these cell units.
class HexCell : public Object {
	public:
				HexCell( Fighter*, HexCellType, const ivec2 & );
				virtual ~HexCell();

				virtual void Update( int );

				virtual void Draw();

				void destroy();

				ivec2 getCellOffset();
				vec2 getCellPosition();
				HexCellType getCellType();

	protected:
				// Draw the hexagon.
				void drawHex( float, float, float );

				// The offset of the cell inside the ship structure.
				// This assumes a unit size of one cell.
				ivec2 cellOffset;

				// The position of the cell inside the ship structure.
				// This is where the cell will actually be drawn.
				vec2 cellPosition;

				// What is the purpose of this cell?
				HexCellType cellType;

				// The fighter that this cell belongs to.
				Fighter* fighter;

	private:
				HexCell( const HexCell & );
				const HexCell & operator= ( const HexCell & );
};


// Standard sizes for hex cell.
static const float HEX_CELL_SIZE[3] = {
	0.5,	// Inner width
	0.65,	// Outer width
	0.2		// Height
};


// Points on a unit hexagon (x, y).
static const float HEX_VERTS[6][2] = {
	{ -1.0, 0.0 },
	{ -0.5, 0.866025404 },
	{ 0.5, 0.866025404 },
	{ 1.0, 0.0 },
	{ 0.5, -0.866025404 },
	{ -0.5, -0.866025404 }
};


#endif /*HEXCELL_H_*/
