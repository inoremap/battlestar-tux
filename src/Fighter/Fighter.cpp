/* Fighter.cpp
 *
 * Copyright 2005-2007 Eliot Eshelman
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


#include "ArmorCell.h"
#include "Fighter.h"
#include "Vector.h"

Fighter::Fighter( FighterAlignment a, Game* g ) : Object( FIGHTER ) {
	game = g;

	torque[1] = 1;

	pos[2] = 3;

	allCells = new HexCellList( game );
	generationCells = new HexCellList( game );
	storageCells = new HexCellList( game );
	captureCells = new HexCellList( game );
	propulsionCells = new HexCellList( game );
	shieldCells = new HexCellList( game );
	weaponCells = new HexCellList( game );

	ivec2 cellPos = ivec2();
	coreCell = new CoreCell( this, cellPos );
	coreCell->setFullHealth( 10000 );
	coreCell->setHealth( 10000 );
	coreCell->setMass( 1000 );
	allCells->addObject( coreCell );

	cellPos = ivec2( 1, 0 );
	ArmorCell* cell = new ArmorCell( this, cellPos );
	cell->setFullHealth( 1000 );
	cell->setHealth( 1000 );
	cell->setMass( 250 );
	allCells->addObject( cell );

	cellPos = ivec2( 0, 1 );
	cell = new ArmorCell( this, cellPos );
	cell->setFullHealth( 1000 );
	cell->setHealth( 1000 );
	cell->setMass( 250 );
	allCells->addObject( cell );

	cellPos = ivec2( -1, 0 );
	cell = new ArmorCell( this, cellPos );
	cell->setFullHealth( 1000 );
	cell->setHealth( 1000 );
	cell->setMass( 250 );
	allCells->addObject( cell );

	cellPos = ivec2( -1, -1 );
	cell = new ArmorCell( this, cellPos );
	cell->setFullHealth( 1000 );
	cell->setHealth( 1000 );
	cell->setMass( 250 );
	allCells->addObject( cell );

	cellPos = ivec2( 0, -1 );
	cell = new ArmorCell( this, cellPos );
	cell->setFullHealth( 1000 );
	cell->setHealth( 1000 );
	cell->setMass( 250 );
	allCells->addObject( cell );

	cellPos = ivec2( 1, -1 );
	cell = new ArmorCell( this, cellPos );
	cell->setFullHealth( 1000 );
	cell->setHealth( 1000 );
	cell->setMass( 250 );
	allCells->addObject( cell );

	align = a;
}


Fighter::~Fighter() {
	// Delete all fighter cells.
	HexCell* cur = (HexCell*) allCells->getRoot();
	HexCell* next = 0;
	while( cur ) {
		next = (HexCell*) cur->getNext();
		delete cur;
		cur = next;
	}

	delete allCells;
	delete generationCells;
	delete storageCells;
	delete captureCells;
	delete propulsionCells;
	delete shieldCells;
	delete weaponCells;
}


void Fighter::Update( int speed ) {
	Object::Update( speed );

	allCells->UpdateObjects();
}


void Fighter::Draw() {
	glPushMatrix();

	// Apply fighter position transformations.
	Object::Draw();

	// Draw all cells.
	HexCell* cur = (HexCell*) allCells->getRoot();
	HexCell* next = 0;
	while( cur ) {
		next = (HexCell*) cur->getNext();

		glPushMatrix();
		// The matrices have already been transformed for
		// the position of the fighter - we just need to
		// translate to the position of this cell in the fighter.
		vec2 translation = cur->getCellPosition();
		glTranslatef( translation[0], translation[1], 0 );
		cur->Draw();
		glPopMatrix();

		cur = next;
	}

	glPopMatrix();
}


void Fighter::startFiring() { 
	//weaponSystem->Fire( true );
}
void Fighter::stopFiring() {
	//weaponSystem->Fire( false );
}


float Fighter::getHealth() { return coreCell->getHealth(); }
float Fighter::getFullHealth() { return coreCell->getFullHealth(); }


void Fighter::destroyCell( HexCell* cell ) {
	switch( cell->getCellType() ) {
		// The whole ship has been destroyed when this cell goes...
		case CORE_CELL:
			break;

		// These components can be destroyed without losing the ship.
		case GENERATION_CELL:
			generationCells->remObject( cell );
			break;
		case STORAGE_CELL:
			storageCells->remObject( cell );
			break;
		case CAPTURE_CELL:
			captureCells->remObject( cell );
			break;
		case PROPULSION_CELL:
			propulsionCells->remObject( cell );
			break;
		case SHIELD_CELL:
			shieldCells->remObject( cell );
			break;
		case WEAPON_CELL:
			weaponCells->remObject( cell );
			break;
	}

	allCells->remObject( cell );

	delete cell;
}


int Fighter::getAlignment() { return align; }
