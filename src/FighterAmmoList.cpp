/* FighterAmmoList.cpp
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


#include <math.h>

#include "FighterAmmo.h"
#include "FighterAmmoList.h"
#include "GfxUtils.h"

FighterAmmoList::FighterAmmoList( Game* g ) {
	rootObj = 0;

	// Load all ammo textures.
	textures[0] = loadTexture( "data/gfx/laser_0001-64.png" );		// BASIC_LASER

	game = g;
}


FighterAmmoList::~FighterAmmoList() {
	glDeleteTextures( numFighterAmmo, textures );

	for( int i=0; i < numFighterAmmo; i++ )
		textures[i] = 0;
}


void FighterAmmoList::UpdatePositions() {
	FighterAmmo* cur = rootObj;

	while( cur ) {
		cur->UpdatePos();
		cur = (FighterAmmo*) cur->getNext();
	}
}


void FighterAmmoList::DrawObjects() {
	FighterAmmo* cur = rootObj;

	while( cur ) {
		cur->Draw();
		cur = (FighterAmmo*) cur->getNext();
	}
}


void FighterAmmoList::CheckCollisions( Displayable* object ) {
	FighterAmmo* cur = rootObj;
	bool objColl = false;

	while( cur ) {
		float mx = object->getPos()[0] - cur->getPos()[0];
		float my = object->getPos()[1] - cur->getPos()[1];
		float dist = sqrtf( mx*mx + my*my );
		float d0 = ((float) object->getSize()[0] + (float) object->getSize()[1]) / 2;
		float d1 = ((float) cur->getSize()[0] + (float) cur->getSize()[1]) / 2;
		float minDist = d0 / 2 + d1 / 2;

		if( dist < minDist ) {
			objColl = true;
			cur->setColor( 1.0, 0.0, 0.0, 1.0 );
		}
		else
			cur->setColor( 1.0, 1.0, 1.0, 1.0 );

		cur = (FighterAmmo*) cur->getNext();
	}

	if( objColl ) {
		object->setColor( 1.0, 0.0, 0.0, 1.0 );
	}
	else
		object->setColor( 1.0, 1.0, 1.0, 1.0 );
}


void FighterAmmoList::CullObjects() {
	float* bounds = game->getBounds();
	FighterAmmo* cur = rootObj;
	FighterAmmo* rem = 0;

	while( cur ) {
		float* pos = cur->getPos();
		float* size = cur->getSize();

		// Top of screen.
		if( (pos[1] - size[1] / 2) > bounds[1] ) {
			rem = cur;
	 		cur = (FighterAmmo*) cur->getNext();

			remObject( rem );
			continue;
		}

		// Bottom of screen.
		if( (pos[1] + size[1] / 2) < (0.0 - bounds[1]) ) {
			rem = cur;
	 		cur = (FighterAmmo*) cur->getNext();

			remObject( rem );
			continue;
		}

		// Left of screen.
		if( (pos[0] + size[0] / 2) < (0.0 - bounds[0]) ) {
			rem = cur;
	 		cur = (FighterAmmo*) cur->getNext();

			remObject( rem );
			continue;
		}

		// Right of screen.
		if( (pos[0] - size[0] / 2) > bounds[0] ) {
			rem = cur;
	 		cur = (FighterAmmo*) cur->getNext();

			remObject( rem );
			continue;
		}

		cur = (FighterAmmo*) cur->getNext();
	}
}


GLuint FighterAmmoList::getTexture( int index ) { return textures[index]; }


void FighterAmmoList::addObject( FighterAmmo* obj ) {
	FighterAmmo* cur = rootObj;
	FighterAmmo* last = cur;
	while( cur ) {
		last = cur;
		cur = (FighterAmmo*) cur->getNext();
	}

	if( !last )
		rootObj = obj;
	else {
		last->setNext( (FighterAmmo*) obj );
		obj->setPrev( (FighterAmmo*) last );
	}
}


void FighterAmmoList::remObject( FighterAmmo* obj ) {
	// obj is rootObj
	if( !obj->getPrev() )
		rootObj = (FighterAmmo*) obj->getNext();
	else
		obj->getPrev()->setNext( (FighterAmmo*) obj->getNext() );

	if( obj->getNext() )
		obj->getNext()->setPrev( (FighterAmmo*) obj->getPrev() );

	delete obj;
}
