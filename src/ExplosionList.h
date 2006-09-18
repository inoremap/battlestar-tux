/* ExplosionList.h
 *
 * Copyright 2006 Eliot Eshelman
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


#ifndef EXPLOSIONLIST_H_
#define EXPLOSIONLIST_H_

#include <SDL_opengl.h>

#include "Game.h"
#include "List.h"

class Explosion;

enum ExplosionType {
	BASIC_EXPLOSION		=	0	// Default fighter explosion
};
static const int numExplosionTypes = 1;


/* Holds, updates and draws explosion animations. */
class ExplosionList : public List {
	public:
				ExplosionList( Game* g );
				~ExplosionList();

				// Draw explosions.
				void Draw();

				// Update explosions.
				void Update();

				// Add an explosion at the specified point.
				void AddExplosion( float* point );

	private:
				ExplosionList( const ExplosionList &list );
				const ExplosionList & operator= ( const ExplosionList &list );

				// Texture for each type of explosion.
				GLuint textures[numExplosionTypes];

				Game* game;
};


#endif /*EXPLOSIONLIST_H_*/
