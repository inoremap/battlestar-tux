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


#include <string>
#include <iostream>

#include "Config.h"


Config::Config( Game* g ) {
	game = g;

	debug = false;
	wireframe = false;
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
		else if( argument == "--wireframe" )
			wireframe = true;
		else
			usage = true;
	}

	printGreeting();
	if( usage )
		printUsage();
}


void Config::printGreeting() {
	std::cout << "Battlestar T.U.X.";
	std::cout << "\n  Copyright (C) 2005-2006 Eliot Eshelman <eliot@6by9.net>";
	std::cout << "\n";
	std::cout << "\n  Battlestar Tux is free software; you can redistribute it and/or modify";
	std::cout << "\n  it under the terms of the GNU General Public License as published by";
	std::cout << "\n  the Free Software Foundation; version 2 of the License.";
	std::cout << "\n";
	std::cout << "\n  See http://6by9.net/code/battlestar/ for the latest updates.";
	std::cout << "\n\n";
}


void Config::printUsage() {
	std::cout << "Usage: battlestarTUX [options]";
	std::cout << "\n    Options:";
	std::cout << "\n       --debug       Enable debugging.  Extra game-state messages will be printed.";
	std::cout << "\n       --wireframe   Draw all polygons in wireframe.  For debugging.";
	std::cout << "\n       --no-grab     Do not grab mouse input - the cursor will not stay inside the window.";
	std::cout << "\n\n";
}


bool Config::getDebug() { return debug; }

bool Config::getWireframe() { return wireframe; }

bool Config::getGrabInput() { return grabInput; }
