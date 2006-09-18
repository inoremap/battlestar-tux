/* StringArray.h
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


#ifndef STRINGARRAY_H_
#define STRINGARRAY_H_

#include <string>

/* Holds a sorted array of strings with an associated
 * array of integer IDs.  Perfect for storing texture IDs.
 */
class StringArray {
	public:
				StringArray();
				~StringArray();

				void insert( std::string value, int id );

				void remove( std::string value );
				void remove( int id );

				void removeAll();

				int getID( std::string value );

				const int* getAllIDs();

				// Return number of values and IDs stored.
				const int getSize();

				void print();

	private:
				StringArray( const StringArray &a );
				const StringArray & operator= ( const StringArray &a );

				// Number of array slots used.
				int used;

				// Size of the arrays.
				int size;

				// Array of string values.
				std::string* values;

				// Array of integer ids.
				int* ids;
};


#endif /*STRINGARRAY_H_*/
