/* Config.h
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


#ifndef CONFIG_H_
#define CONFIG_H_

#include "Game.h"


/* Stores game configuration. */
class Config {
	public:
				Config( Game* g );
				~Config();

				// Read command line arguments and set
				// variable appropriately.  Print  usage
				// if illegal arguments are specified.
				void parseCommandline( int argc, char* argv[] );

				// Print initial Battlestar T.U.X. greeting message
				void printGreeting();

				// Print list of legal arguments
				void printUsage();

				bool getDebug();

				bool getGrabInput();

	private:
				Config( const Config &config );
				const Config & operator= ( const Config &config );

				// True when debugging application.
				bool debug;

				// Capturing the keyboard and mouse means the
				// user can't user either until the application
				// exits or releases control.  This is bad if
				// the game freezes or crashes.
				bool grabInput;

				Game* game;
};


#endif /*CONFIG_H_*/
