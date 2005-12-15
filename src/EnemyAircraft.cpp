/* EnemyAircraft.cpp
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


#include "EnemyAircraft.h"

EnemyAircraft::EnemyAircraft( Game* g ) {
	game = g;
}


void EnemyAircraft::UpdatePositions() {
	EnemyFighter* cur = rootObj;

	while( cur ) {
		cur->UpdatePos();
		cur = (EnemyFighter*) cur->getNext();
	}
}


void EnemyAircraft::DrawObjects() {
	EnemyFighter* cur = rootObj;

	while( cur ) {
		cur->Draw();
		cur = (EnemyFighter*) cur->getNext();
	}
}


void EnemyAircraft::CheckCollisions( Displayable* object ) {

}


void EnemyAircraft::CullObjects() {

}


void EnemyAircraft::addObject( EnemyFighter* obj ) {
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

void EnemyAircraft::remObject( EnemyFighter* obj ) {
	EnemyFighter* cur = rootObj;

	while( cur ) {
		if( cur == obj ) {
			cur->getPrev()->setNext( (EnemyFighter*) cur->getNext() );
			cur->getNext()->setPrev( (EnemyFighter*) cur->getPrev() );

			delete cur;

			break;
		}

		cur = (EnemyFighter*) cur->getNext();
	}
}
