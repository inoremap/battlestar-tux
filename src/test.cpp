/* test.cpp
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


#include <SDL.h>
#include <iostream>
#include <math.h>

#include "Simplex.h"


using namespace std;

int main(int argc, char* argv[])
{
	float octaves = 0.0;
	float persist = 0.0;

	cin >> octaves;
	cin >> persist;

	for( float n = 0.0; n < 100; n += 0.1 )
		//cout << n << "\t" << simplexRawNoise( n, n ) << endl;
		//cout << n << "\t" << simplexScaledNoise( -1, 1, n, n ) << endl;
		cout << n << "\t" << simplexNoise( octaves, persist, 1, n, n ) << endl;


	SDL_Quit();

	return 0;
}
