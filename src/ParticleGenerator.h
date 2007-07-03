/* ParticleGenerator.h
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


#ifndef PARTICLEGENERATOR_H_
#define PARTICLEGENERATOR_H_


#include <SDL_opengl.h>

#include "List.h"
#include "Particle.h"
#include "Pulse.h"
#include "TextureManager.h"
#include "Vector.h"


/* Holds, updates and draws particles. */
class ParticleGenerator : public List {
	public:
				ParticleGenerator( TextureManager*, int, float );
				~ParticleGenerator();

				// Update particles.
				void Update( int );

				// Draw particles.
				void Draw();

				void addObject( Particle* );
				void remObject( Particle* );

	private:
				ParticleGenerator( const ParticleGenerator & );
				const ParticleGenerator & operator= ( const ParticleGenerator & );

				// Number of particles to generate.
				int maxParticles;

				// Current number of particles.
				int numParticles;

				// Particle generation rate (number/second).
				float generationRate;

				// Number of frames that should pass before
				// a new particle is created.
				// Automatically calculated from generationRate.
				int waitFrames;

				// The number of frames that have passed since
				// a particle was generated.  When will we create the next?
				int framesPassed;

				// To keep the particles from all being the same,
				// some randomness should be added.  These are maximums.
				float generationRandomness;
				float positionRandomness;
				float velocityRandomness;
				float sizeRandomness;
				float alphaRandomness;

				// Particle ages (frames).
				float maxAge;
				// Some particles may die before they reach maturity.
				float ageRandomness;

				TextureManager* textureManager;
				GLuint texture;
};


#endif /*PARTICLEGENERATOR_H_*/
