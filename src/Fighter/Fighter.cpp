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


#include "Fighter.h"
#include "Vector.h"

Fighter::Fighter( FighterAlignment a, Game* g ) : Object( FIGHTER ) {
	game = g;

	allCells = new HexCellList( game );
	storageCells = new HexCellList( game );
	generationCells = new HexCellList( game );
	shieldCells = new HexCellList( game );
	weaponCells = new HexCellList( game );
	propulsionCells = new HexCellList( game );

	vec2 pos = vec2();
	coreCell = new CoreCell( this, pos );
	coreCell->setFullHealth( 10000 );
	coreCell->setHealth( 10000 );
	coreCell->setMass( 1000 );
	allCells->addObject( coreCell );

	align = a;
}


Fighter::~Fighter() {}


void Fighter::Draw() {
	allCells->DrawObjects();
}


void Fighter::Update() {
	//weaponSystem->Update();

	allCells->UpdateObjects();
}


void Fighter::startFiring() { 
	//weaponSystem->Fire( true );
}
void Fighter::stopFiring() {
	//weaponSystem->Fire( false );
}


float Fighter::getHealth() { return coreCell->getHealth(); }
float Fighter::getFullHealth() { return coreCell->getFullHealth(); }

int Fighter::getAlignment() { return align; }
