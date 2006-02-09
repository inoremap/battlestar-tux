/* List.cpp
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


#include <stdio.h>

#include "List.h"


List::List() {
	rootObj = 0;
}


List::~List() {}


void List::addObject( ListItem* obj ) {
	ListItem* first = rootObj;

	if( !first )
		rootObj = obj;
	else {
		first->setPrev( obj );
		obj->setNext( first );
		rootObj = obj;
	}
}


void List::remObject( ListItem* obj ) {
//if( obj->getType() == ENEMY_AMMO ) {
	printf( "\nDelete: %x\tPrev: %x\tNext: %x\n", obj, obj->getPrev(), obj->getNext() );
	printList( obj );
//}
	// obj is rootObj
	if( obj == rootObj ) 
		rootObj = obj->getNext();
	else if( ! obj->getPrev() ) {
		printf( "There's a split in the list!!" );
	}
	else
		obj->getPrev()->setNext( obj->getNext() );

	if( obj->getNext() )
		obj->getNext()->setPrev( obj->getPrev() );
//if( obj->getType() == ENEMY_AMMO ) {
	printf( "\nDelete: %x\n", obj );
	printList();
	printf( "\nrootObj: %x\n", rootObj );
//}
	obj->setPrev( 0 );
	obj->setNext( 0 );
	delete obj;
}


ListItem* List::getRoot() { return rootObj; }


void List::printList() { printList(rootObj); }
void List::printList( ListItem* obj ) {
	ListItem* cur = obj;
	int count = 0;

	printf( "---List------------------\n" );
	printf( " obj: %8x\trootObj: %8x", obj, rootObj );
	if( obj )
		printf( "\tprev: %8x\tnext: %8x\n", obj->getPrev(), obj->getNext() );
	else
		printf( "\n" );

	while( cur ) {
		if( count < 10 ) {
			printf( " Object: 0x%x", cur );
			printf( "\tprev: %8x\tnext: %8x\n", cur->getPrev(), cur->getNext() );
		}

		count++;
		cur = cur->getNext();
	}

	if( count >= 10 )
		printf( " more...%i total\n", count );

	printf( "---List------------------\n\n" );
}
