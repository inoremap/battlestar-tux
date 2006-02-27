/* Config.cpp
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
#include <string>

#include "Config.h"


Config::Config( Game* g ) {
	game = g;

	debug = false;
	grabInput = true;
}


Config::~Config() {}


void Config::parseCommandline( int argc, char* argv[] ) {
	bool usage = false;

	// Iterate through arguments passed.
	// Ignore argument 0, which will be './battlestarTUX'.
	for( int i = 1; i < argc; i++ ) {
		std::string argument( argv[i] );

		if( argument == "--debug" )
			debug = true;
		else if( argument == "--no-grab" )
			grabInput = false;
		else
			usage = true;
	}

	printGreeting();
	if( usage )
		printUsage();
}


void Config::printGreeting() {
	printf( "Battlestar T.U.X." );
	printf( "\n  Copyright (C) 2005-2006 Eliot Eshelman <eliot@6by9.net>" );
	printf( "\n" );
	printf( "\n  Battlestar Tux is free software; you can redistribute it and/or modify" );
	printf( "\n  it under the terms of the GNU General Public License as published by" );
	printf( "\n  the Free Software Foundation; version 2 of the License." );
	printf( "\n" );
	printf( "\n  See http://6by9.net/code/battlestar/ for the latest updates." );
	printf( "\n\n" );
}


void Config::printUsage() {
	printf( "Usage: battlestarTUX [options]" );
	printf( "\n    Options:" );
	printf( "\n       --debug       Enable debugging.  Extra game-state messages will be printed." );
	printf( "\n       --no-grab     Do not grab mouse input - the cursor will not stay inside the window." );
	printf( "\n\n" );
}


bool Config::getDebug() { return debug; }

bool Config::getGrabInput() { return grabInput; }
