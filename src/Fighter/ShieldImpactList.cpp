/* ShieldImpactList.cpp
 *
 * Copyright 2006 Eliot Eshelman
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


#include "ShieldImpactList.h"
#include "../TextureManager.h"

ShieldImpactList::ShieldImpactList( Game* g ) {
	texture = g->getTextureManager()->loadTexture( "data/gfx/shields_0001-64.png" );
}


ShieldImpactList::~ShieldImpactList() {}


void ShieldImpactList::Draw() {
	if( rootObj ) {
		glBindTexture( GL_TEXTURE_2D, texture );
	}
}


void ShieldImpactList::Update() {
	Displayable* cur = (Displayable*) rootObj;
	Displayable* next = 0;

	while( cur ) {
		next = (Displayable*) cur->getNext();

		cur = next;
	}
}
