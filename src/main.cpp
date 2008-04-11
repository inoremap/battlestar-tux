/* main.cpp
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


#include <SDL.h>
#include <math.h>

#include "Config.h"
#include "Game.h"
#include "MainMenu.h"
#include "Screen.h"
#include "TextureManager.h"

using namespace std;

int main(int argc, char* argv[])
{
	Game* game = getGame();
	Config* config = new Config( game );
	config->parseCommandline( argc, argv );
	game->setConfig( config );
	TextureManager* textureManager = new TextureManager();
	game->setTextureManager( textureManager );
	Screen* screen = new Screen( game );
	game->setScreen( screen );

	// Exit if there is no screen.
	if( screen->isNull() ) {
		game->exitBT();
		return 1;
	}

	// Loop - drawing until application is finished.
	while( !game->isFinished() ) {
		MainMenu* menu = new MainMenu( OPENING_MENU, game );
		menu->ShowMenu();
		delete menu;
	}

	SDL_Quit();

    return 0;
}
