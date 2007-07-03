/* Particle.h
 *
 * Copyright 2007 Eliot Eshelman
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


#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <SDL_opengl.h>

#include "Displayable.h"
#include "Game.h"
#include "Pulse.h"

class Particle : public Displayable {
	public:
				Particle( GLuint );
				~Particle();

				void Update( int );

				void Draw();

	private:
				Particle( const Particle & );
				const Particle & operator= ( const Particle & );

				// Control the changing size of the Particle.
				Pulse* sizePulse;

				// Control the appearance and fade of the Particle.
				Pulse* alphaPulse;

				GLuint texture;
};


#endif /*PARTICLE_H_*/
