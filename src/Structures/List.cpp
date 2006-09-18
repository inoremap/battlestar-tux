/* List.cpp
 *
 * Copyright 2005-2006 Eliot Eshelman
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


#include <iostream>

#include "List.h"

List::List() {
	rootObj = 0;
	addAtEnd = false;
}


List::List( bool atEnd ) {
	rootObj = 0;
	addAtEnd = atEnd;
}


List::~List() {}


void List::addObject( ListItem* obj ) {
	if( !rootObj )
		rootObj = obj;
	else {
		// Add object to end of list.
		if( addAtEnd ) {
			ListItem* cur = rootObj;
			ListItem* last = NULL;

			// Find last object in list.
			while( cur ) {
				last = cur;
				cur = cur->getNext();
			}

			last->setNext( obj );
			obj->setPrev( last );
		}

		// Add object to beginning of list.
		else {
			rootObj->setPrev( obj );
			obj->setNext( rootObj );
			rootObj = obj;
		}
	}
}


void List::remObject( ListItem* obj ) {
	// obj is rootObj
	if( obj == rootObj ) 
		rootObj = rootObj->getNext();
	else
		obj->getPrev()->setNext( obj->getNext() );

	if( obj->getNext() )
		obj->getNext()->setPrev( obj->getPrev() );

	delete obj;
}


ListItem* List::getRoot() { return rootObj; }


void List::printList() { printList( rootObj, "List" ); }
void List::printList( std::string desc ) { printList( rootObj, desc ); }
void List::printList( ListItem* obj ) { printList( obj, "List" ); }
void List::printList( ListItem* obj, std::string desc ) {
	ListItem* cur = obj;
	int count = 0;

	std::cout << "---" << desc << "------------------\n";
	std::cout << " obj: " << obj << "\trootObj: " << rootObj;
	if( obj )
		std::cout << "\tprev: " << obj->getPrev() << "\tnext: " << obj->getNext() << "\n";
	else
		std::cout << "\n";

	while( cur ) {
		if( count < 20 ) {
			std::cout << " Object: 0x" << cur;
			std::cout << "\tprev: " << cur->getPrev() << "\tnext: " << cur->getNext() << "\n";
		}

		count++;
		cur = cur->getNext();
	}

	if( count >= 20 )
		std::cout << " more..." << count << " total\n";

	std::cout << "---" << desc << "------------------\n\n";
}
