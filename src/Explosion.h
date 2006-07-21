/* Explosion.h
 *
 * Copyright 2006 Eliot Eshelman
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


#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include <SDL_opengl.h>

#include "Displayable.h"
#include "ExplosionList.h"
#include "Game.h"
#include "Pulse.h"

class Explosion : public Displayable {
	public:
				Explosion( ExplosionType e, GLuint t, Game* g );

				void Update();

				void Draw();

				// Returns true when the explosion has subsided.
				bool done();

	private:
				Explosion( const Explosion &explosion );
				const Explosion & operator= ( const Explosion &explosion );

				// Control the changing size of the explosion.
				Pulse* sizePulse;

				// Control the appearance and fade of the explosion.
				Pulse* alphaPulse;

				ExplosionType explosionType;

				GLuint texture;
};


#endif /*EXPLOSION_H_*/
