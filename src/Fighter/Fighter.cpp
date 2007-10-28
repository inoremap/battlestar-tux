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
#include "GenerationCell.h"
#include "PropulsionCell.h"
#include "StorageCell.h"
#include "Vector.h"
#include "WeaponSystem.h"


Fighter::Fighter( FighterAlignment a, Game* g ) : Object( FIGHTER ) {
	game = g;

	pos[2] = 3;

	weaponSystem = new WeaponSystem( this, game );

	allCells = new HexCellList( game );

	ivec2 cellPos = ivec2();
	coreCell = new CoreCell( this, game, cellPos );
	coreCell->setFullHealth( 10000 );
	coreCell->setHealth( 10000 );
	coreCell->setMass( 100000 );
	allCells->addObject( coreCell );

	cellPos = ivec2( 1, 0 );
	ArmorCell* armorCell = new ArmorCell( this, game, cellPos );
	armorCell->setFullHealth( 1000 );
	armorCell->setHealth( 1000 );
	armorCell->setMass( 2500 );
	allCells->addObject( armorCell );

	cellPos = ivec2( 0, 1 );
	armorCell = new ArmorCell( this, game, cellPos );
	armorCell->setFullHealth( 1000 );
	armorCell->setHealth( 1000 );
	armorCell->setMass( 2500 );
	allCells->addObject( armorCell );

	cellPos = ivec2( -1, 0 );
	armorCell = new ArmorCell( this, game, cellPos );
	armorCell->setFullHealth( 1000 );
	armorCell->setHealth( 1000 );
	armorCell->setMass( 2500 );
	allCells->addObject( armorCell );

	cellPos = ivec2( -1, -1 );
	armorCell = new ArmorCell( this, game, cellPos );
	armorCell->setFullHealth( 1000 );
	armorCell->setHealth( 1000 );
	armorCell->setMass( 2500 );
	allCells->addObject( armorCell );

	cellPos = ivec2( 0, -1 );
	armorCell = new ArmorCell( this, game, cellPos );
	armorCell->setFullHealth( 1000 );
	armorCell->setHealth( 1000 );
	armorCell->setMass( 2500 );
	allCells->addObject( armorCell );

	cellPos = ivec2( 1, -1 );
	armorCell = new ArmorCell( this, game, cellPos );
	armorCell->setFullHealth( 1000 );
	armorCell->setHealth( 1000 );
	armorCell->setMass( 2500 );
	allCells->addObject( armorCell );

	cellPos = ivec2( 0, -2 );
	GenerationCell* generationCell = new GenerationCell( this, game, cellPos );
	generationCell->setFullHealth( 200 );
	generationCell->setHealth( 200 );
	generationCell->setMass( 1500 );
	generationCell->setGenerationRate( 555 );
	allCells->addObject( generationCell );

	cellPos = ivec2( -1, -2 );
	StorageCell* storageCell = new StorageCell( this, game, cellPos );
	storageCell->setFullHealth( 300 );
	storageCell->setHealth( 300 );
	storageCell->setMass( 2000 );
	storageCell->setMaxEnergy( 25000 );
	allCells->addObject( storageCell );

	cellPos = ivec2( 1, -2 );
	storageCell = new StorageCell( this, game, cellPos );
	storageCell->setFullHealth( 300 );
	storageCell->setHealth( 300 );
	storageCell->setMass( 2000 );
	storageCell->setMaxEnergy( 25000 );
	allCells->addObject( storageCell );

	cellPos = ivec2( -2, -1 );
	PropulsionCell* propulsionCell = new PropulsionCell( this, game, cellPos );
	propulsionCell->setFullHealth( 500 );
	propulsionCell->setHealth( 500 );
	propulsionCell->setMass( 3000 );
	propulsionCell->setAccelerationRate( 50 );
	propulsionCell->setPowerRate( 250 );
	allCells->addObject( propulsionCell );

	cellPos = ivec2( 2, -1 );
	propulsionCell = new PropulsionCell( this, game, cellPos );
	propulsionCell->setFullHealth( 500 );
	propulsionCell->setHealth( 500 );
	propulsionCell->setMass( 3000 );
	propulsionCell->setAccelerationRate( 50 );
	propulsionCell->setPowerRate( 250 );
	allCells->addObject( propulsionCell );

	align = a;
}


