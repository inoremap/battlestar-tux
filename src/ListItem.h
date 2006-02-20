/* ListItem.h
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


#ifndef LISTITEM_H_
#define LISTITEM_H_

/* Linked list items.  This class is to be inheritted by objects
 * which belong in a list.
 */
class ListItem {
	public:
				ListItem();
				virtual ~ListItem();

				void setPrev( ListItem* p );
				void setNext( ListItem* n );

				ListItem* & getPrev();
				ListItem* & getNext();

	protected:
				ListItem* prev;
				ListItem* next;

	private:
				ListItem( const ListItem &item );
				const ListItem & operator= ( const ListItem &item );
};


#endif /*LISTITEM_H_*/
