/* DisplayableList.h
 *
 * Copyright 2005-2007 Eliot Eshelman
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


#ifndef DISPLAYABLELIST_
#define DISPLAYABLELIST_

#include "List.h"

class Displayable;


/* Holds a group of displayable objects. */
class DisplayableList : public List {
	public:
				DisplayableList();
				virtual ~DisplayableList();

				// Update positions and states of all objects.
				void UpdateObjects( int );

				// Draw all the objects.
				void DrawObjects();

	private:
				DisplayableList( const DisplayableList & );
				const DisplayableList & operator= ( const DisplayableList & );
};


#endif /*DISPLAYABLELIST_*/
