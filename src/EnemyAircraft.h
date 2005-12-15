/* EnemyAircraft.h
 *
 * Copyright 2005 Eliot Eshelman
 * eliot@6by9.net
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


#ifndef ENEMYAIRCRAFT_H_
#define ENEMYAIRCRAFT_H_

#include "Displayable.h"
#include "EnemyFighter.h"

/* Holds, updates and draws a group of displayable objects. */
class EnemyAircraft {
	public:
				EnemyAircraft( Game* g );

				// Move all the objects to their next position.
				void UpdatePositions();

				// Draw all the objects.
				void DrawObjects();

				// Determine if any object collides with 'object'.
				void CheckCollisions( Displayable* object );

				// Remove any objects that are out of bounds.
				void CullObjects();

				// Add a new object to be managed.
				void addObject( EnemyFighter* obj );

				// Remove an object.
				void remObject( EnemyFighter* obj );

	private:
				EnemyFighter* rootObj;
				Game* game;
};


#endif /*ENEMYAIRCRAFT_H_*/
