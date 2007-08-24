/* List.h
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


#ifndef LIST_H_
#define LIST_H_

#include <string>

#include "ListItem.h"

class List {
	public:
				List();
				List( bool atEnd );
				virtual ~List();

				// Add a new object.
				virtual void addObject( ListItem* obj );

				// Remove an object.
				virtual void remObject( ListItem* obj );

				// Return the list of objects.
				ListItem* getRoot();

				// Return the total number of items.
				int getNum();

				// Print list of objects, starting at root.
				void printList();
				void printList( std::string desc );

				// Print list of objects, starting at obj.
				void printList( ListItem* obj );
				void printList( ListItem* obj, std::string desc );

	protected:
				ListItem* rootObj;

				// Add items at beginning or end of list?
				bool addAtEnd;

				// Current number of objects.
				int numItems;

	private:
				List( const List &list );
				const List & operator= ( const List &list );
};


#endif /*LIST_H_*/
