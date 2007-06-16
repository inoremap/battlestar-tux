/* Fighter.h
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


#ifndef FIGHTER_H_
#define FIGHTER_H_

#include <SDL_opengl.h>

#include "CoreCell.h"
#include "Game.h"
#include "HexCell.h"
#include "HexCellList.h"
#include "Object.h"
#include "Vector.h"


// Distinguish between 'evil' and 'good' fighters.
enum FighterAlignment {
	HEROS_FIGHTER,		// Fighter flown by player
	ENEMY_FIGHTER		// Enemy fighter
};


// A fighter aircraft.
// All the physical parts are actually handled by
// the cells.  This is just a logical grouping.
class Fighter : public Object {
	public:
				Fighter( FighterAlignment, Game* );
				virtual ~Fighter();

				// Update fighter systems.
				void Update( int );

				void Draw();

				// Weapons begin firing.
				void startFiring();

				// Weapons cease firing.
				void stopFiring();

				float getHealth();
				float getFullHealth();

				// One of the ship's components has been destroyed.
				void destroyCell( HexCell* );

				int getAlignment();

				bool hasComponents() { return true; }
				ObjectList* getComponents() { return allCells; }

	protected:
				// Ship components can get power here.
				// Returns the amount of power obtained.
				float getPower( float );

				// If a component doesn't use all the power it has
				// reserved, it must be returned to the ship.
				void returnPower( float );

				// Propulsion cells will be used to move ship.
				void setPropulsion( const vec3 & );


				CoreCell* coreCell;
				HexCellList* allCells;
				HexCellList* generationCells;
				HexCellList* storageCells;
				HexCellList* captureCells;
				HexCellList* propulsionCells;
				HexCellList* shieldCells;
				HexCellList* weaponCells;

				FighterAlignment align;

				Game* game;

	private:
				Fighter( const Fighter & );
				const Fighter & operator= ( const Fighter & );


	friend class ArmorCell;
	friend class CoreCell;
	friend class FighterController;
	friend class GenerationCell;
	friend class PropulsionCell;
	friend class StorageCell;
};


#endif /*FIGHTER_H_*/
