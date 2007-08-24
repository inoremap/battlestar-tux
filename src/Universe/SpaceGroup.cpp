/* SpaceGroup.cpp
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


#include "SpaceGroup.h"
#include "SpaceObject.h"


SpaceGroup::SpaceGroup() {
}


SpaceGroup::~SpaceGroup() {
}


void SpaceGroup::UpdateObjects() {
	SpaceObject* cur = (SpaceObject*) rootObj;

	while( cur ) {
		cur->Update();
		cur = (SpaceObject*) cur->getNext();
	}
}


void SpaceGroup::DrawObjects() {
	// The matrices should be set so that we are at the center of gravity of
	// the containing object.  Each object will then move from that point.

	SpaceObject* cur = (SpaceObject*) rootObj;

	while( cur ) {
		cur->Draw();
		cur = (SpaceObject*) cur->getNext();
	}
}

