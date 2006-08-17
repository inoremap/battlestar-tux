/* StringArray.cpp
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


#include <iostream>

#include "StringArray.h"

StringArray::StringArray() {
	used = 0;
	size = 8;

	values = new std::string[size];
	ids = new int[size];

	// Initialize arrays.
	for( int i = 0; i < size; i++ ) {
		values[i] = "";
		ids[i] = 0;
	}
}


StringArray::~StringArray() {
	used = 0;
	size = 0;

	delete[] values;
	delete[] ids;
}


void StringArray::insert( std::string value, int id ) {
	int position = -1;

	// Find the sorted position of the new value.
	for( int i = 0; i < used; i++ ) {
		if( value == values[i] ) {
			std::cout << "StringArray: Duplicate load attempted: " << value << "\n";
			return;
		}
		else if( value < values[i] ) {
			position = i;
			break;
		}
	}

	if( position == -1 )
		position = used;

	// Grow the arrays, if necessary.
	if( used == size ) {
		size *= 2;
		std::string* newValues = new std::string[size];
		int* newIds = new int[size];

		// Initialize arrays.
		for( int i = 0; i < used; i++ ) {
			newValues[i] = values[i];
			newIds[i] = ids[i];
		}
		for( int i = used; i < size; i++ ) {
			newValues[i] = "";
			newIds[i] = 0;
		}

		delete[] values;
		delete[] ids;
		values = newValues;
		ids = newIds;
	}

	// Push values back to make room for insertion.
	for( int i = size - 1; i > position; i-- ) {
		values[i] = values[i - 1];
		ids[i] = ids[i - 1];
	}

	values[position] = value;
	ids[position] = id;
	used++;
}


void StringArray::remove( std::string value ) {
	int position = -1;

	// Find the position of value.
	for( int i = 0; i < used; i++ ) {
		if( values[i] == value ) {
			position = i;
			break;
		}
	}

	if( position >= 0 ) {
		// Move values forward.
		for( int i = position; i < used - 1; i++ ) {
			values[i] = values[i + 1];
			ids[i] = ids[i + 1];
		}

		values[used - 1] = "";
		ids[used - 1] = 0;
		used--;
	}
	else
		std::cout << "StringArray: Unable to remove value " << value << "\n";
}


void StringArray::remove( int id ) {
	int position = -1;

	// Find the position of value.
	for( int i = 0; i < used; i++ ) {
		if( ids[i] == id ) {
			position = i;
			break;
		}
	}

	if( position >= 0 ) {
		// Move values forward.
		for( int i = position; i < used - 1; i++ ) {
			values[i] = values[i + 1];
			ids[i] = ids[i + 1];
		}

		values[used - 1] = "";
		ids[used - 1] = 0;
		used--;
	}
	else
		std::cout << "StringArray: Unable to remove id " << id << "\n";
}


void StringArray::removeAll() {
	for( int i = 0; i < used; i++ ) {
		values[i] = "";
		ids[i] = 0;
	}

	used = 0;
}


int StringArray::getID( std::string value ) {
	int index = used / 2;
	int prevone = 0;
	int prevtwo = 0;
	int increment = index;
	int position = -1;
	int depth = 0;

	// Find the position of value.
	while( depth < used ) {
		if( increment >= 2 )
			increment /= 2;
		else
			increment = 1;

		if( index < 0 )
			break;
		else if( index >= used )
			break;

		if( value == values[index] ) {
			position = index;
			break;
		}
		else if( value < values[index] )
			index -= increment;
		else
			index += increment;

		if( index == prevtwo )
			break;

		prevtwo = prevone;
		prevone = index;

		depth++;
	}

	if( position >= 0 )
		return ids[position];
	else
		return 0;
}


const int* StringArray::getAllIDs() {
	return ids;
}


const int StringArray::getSize() { return used; }


void StringArray::print() {
	std::cout << "---String Array (" << used << " / " << size << ") ---\n";

	for( int i = 0; i < size; i++ )
		std::cout << "Value (" << i << "):  " << values[i] << "\tID:  " << ids[i] << "\n";

	std::cout << "---String Array---\n";
}
