/* DisplayableList.h
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


#ifndef DISPLAYABLELIST_
#define DISPLAYABLELIST_

#include "Structures/List.h"

class Displayable;


// What portions of the screen cut items off.
enum objectCulling {
	CULL_TOP		=	0x0001,
	CULL_LEFT		=	0x0002,
	CULL_BOTTOM		=	0x0004,
	CULL_RIGHT		=	0x0008
};


/* Holds a group of displayable objects. */
class DisplayableList : public List {
	public:
				DisplayableList( Game* g );
				virtual ~DisplayableList();

				// Update positions and states of all objects.
				void UpdateObjects();

				// Draw all the objects.
				void DrawObjects();

				// Determine if any objects collide.
				void CheckCollisions( DisplayableList* objectList );

				// Determine if any objects collide.
				void CheckCollisions( Displayable* object );

				// Determine what should result from a collision.
				//
				// References to pointers are passed to ensure the
				// caller knows if an object was destroyed.
				void ResolveCollision( Displayable* &a, Displayable* &b );

				// Remove any objects that are out of bounds.
				void CullObjects( objectCulling cull );

	protected:
				Game* game;

	private:
				DisplayableList( const DisplayableList &list );
				const DisplayableList & operator= ( const DisplayableList &list );
};


#endif /*DISPLAYABLELIST_*/
