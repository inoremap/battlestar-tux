/* MainMenu.cpp
 *
 * Copyright 2006 Eliot Eshelman
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


#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>

#include "GUI.h"
#include "LoadCampaignMenu.h"
#include "MainMenu.h"
#include "NewCampaignMenu.h"
#include "CreditsMenu.h"
#include "OpeningMenu.h"
#include "SettingsMenu.h"
#include "SystemMenu.h"
#include "../Screen.h"

MainMenu::MainMenu( MenuType t, Game* g ) {
	currentType = nextType = t;
	game = g;
	currentMenu = NULL;

	// Load normal font.
	std::string normalFontFile = "data/fonts/forgottenfuturist.ttf";
	normalFont = new FTGLTextureFont( normalFontFile.c_str() );
	if( normalFont->Error() )
		std::cout << "Unable to open font file: " << normalFontFile << "\n";
	normalFont->FaceSize( 30 );
	normalFont->CharMap( ft_encoding_unicode );
	if( normalFont->Error() )
		std::cout << "Unable to set font parameters: " << normalFontFile << "\n";

	// Load italic font.
	std::string italicFontFile = "data/fonts/forgottenfuturist_i.ttf";
	italicFont = new FTGLTextureFont( italicFontFile.c_str() );
	if( italicFont->Error() )
		std::cout << "Unable to open font file: " << italicFontFile << "\n";
	italicFont->FaceSize( 30 );
	italicFont->CharMap( ft_encoding_unicode );
	if( italicFont->Error() )
		std::cout << "Unable to set font parameters: " << italicFontFile << "\n";

	// Load bold font.
	std::string boldFontFile = "data/fonts/forgottenfuturist_b.ttf";
	boldFont = new FTGLTextureFont( boldFontFile.c_str() );
	if( boldFont->Error() )
		std::cout << "Unable to open font file: " << boldFontFile << "\n";
	boldFont->FaceSize( 30 );
	boldFont->CharMap( ft_encoding_unicode );
	if( boldFont->Error() )
		std::cout << "Unable to set font parameters: " << boldFontFile << "\n";
}


MainMenu::~MainMenu() {
	delete normalFont;
	delete italicFont;
	delete boldFont;
}


void MainMenu::ShowMenu() {
	GenerateMenu();

	SDL_Event event;

	// Continue displaying menu until the menu is closed or the game is exited.
	while( !game->isFinished() ) {
		game->startFrame();

		// Clear the buffers.
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// Update menu.
		currentMenu->Update();

		// Event listeners are called during Update().  The current menu may have changed.
		if( nextType != NULL_MENU )
			GenerateMenu();

		// Draw menu.
		currentMenu->Draw();

		// Swap buffers - the newly drawn items will appear.
		SDL_GL_SwapBuffers();

		// Read all events off the queue.
		while( !game->isFinished() && SDL_PollEvent(&event) ) {
			switch( event.type ) {
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym ) {
						case SDLK_ESCAPE:
							if( currentType == OPENING_MENU )
								game->exitBT();
							else
								ChangeMenu( OPENING_MENU );
							break;

						default:
							break;
					}
					break;

				case SDL_QUIT:
					game->exitBT();
					break;

				default:
					break;
			}
		}

		// Check for OpenGL errors.

		game->stopFrame();
	}
	// Menu is finished or was aborted.
}


void MainMenu::ChangeMenu( MenuType t ) { nextType = t; }


void MainMenu::GenerateMenu() {
	if( currentMenu )
		delete currentMenu;

	currentType = nextType;
	nextType = NULL_MENU;

	switch( currentType ) {
		case OPENING_MENU:
		case NULL_MENU:
		default:
			currentMenu = new OpeningMenu( this, game, game->getScreen()->getWidth(), game->getScreen()->getHeight() );
			break;

		case NEW_CAMPAIGN_MENU:
			currentMenu = new NewCampaignMenu( this, game, game->getScreen()->getWidth(), game->getScreen()->getHeight() );
			break;

		case LOAD_CAMPAIGN_MENU:
			currentMenu = new LoadCampaignMenu( this, game, game->getScreen()->getWidth(), game->getScreen()->getHeight() );
			break;

		case SETTINGS_MENU:
			currentMenu = new SettingsMenu( this, game, game->getScreen()->getWidth(), game->getScreen()->getHeight() );
			break;

		case CREDITS_MENU:
			currentMenu = new CreditsMenu( this, game, game->getScreen()->getWidth(), game->getScreen()->getHeight() );
			break;

		case SYSTEM_MENU:
			currentMenu = new SystemMenu( this, game, game->getScreen()->getWidth(), game->getScreen()->getHeight() );
			break;
	}

	currentMenu->CreateWidgets();
}

FTFont* MainMenu::getFont() { return normalFont; }
FTFont* MainMenu::getItalicFont() { return italicFont; }
FTFont* MainMenu::getBoldFont() { return boldFont; }
