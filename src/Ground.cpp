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

Ground::Ground( GroundType type, Game* g ) {
	groundType = type;
	game = g;

	float baseY = game->getBounds()[1] + segSize / 2;

	rootSeg = new GroundSegment( groundType, this, game );
	rootSeg->setPos( 0.0, baseY, 0.0 );

	GroundSegment* last = rootSeg;
	GroundSegment* seg = 0;

	for( int i=1; i < (numSegY + 1); i++ ) {
		seg = new GroundSegment( type, this, game );
		seg->setPos( 0.0, baseY - (i * segSize), 0.0 );
		seg->setPrev( last );

		last->setNext( seg );
		last = seg;
	}
}


void Ground::Draw() {
	GroundSegment* seg = rootSeg;

	while( seg ) {
		// Determine if this segment is off screen.
		float* pos = seg->getPos();
		if( pos[1] < (- game->getBounds()[1] - segSize/2) )
			rotateSegments();

		seg->UpdatePos();
		seg->Draw();

		seg = seg->getNext();
	}
}


GroundType Ground::getType() { return groundType; }


void Ground::rotateSegments() {
	GroundSegment* first = rootSeg;
	GroundSegment* cur = rootSeg;
	GroundSegment* last = 0;

	// Find the very last segment.
	while( (cur = cur->getNext()) ) {
		last = cur;
	}

	// Move the last segment to the front of the list.
	last->getPrev()->setNext( 0 );
	last->setPrev( 0 );
	last->setNext( first );
	first->setPrev( last );
	rootSeg = last;

	// Move the last segment to the proper Y position.
	float baseY = (float) first->getPos()[1] + segSize;
	last->setPos( 0.0, baseY, 0.0 );
}
