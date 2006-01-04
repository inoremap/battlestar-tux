/* EnemyFighterList.cpp
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

#include "EnemyFighter.h"
#include "EnemyFighterList.h"
#include "GfxUtils.h"

EnemyFighterList::EnemyFighterList( Game* g ) {
	rootObj = 0;

	// Load all enemy textures.
	textures[0] = loadTexture( "data/gfx/enemy_fighter_0001-64.png" );		// BASIC_ENEMY_FIGHTER

	game = g;
}


EnemyFighterList::~EnemyFighterList() {
	glDeleteTextures( numEnemyTypes, textures );

	for( int i=0; i < numEnemyTypes; i++ )
		textures[i] = 0;
}


void EnemyFighterList::UpdatePositions() {
	EnemyFighter* cur = rootObj;

	while( cur ) {
		cur->UpdatePos();
		cur = (EnemyFighter*) cur->getNext();
	}
}


void EnemyFighterList::DrawObjects() {
	EnemyFighter* cur = rootObj;

	while( cur ) {
		cur->Draw();
		cur = (EnemyFighter*) cur->getNext();
	}
}


void EnemyFighterList::CheckCollisions( Displayable* object ) {
	EnemyFighter* cur = rootObj;
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

		cur = (EnemyFighter*) cur->getNext();
	}

	if( objColl ) {
		object->setColor( 1.0, 0.0, 0.0, 1.0 );
	}
	else
		object->setColor( 1.0, 1.0, 1.0, 1.0 );
}


void EnemyFighterList::CullObjects() {
	float* bounds = game->getBounds();
	EnemyFighter* cur = rootObj;
	EnemyFighter* rem = 0;

	while( cur ) {
		float* pos = cur->getPos();
		float* size = cur->getSize();
		if( (pos[1] + size[1] / 2) < (0.0 - bounds[1]) ) {
			rem = cur;
	 		cur = (EnemyFighter*) cur->getNext();
			remObject( rem );
		}
		else
			cur = (EnemyFighter*) cur->getNext();
	}
}


GLuint EnemyFighterList::getTexture( int index ) { return textures[index]; }


void EnemyFighterList::addObject( EnemyFighter* obj ) {
	EnemyFighter* cur = rootObj;
	EnemyFighter* last = cur;
	while( cur ) {
		last = cur;
		cur = (EnemyFighter*) cur->getNext();
	}

	if( !last )
		rootObj = obj;
	else {
		last->setNext( (EnemyFighter*) obj );
		obj->setPrev( (EnemyFighter*) last );
	}
}


void EnemyFighterList::remObject( EnemyFighter* obj ) {
	// obj is rootObj
	if( !obj->getPrev() )
		rootObj = (EnemyFighter*) obj->getNext();
	else
		obj->getPrev()->setNext( (EnemyFighter*) obj->getNext() );

	if( obj->getNext() )
		obj->getNext()->setPrev( (EnemyFighter*) obj->getPrev() );

	delete obj;
}
