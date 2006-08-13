/* MainMenu.h
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


#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "GUI.h"
#include "../Game.h"

// Possible menu screens.
enum MenuType {
	OPENING_MENU		=	0,	// Menu shown at startup.
	SETTINGS_MENU	=	1,	// Game settings and options.
	CREDITS_MENU		=	2,	// Game credits.
	SYSTEM_MENU		=	3	// Show solar system the ship is currently in.
};

/* Parent menu.  All other menus are spawned here. */
class MainMenu {
	public:
				MainMenu( MenuType t, Game* g );
				~MainMenu();

				// Show current menu.
				void ShowMenu();

				// Change the menu being displayed.
				void ChangeMenu( MenuType t );

	private:
				MainMenu( const MainMenu &menu );
				const MainMenu & operator= ( const MainMenu &menu );

				// Current menu type.
				MenuType currentType;

				// Menu that is currently being displayed.
				GUI* currentMenu;

				Game* game;
};


#endif /*MAINMENU_H_*/
