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

Fighter::Fighter( FighterAlignment a, Game* g ) : Object( FIGHTER ) {
	game = g;

	torq[1] = 1;

	pos[2] = 3;

	allCells = new HexCellList( game );
	generationCells = new HexCellList( game );
	storageCells = new HexCellList( game );
	captureCells = new HexCellList( game );
	propulsionCells = new HexCellList( game );
	shieldCells = new HexCellList( game );
	weaponCells = new HexCellList( game );

	ivec2 cellPos = ivec2();
	coreCell = new CoreCell( this, game->getTextureManager(), cellPos );
	coreCell->setFullHealth( 10000 );
	coreCell->setHealth( 10000 );
	coreCell->setMass( 100000 );
	allCells->addObject( coreCell );

	cellPos = ivec2( 1, 0 );
	ArmorCell* armorCell = new ArmorCell( this, game->getTextureManager(), cellPos );
	armorCell->setFullHealth( 1000 );
	armorCell->setHealth( 1000 );
	armorCell->setMass( 2500 );
	allCells->addObject( armorCell );

	cellPos = ivec2( 0, 1 );
	armorCell = new ArmorCell( this, game->getTextureManager(), cellPos );
	armorCell->setFullHealth( 1000 );
	armorCell->setHealth( 1000 );
	armorCell->setMass( 2500 );
	allCells->addObject( armorCell );

	cellPos = ivec2( -1, 0 );
	armorCell = new ArmorCell( this, game->getTextureManager(), cellPos );
	armorCell->setFullHealth( 1000 );
	armorCell->setHealth( 1000 );
	armorCell->setMass( 2500 );
	allCells->addObject( armorCell );

	cellPos = ivec2( -1, -1 );
	armorCell = new ArmorCell( this, game->getTextureManager(), cellPos );
	armorCell->setFullHealth( 1000 );
	armorCell->setHealth( 1000 );
	armorCell->setMass( 2500 );
	allCells->addObject( armorCell );

	cellPos = ivec2( 0, -1 );
	armorCell = new ArmorCell( this, game->getTextureManager(), cellPos );
	armorCell->setFullHealth( 1000 );
	armorCell->setHealth( 1000 );
	armorCell->setMass( 2500 );
	allCells->addObject( armorCell );

	cellPos = ivec2( 1, -1 );
	armorCell = new ArmorCell( this, game->getTextureManager(), cellPos );
	armorCell->setFullHealth( 1000 );
	armorCell->setHealth( 1000 );
	armorCell->setMass( 2500 );
	allCells->addObject( armorCell );

	cellPos = ivec2( 0, -2 );
	GenerationCell* generationCell = new GenerationCell( this, game->getTextureManager(), cellPos );
	generationCell->setFullHealth( 200 );
	generationCell->setHealth( 200 );
	generationCell->setMass( 1500 );
	generationCell->setGenerationRate( 555 );
	generationCells->addObject( generationCell );
	allCells->addObject( generationCell );

	cellPos = ivec2( -1, -2 );
	StorageCell* storageCell = new StorageCell( this, game->getTextureManager(), cellPos );
	storageCell->setFullHealth( 300 );
	storageCell->setHealth( 300 );
	storageCell->setMass( 2000 );
	storageCell->setMaxEnergy( 25000 );
	storageCells->addObject( storageCell );
	allCells->addObject( storageCell );

	cellPos = ivec2( 1, -2 );
	storageCell = new StorageCell( this, game->getTextureManager(), cellPos );
	storageCell->setFullHealth( 300 );
	storageCell->setHealth( 300 );
	storageCell->setMass( 2000 );
	storageCell->setMaxEnergy( 25000 );
	storageCells->addObject( storageCell );
	allCells->addObject( storageCell );

	cellPos = ivec2( -2, -1 );
	PropulsionCell* propulsionCell = new PropulsionCell( this, game->getTextureManager(), cellPos );
	propulsionCell->setFullHealth( 500 );
	propulsionCell->setHealth( 500 );
	propulsionCell->setMass( 3000 );
	propulsionCell->setAccelerationRate( 50 );
	propulsionCell->setPowerRate( 250 );
	propulsionCells->addObject( propulsionCell );
	allCells->addObject( propulsionCell );

	cellPos = ivec2( 2, -1 );
	propulsionCell = new PropulsionCell( this, game->getTextureManager(), cellPos );
	propulsionCell->setFullHealth( 500 );
	propulsionCell->setHealth( 500 );
	propulsionCell->setMass( 3000 );
	propulsionCell->setAccelerationRate( 50 );
	propulsionCell->setPowerRate( 250 );
	propulsionCells->addObject( propulsionCell );
	allCells->addObject( propulsionCell );

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

	// need to move generated power to storage cells??
}


void Fighter::Draw() {
	glPushMatrix();

	// Apply fighter position transformations.
	Object::Draw();

	// Draw all cells.
	HexCell* cur = (HexCell*) allCells->getRoot();
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


float Fighter::getPower( float power ) {
	float available = 0;

	// Try to get the power from the generators.
	GenerationCell* gen = (GenerationCell*) generationCells->getRoot();
	while( gen && available < power ) {
		available += gen->getPower( power - available );

		gen = (GenerationCell*) gen->getNext();
	}

	// If the generators don't have enough,
	// the storage cells might.
	StorageCell* stor = (StorageCell*) storageCells->getRoot();
	while( stor && available < power ) {
		available += stor->getPower( power - available );

		stor = (StorageCell*) stor->getNext();
	}

	return available;
}


void Fighter::returnPower( float power ) {
	float returned = 0;

	// Try to return the power to the generators.
	GenerationCell* gen = (GenerationCell*) generationCells->getRoot();
	while( gen && returned < power ) {
		returned += gen->returnPower( power - returned );

		gen = (GenerationCell*) gen->getNext();
	}

	// If the generators don't have enough space,
	// the rest will be put in the storage cells.
	StorageCell* stor = (StorageCell*) storageCells->getRoot();
	while( stor && returned < power ) {
		returned += stor->putPower( power - returned );

		stor = (StorageCell*) stor->getNext();
	}
}


void Fighter::setPropulsion( const vec3 &p ) {
	vec3 propulsionDone = vec3();

	// Try to propel the fighter.
	PropulsionCell* prop = (PropulsionCell*) propulsionCells->getRoot();
	while( prop && propulsionDone < p ) {
		propulsionDone += prop->accelerate( p - propulsionDone );

		prop = (PropulsionCell*) prop->getNext();
	}
}

