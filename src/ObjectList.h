/* ObjectList.h
 *
 * Copyright 2005-2008 Eliot Eshelman
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


#ifndef OBJECTLIST_H_
#define OBJECTLIST_H_

#include "Game.h"
#include "List.h"

class Object;


/* Holds a group of physical game Objects. */
class ObjectList : public List {
	public:
				ObjectList();
				virtual ~ObjectList();

				// Update positions and states of all objects.
				void UpdateObjects();

				// Draw all the objects.
				virtual void DrawObjects();

				// Check for collisions between this list and the given list.
				void CheckCollisions( ObjectList* );

				// Check for collisions with the given object.
				void CheckCollisions( Object* );

				// Check for collisions between the list and object.
				void CheckCollisions( ObjectList*, Object* );

				// Check for collisions between the two objects.
				void CheckCollisions( Object*, Object* );

	protected:
				Game* game;

	private:
				ObjectList( const ObjectList & );
				const ObjectList & operator= ( const ObjectList & );

				// Determine if the two objects collide.
				bool DetermineCollision( Object*, Object* );

				// Determine what should result from a collision.
				//
				// References to Object* are passed to ensure the
				// caller knows if an object was destroyed.
				//
				// Point (x, y) p specifies the location of the collision.
				void ResolveCollision( Object* &, Object* &, float* );
};


#endif /*OBJECTLIST_H_*/
