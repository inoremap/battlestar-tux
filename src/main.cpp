/* main.cpp
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Battle.h"
#include "Config.h"
#include "Game.h"
#include "Screen.h"
#include "TextureManager.h"
#include "UI/Button.h"
#include "UI/HorizontalContainer.h"
#include "UI/HorizontalPane.h"
#include "UI/VerticalContainer.h"
#include "UI/VerticalPane.h"

using namespace std;

int main(int argc, char* argv[])
{
	Game* game = new Game();
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

	GUI* gui = new GUI( screen->getWidth(), screen->getHeight() );
	VerticalPane* vPane = new VerticalPane( gui, true, HORIZ_CENTER );
	VerticalContainer* vContainer = new VerticalContainer( gui, true, HORIZ_CENTER );
	Button* button = new Button( gui, "Battlestar TUX|Test the ugly puppy.", HORIZ_CENTER );
	vContainer->AddWidget( button );
	button = new Button( gui, "Resume Game", HORIZ_CENTER );
	vContainer->AddWidget( button );
	button = new Button( gui, "Examine Inventory", HORIZ_CENTER );
	vContainer->AddWidget( button );
	button = new Button( gui, "Battlestar TUX|Test the ugly puppy.", HORIZ_CENTER );
	vContainer->AddWidget( button );
	HorizontalContainer* hContainer = new HorizontalContainer( gui, false, VERTI_TOP );
	hContainer->AddWidget( vContainer );
	button = new Button( gui, "Examine Inventory", HORIZ_CENTER );
	hContainer->AddWidget( button );
	button = new Button( gui, "Battlestar TUX|Test the ugly puppy.", HORIZ_CENTER );
	hContainer->AddWidget( button );
	vPane->AddWidget( hContainer );
	vPane->setPos( 50, 300 );
	gui->addObject( vPane );

	// Loop - drawing until application is finished.
	while( !game->isFinished() ) {
		Battle* battle = new Battle( game );
		battle->Start();

		/* Do something with the GUI?
		game->startFrame();

		gui->Update();
		gui->Draw();

		// Swap buffers - the newly drawn items will appear.
		SDL_GL_SwapBuffers();

		// Check for OpenGL errors.

		game->stopFrame();*/
	}

	SDL_Quit();

    return 0;
}
