/* MainMenu.h
 *
 * Copyright 2006-2008 Eliot Eshelman
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


#ifndef MAINMENU_H_
#define MAINMENU_H_

#include <FTGLTextureFont.h>

#include "Battle.h"
#include "Game.h"

class GUI;

// Possible menu screens.
enum MenuType {
	NULL_MENU,				// No menu.
	OPENING_MENU,			// Menu shown at startup.
	NEW_CAMPAIGN_MENU,		// Start a new game.
	LOAD_CAMPAIGN_MENU,		// Load an existing game.
	SETTINGS_MENU,			// Game settings and options.
	CREDITS_MENU,			// Game credits.
	SYSTEM_MENU				// Show solar system the ship is currently in.
};

/* Parent menu.  All other menus are spawned here. */
class MainMenu {
	public:
				MainMenu( MenuType t );
				~MainMenu();

				// Show current menu.
				void ShowMenu();

				// Change the menu being displayed.
				void ChangeMenu( MenuType t );

				FTFont* getFont();
				FTFont* getItalicFont();
				FTFont* getBoldFont();

	private:
				MainMenu( const MainMenu &menu );
				const MainMenu & operator= ( const MainMenu &menu );

				// Generate a new menu.
				void GenerateMenu();

				// Current menu type.
				MenuType currentType;

				// Menu type to change to.
				MenuType nextType;

				// Menu that is currently being displayed.
				GUI* currentMenu;

				FTFont* normalFont;
				FTFont* italicFont;
				FTFont* boldFont;

				// Battle/Campaign event
				Battle* battle;

				Game* game;
};


#endif /*MAINMENU_H_*/
