/* ParticleGenerator.cpp
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


#include "ParticleGenerator.h"
#include "Simplex.h"


ParticleGenerator::ParticleGenerator( TextureManager* t, int num, float rate ) {
	maxParticles = num;
	numParticles = 0;
	generationRate = rate;
	waitFrames = (int) (1 / rate) * 50;
	framesPassed = 0;

	generationRandomness = 0.1;
	positionRandomness = 0.0001;
	velocityRandomness = 0.0004;
	sizeRandomness = 0.0001;
	alphaRandomness = 0.05;

	maxAge = 75;
	ageRandomness = 25;

	textureManager = t;
	texture = textureManager->loadTexture( "data/gfx/plasma_0001-32.png" );
}


ParticleGenerator::~ParticleGenerator() {
	textureManager->freeTextures( 1, &texture );
}


void ParticleGenerator::Update( int speed, float param1, float param2 ) {
	Particle* cur = (Particle*) rootObj;
	Particle* next = 0;

	// Update each particle, if there are any.
	while( cur ) {
		next = (Particle*) cur->getNext();

		// Remove finished particle.
		if( cur->getAge() >= maxAge )
			remObject( cur );
		else
			cur->Update( speed );

		cur = next;
	}


	// If the proper amount of time has passed,
	// add a new particle.
	framesPassed += speed;
	if( framesPassed >= waitFrames && numParticles < maxParticles) {
		framesPassed = 0;

		Particle* p = new Particle( texture );
		vec3 position = vec3(
			simplexRawNoise(param1, param2) * positionRandomness,
			simplexRawNoise(param2, param1) * positionRandomness,
			simplexRawNoise(param1, param2) * 0.000001
		);
		vec3 velocity = vec3(
			simplexRawNoise(param1, param2) * velocityRandomness,
			simplexRawNoise(param2, param1) * velocityRandomness,
			simplexRawNoise(param1, param2) * 0.000001
		);
		p->setPos( position );
		p->setVel( velocity );
		addObject( p );
	}
}


void ParticleGenerator::Draw() {
	Particle* cur = (Particle*) rootObj;
	Particle* next = 0;

	// Draw each Particle, if there are any.
	while( cur ) {
		next = (Particle*) cur->getNext();

		cur->Draw();

		cur = next;
	}
}


void ParticleGenerator::addObject( Particle* p ) {
	numParticles++;
	List::addObject( p );
}


void ParticleGenerator::remObject( Particle* p ) {
	numParticles--;
	List::remObject( p );
}

