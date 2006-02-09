/* List.h
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


#ifndef LIST_H_
#define LIST_H_

#include "ListItem.h"


class List {
	public:
				List();
				virtual ~List();

				// Add a new object.
				void addObject( ListItem* obj );

				// Remove an object.
				void remObject( ListItem* obj );

				// Return the list of objects.
				ListItem* getRoot();

				// Print list of objects.
				void printList();

				// Print list of objects, starting at obj.
				void printList( ListItem* obj );

	protected:
				ListItem* rootObj;
};


#endif /*LIST_H_*/
