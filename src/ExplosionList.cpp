/* ExplosionList.cpp
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


#include "Explosion.h"
#include "ExplosionList.h"
#include "TextureManager.h"

ExplosionList::ExplosionList( Game* g ) {
	game = g;

	// Load all explosion textures.
	textures[0] = game->getTextureManager()->loadTexture( "data/gfx/explosion_0001-128.png" );		// BASIC_EXPLOSION
}


ExplosionList::~ExplosionList() {
	game->getTextureManager()->freeTextures( numExplosionTypes, textures );

	for( int i=0; i < numExplosionTypes; i++ )
		textures[i] = 0;
}


void ExplosionList::Draw() {
	Explosion* cur = (Explosion*) rootObj;
	Explosion* next = 0;

	// Draw each explosion, if there are any.
	while( cur ) {
		next = (Explosion*) cur->getNext();

		cur->Draw();

		cur = next;
	}
}


void ExplosionList::Update() {
	Explosion* cur = (Explosion*) rootObj;
	Explosion* next = 0;

	// Update each explosion, if there are any.
	while( cur ) {
		next = (Explosion*) cur->getNext();

		// Remove finished explosion.
		if( cur->done() )
			remObject( cur );
		else
			cur->Update();

		cur = next;
	}
}


void ExplosionList::AddExplosion( float* point ) {
	Explosion* explosion = new Explosion( BASIC_EXPLOSION, textures[BASIC_EXPLOSION], game );
	explosion->setPos( point[0], point[1] );
	addObject( explosion );
}
