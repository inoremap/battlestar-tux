/* EnemyFighter.h
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


#ifndef ENEMYFIGHTER_H_
#define ENEMYFIGHTER_H_

#include "SDL_opengl.h"

#include "Displayable.h"
#include "EnemyFighterList.h"
#include "Game.h"

/* An enemy fighter ship - NPC. */
class EnemyFighter : public Displayable {
	public:
				EnemyFighter( EnemyFighterType f, EnemyFighterList* l, Game* g );

				void Draw();

	private:
				// Constant Z position of the fighter.
				static const float zPos = -1.5;

				EnemyFighterType type;

				GLuint texture;
};


#endif /*ENEMYFIGHTER_H_*/
