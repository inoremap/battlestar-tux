/* Ground.cpp
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


#include "Ground.h"
#include "GroundSegment.h"
#include "TextureManager.h"

Ground::Ground( GroundType type, Game* g ) {
	groundType = type;
	game = g;
	texture = game->getTextureManager()->loadTexture( "data/gfx/ground_0001-256.png" );

	float baseY = game->getBounds()[1] + segSize / 2;

	rootSeg = new GroundSegment( groundType, this, game );
	rootSeg->setPos( 0.0, baseY );

	GroundSegment* last = rootSeg;
	GroundSegment* seg = 0;

	for( int i=1; i < (numSegY + 1); i++ ) {
		seg = new GroundSegment( type, this, game );
		seg->setPos( 0.0, baseY - (i * segSize) );
		seg->setPrev( (GroundSegment*) last );

		last->setNext( (GroundSegment*) seg );
		last = seg;
	}
}


Ground::~Ground() {
	GroundSegment* cur = rootSeg;
	GroundSegment* prev = cur;

	while( cur ) {
		prev = (GroundSegment*) cur->getPrev();
		if( prev )
			delete prev;
		prev = cur;

		cur = (GroundSegment*) cur->getNext();
	}

	if( prev )
		delete prev;

	game->getTextureManager()->freeTextures( 1, &texture );
}


void Ground::Draw() {
	GroundSegment* seg = rootSeg;

	while( seg ) {
		// Determine if this segment is off screen.
		float* pos = seg->getPos();
		if( pos[1] < (0.0 - game->getBounds()[1] - segSize/2) )
			rotateSegments();

		seg->Update();
		seg->Draw();

		seg = (GroundSegment*) seg->getNext();
	}
}


void Ground::rotateSegments() {
	GroundSegment* first = rootSeg;
	GroundSegment* cur = rootSeg;
	GroundSegment* last = 0;

	// Find the very last segment.
	while( (cur = (GroundSegment*) cur->getNext()) ) {
		last = cur;
	}

	// Move the last segment to the front of the list.
	last->getPrev()->setNext( 0 );
	last->setPrev( 0 );
	last->setNext( (GroundSegment*) first );
	first->setPrev( (GroundSegment*) last );
	rootSeg = last;

	// Move the last segment to the proper Y position.
	float baseY = (float) first->getPos()[1] + segSize;
	last->setPos( 0.0, baseY );
}


GroundType Ground::getType() { return groundType; }
GLuint Ground::getTexture() { return texture; }
