/* DisplayableList.cpp
 *
 * Copyright 2005-2006 Eliot Eshelman
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


#include <math.h>

#include "Displayable.h"
#include "DisplayableList.h"

DisplayableList::DisplayableList( Game* g ) {
	rootObj = 0;
	game = g;
}


DisplayableList::~DisplayableList() {}


void DisplayableList::UpdatePositions() {
	Displayable* cur = rootObj;

	while( cur ) {
		cur->UpdatePos();
		cur = (Displayable*) cur->getNext();
	}
}


void DisplayableList::DrawObjects() {
	Displayable* cur = rootObj;

	while( cur ) {
		cur->Draw();
		cur = (Displayable*) cur->getNext();
	}
}


void DisplayableList::CheckCollisions( DisplayableList* objectList ) {
	Displayable* cur = objectList->getRoot();

	while( cur ) {
		CheckCollisions( cur );
		cur = (Displayable*) cur->getNext();
	}
}


void DisplayableList::CheckCollisions( Displayable* object ) {
	Displayable* cur = rootObj;
	bool objColl = false;

	float* sizeA = object->getSize();
	float* posA = object->getPos();
	float rightA = posA[0] + sizeA[0]/2;
	float leftA = posA[0] - sizeA[0]/2;
	float topA = posA[1] + sizeA[1]/2;
	float bottomA = posA[1] - sizeA[1]/2;

	while( cur ) {
		// Do a 'rough estimate' collision detection.
		float* sizeB = cur->getSize();
		float* posB = cur->getPos();
		float rightB = posB[0] + sizeB[0]/2;
		float leftB = posB[0] - sizeB[0]/2;
		float topB = posB[1] + sizeB[1]/2;
		float bottomB = posB[1] - sizeB[1]/2;

		if( rightB > leftA && rightA > leftB && topB > bottomA && topA > bottomB ) {
			// Accurate collision detection.
			float mx = posA[0] - posB[0];
			float my = posA[1] - posB[1];
			float dist = sqrtf( mx*mx + my*my );
			float minDist = (sizeA[0] + sizeA[1] + sizeB[0] + sizeB[1]) / 4;
	
			if( dist < minDist ) {
				objColl = true;
				cur->setColor( 1.0, 0.0, 0.0, 1.0 );
			}
			else
				cur->setColor( 1.0, 1.0, 1.0, 1.0 );
		}

		cur = (Displayable*) cur->getNext();
	}

	if( objColl ) {
		object->setColor( 1.0, 0.0, 0.0, 1.0 );
	}
	else
		object->setColor( 1.0, 1.0, 1.0, 1.0 );
}


void DisplayableList::CullObjects() {
	float* bounds = game->getBounds();
	Displayable* cur = rootObj;
	Displayable* rem = 0;

	while( cur ) {
		float* pos = cur->getPos();
		float* size = cur->getSize();

		// Top of screen.
		if( (pos[1] - size[1] / 2) > bounds[1] ) {
			rem = cur;
	 		cur = (Displayable*) cur->getNext();

			remObject( rem );
			continue;
		}

		// Bottom of screen.
		if( (pos[1] + size[1] / 2) < (0.0 - bounds[1]) ) {
			rem = cur;
	 		cur = (Displayable*) cur->getNext();

			remObject( rem );
			continue;
		}

		// Left of screen.
		if( (pos[0] + size[0] / 2) < (0.0 - bounds[0]) ) {
			rem = cur;
	 		cur = (Displayable*) cur->getNext();

			remObject( rem );
			continue;
		}

		// Right of screen.
		if( (pos[0] - size[0] / 2) > bounds[0] ) {
			rem = cur;
	 		cur = (Displayable*) cur->getNext();

			remObject( rem );
			continue;
		}

		cur = (Displayable*) cur->getNext();
	}
}


void DisplayableList::CullObjectsBottom() {
	float* bounds = game->getBounds();
	Displayable* cur = rootObj;
	Displayable* rem = 0;

	while( cur ) {
		float* pos = cur->getPos();
		float* size = cur->getSize();

		// Bottom of screen.
		if( (pos[1] + size[1] / 2) < (0.0 - bounds[1]) ) {
			rem = cur;
	 		cur = (Displayable*) cur->getNext();

			remObject( rem );
			continue;
		}

		cur = (Displayable*) cur->getNext();
	}
}


void DisplayableList::addObject( Displayable* obj ) {
	Displayable* cur = rootObj;
	Displayable* last = cur;
	while( cur ) {
		last = cur;
		cur = (Displayable*) cur->getNext();
	}

	if( !last )
		rootObj = obj;
	else {
		last->setNext( (Displayable*) obj );
		obj->setPrev( (Displayable*) last );
	}
}


void DisplayableList::remObject( Displayable* obj ) {
	// obj is rootObj
	if( !obj->getPrev() )
		rootObj = (Displayable*) obj->getNext();
	else
		obj->getPrev()->setNext( (Displayable*) obj->getNext() );

	if( obj->getNext() )
		obj->getNext()->setPrev( (Displayable*) obj->getPrev() );

	delete obj;
}


Displayable* DisplayableList::getRoot() { return rootObj; }