Fighter::~Fighter() {
	delete allCells;
}


void Fighter::Update( int speed ) {
	Object::Update( speed );
	weaponSystem->Update( speed );
	allCells->UpdateObjects();

	// Move any remaining power to storage.
	float available = 0;

	// Pull all the power out of the generators.
	HexCell* cell = (HexCell*) allCells->getRoot();
	while( cell ) {
		if( cell->getCellType() == GENERATION_CELL )
			available += ((GenerationCell*) cell)->getPower( ((GenerationCell*) cell)->getGenerationRate() );

		cell = (HexCell*) cell->getNext();
	}

	// Put as much as possible into storage.
	cell = (HexCell*) allCells->getRoot();
	while( cell && available > 0 ) {
		if( cell->getCellType() == STORAGE_CELL )
			available -= ((StorageCell*) cell)->putPower( ((StorageCell*) cell)->getMaxEnergy() - ((StorageCell*) cell)->getCurrentEnergy() );

		cell = (HexCell*) cell->getNext();
	}
}


void Fighter::Draw() {
	glPushMatrix();

	// Apply fighter position transformations.
	Object::Draw();

	// Draw all cells.
	allCells->DrawObjects();

	glPopMatrix();


	// Draw weapon system (crosshairs).
	weaponSystem->Draw();
}


void Fighter::FirePrimary( bool fire ) {
	weaponSystem->FirePrimary( fire );
}


void Fighter::FireSecondary( bool fire ) {
	weaponSystem->FireSecondary( fire );
}


float Fighter::getHealth() { return coreCell->getHealth(); }
float Fighter::getFullHealth() { return coreCell->getFullHealth(); }


void Fighter::detachCell( HexCell* cell ) { allCells->remObject( cell ); }


void Fighter::destroyCell( HexCell* cell ) {
	// The whole ship has been destroyed when this cell goes...
	if( cell->getCellType() == CORE_CELL ) {
	}

	allCells->remObject( cell );
	delete cell;
}


int Fighter::getAlignment() { return align; }


float Fighter::getPower( float power ) {
	float available = 0;

	// Try to get the power from the generators.
	HexCell* cell = (HexCell*) allCells->getRoot();
	while( cell && available < power ) {
		if( cell->getCellType() == GENERATION_CELL )
			available += ((GenerationCell*) cell)->getPower( power - available );

		cell = (HexCell*) cell->getNext();
	}

	// If the generators don't have enough power, the storage cells might.
	cell = (HexCell*) allCells->getRoot();
	while( cell && available < power ) {
		if( cell->getCellType() == STORAGE_CELL )
			available += ((StorageCell*) cell)->getPower( power - available );

		cell = (HexCell*) cell->getNext();
	}

	return available;
}


void Fighter::returnPower( float power ) {
	float returned = 0;

	// Try to put the power in the storage cells.
	HexCell* cell = (HexCell*) allCells->getRoot();
	while( cell && returned < power ) {
		if( cell->getCellType() == STORAGE_CELL )
			returned += ((StorageCell*) cell)->putPower( power - returned );

		cell = (HexCell*) cell->getNext();
	}

	// If the storage cells don't have enough space,
	// the rest will be returned to the generators.
	cell = (HexCell*) allCells->getRoot();
	while( cell && returned < power ) {
		if( cell->getCellType() == GENERATION_CELL )
			returned += ((GenerationCell*) cell)->returnPower( power - returned );

		cell = (HexCell*) cell->getNext();
	}
}


void Fighter::setPropulsion( const vec3 &p ) {
	vec3 propulsionDone = vec3();

	// Try to propel the fighter.
	HexCell* cell = (HexCell*) allCells->getRoot();
	while( cell && propulsionDone < p ) {
		if( cell->getCellType() == PROPULSION_CELL )
			propulsionDone += ((PropulsionCell*) cell)->accelerate( p - propulsionDone );

		cell = (HexCell*) cell->getNext();
	}
}

