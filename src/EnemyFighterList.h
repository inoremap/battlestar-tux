/* EnemyFighterList.h
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


#ifndef ENEMYFIGHTERLIST_H_
#define ENEMYFIGHTERLIST_H_

#include "SDL_opengl.h"

#include "Displayable.h"

class EnemyFighter;


enum EnemyFighterType {
	BASIC_ENEMY_FIGHTER		// Default enemy fighter
};
static const int numEnemyTypes = 1;


/* Holds, updates and draws enemy aircraft. */
class EnemyFighterList {
	public:
				EnemyFighterList( Game* g );
				~EnemyFighterList();

				// Move all the objects to their next position.
				void UpdatePositions();

				// Draw all the objects.
				void DrawObjects();

				// Determine if any object collides with 'object'.
				void CheckCollisions( Displayable* object );

				// Remove any objects that are out of bounds.
				// For now, only cull objects that leave the
				// bottom of the screen.  Enemies will come in
				// from the top and sides.
				void CullObjects();

				// Get a texture ID.
				GLuint getTexture( int index );

				// Add a new object to be managed.
				void addObject( EnemyFighter* obj );

				// Remove an object.
				void remObject( EnemyFighter* obj );

	private:
				EnemyFighter* rootObj;

				// Texture for each type of enemy.
				GLuint textures[numEnemyTypes];

				Game* game;
};


#endif /*ENEMYFIGHTERLIST_H_*/
