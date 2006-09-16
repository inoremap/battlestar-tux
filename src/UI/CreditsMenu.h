/* CreditsMenu.h
 *
 * Copyright 2006 Eliot Eshelman
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


#ifndef CREDITSMENU_H_
#define CREDITSMENU_H_

#include "GUI.h"
#include "../Game.h"
#include "MainMenu.h"
#include "Primitives/ButtonClickEvent.h"
#include "Primitives/ButtonClickListener.h"

/* Display list of credits. */
class CreditsMenu : public GUI, ButtonClickListener {
	public:
				CreditsMenu( MainMenu* menu, Game* g, int w, int h );
				~CreditsMenu();

				// Create all widgets and bind listeners.
				void CreateWidgets();

				// Button click event.
				void EventGenerated( ButtonClickEvent* e );

	private:
				CreditsMenu( const CreditsMenu &menu );
				const CreditsMenu & operator= ( const CreditsMenu &menu );

				// Main menu selects what menu is currently visible.
				MainMenu* mainMenu;

				Game* game;
};


#endif /*CREDITSMENU_H_*/
