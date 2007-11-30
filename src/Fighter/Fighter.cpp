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
#include "WeaponCell.h"
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

	cellPos = ivec2( -2, 1 );
	WeaponCell* weaponCell = new WeaponCell( this, game, cellPos );
	weaponCell->setFullHealth( 750 );
	weaponCell->setHealth( 750 );
	weaponCell->setMass( 2000 );
	weaponSystem->addPrimaryWeapon( weaponCell );
	allCells->addObject( weaponCell );

	cellPos = ivec2( 2, 1 );
	weaponCell = new WeaponCell( this, game, cellPos );
	weaponCell->setFullHealth( 750 );
	weaponCell->setHealth( 750 );
	weaponCell->setMass( 2000 );
	weaponSystem->addSecondaryWeapon( weaponCell );
	allCells->addObject( weaponCell );

	align = a;
}


Fighter::~Fighter() {
	delete weaponSystem;
	delete allCells;
}


void Fighter::Update( int speed ) {
	Object::Update( speed );
	weaponSystem->Update( speed );
	allCells->UpdateObjects();

	// Determine difference between fighter angle and target angle.
	vec3 target = weaponSystem->getTarget();
	vec2 posDiff = vec2();
	posDiff[0] = target[0] - pos[0];
	posDiff[1] = target[1] - pos[1];
	float targetAngle = (180 / M_PI) * atanf (
		fabsf( posDiff[0]/posDiff[1] )
	);
	// Lower two quadrants.
	if( target[1] < pos[1] ) {
		// Third quadrant.
		if( target[0] < pos[0] )
			targetAngle = 180 - targetAngle;
		// Fourth quadrant.
		else
			targetAngle = 180 + targetAngle;
	}
	// Upper two quadrants.
	else {
		// Second quadrant - do nothing.
		// First quadrant.
		if( target[0] > pos[0] )
			targetAngle = 360 - targetAngle;
	}
	// Rotate fighter towards target.
	float diff = targetAngle - rot[2];
	if( diff > 180 )
		setRotation( diff - 360 );
	else if( diff < -180 )
		setRotation( diff + 360 );
	else
		setRotation( diff );


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
			propulsionDone += ((PropulsionCell*) cell)->generateAcceleration( p - propulsionDone );

		cell = (HexCell*) cell->getNext();
	}
}


void Fighter::setRotation( const float rotation ) {
	vec3 rotationNeeded = vec3();

	// Try to rotate the fighter - we don't actually want it to try to fully
	// rotate in the course of one frame - even if it's possible.
	rotationNeeded[2] = fmodf( rotation, 3 );

	// If the ship is really close, we need to lock it down.
	if( fabsf(rotation) <= 1.0 && fabsf(torq[2]) <= 0.4 ) {
		rot[2] += rotation;
		rotationNeeded[2] = 0;
		torq[2] = 0;
	}
	// Find out if the ship has overshot the target.  If not,
	// and the ship is nearing the target, we'll slow down.
	else if( ! (torq[2] > 0 && rotation < 0) &&	! (torq[2] < 0 && rotation > 0) ) {
		if( fabsf(torq[2] * 10) > fabsf(rotation) )
			rotationNeeded[2] /= - fabsf(torq[2] * 10) / fabsf(rotation);
	}
	// If we're close to the target, we need to approach it slowly.
	// This will eliminate any last possibility of "jittering".
	else if( fabsf(rotation) <= 6.0 && fabsf(rotationNeeded[2]) >= 1.0 ) {
		rotationNeeded[2] /= (10 / fabsf(rotation));
	}

	// Effects of explosions may also be dampened here.
	// If X and Y rotations are not 0, the ship is being buffetted.
	if( rot[0] != 0 )
		rotationNeeded[0] = - rot[0] / 2;
	if( rot[1] != 0 )
		rotationNeeded[1] = - rot[1] / 2;

	HexCell* cell = (HexCell*) allCells->getRoot();
	while( cell && rotationNeeded.length() != 0 ) {
		if( cell->getCellType() == PROPULSION_CELL )
			rotationNeeded -= ((PropulsionCell*) cell)->generateTorque( rotationNeeded );

		cell = (HexCell*) cell->getNext();
	}
}

