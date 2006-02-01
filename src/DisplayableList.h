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

class Displayable;

/* Holds a group of displayable objects. */
class DisplayableList {
	public:
				DisplayableList( Game* g );
				virtual ~DisplayableList();

				// Move all the objects to their next position.
				void UpdatePositions();

				// Draw all the objects.
				void DrawObjects();

				// Determine if any objects collide.
				void CheckCollisions( DisplayableList* objectList );

				// Determine if any objects collide.
				void CheckCollisions( Displayable* object );

				// Remove any objects that are out of bounds.
				void CullObjects();

				// Remove any objects that are out of bounds, but only on the bottom.
				// Many objects come in from the top and sides - technically out of bounds.
				void CullObjectsBottom();

				// Add a new object to be managed.
				void addObject( Displayable* obj );

				// Remove an object.
				void remObject( Displayable* obj );

				// Return the list of objects.
				Displayable* getRoot();

	protected:
				Displayable* rootObj;

				Game* game;
};


#endif /*DISPLAYABLELIST_*/
