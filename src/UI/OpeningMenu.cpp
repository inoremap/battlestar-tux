/* OpeningMenu.cpp
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


#include <string>
#include <iostream>

#include "Button.h"
#include "Label.h"
#include "OpeningMenu.h"
#include "VerticalPane.h"

OpeningMenu::OpeningMenu( MainMenu* menu, int w, int h ) : GUI( w, h, menu ) {
	mainMenu = menu;
	game = Game::getGame();
}


OpeningMenu::~OpeningMenu() {}


void OpeningMenu::CreateWidgets() {
	// Create widgets for Opening Menu.
	VerticalPane* initial = new VerticalPane( this, true, HORIZ_CENTER, VERTI_CENTER );
	Button* button = new Button( this, " New Campaign ", HORIZ_CENTER, VERTI_CENTER );
	button->AddListener( this );
	initial->AddWidget( button );
	button = new Button( this, " Load Campaign ", HORIZ_CENTER, VERTI_CENTER );
	button->AddListener( this );
	initial->AddWidget( button );
	button = new Button( this, "Settings", HORIZ_CENTER, VERTI_CENTER );
	button->AddListener( this );
	initial->AddWidget( button );
	button = new Button( this, "Credits", HORIZ_CENTER, VERTI_CENTER );
	button->AddListener( this );
	initial->AddWidget( button );
	button = new Button( this, "Exit", HORIZ_CENTER, VERTI_CENTER );
	button->AddListener( this );
	initial->AddWidget( button );

	initial->setPos( CONTAINER_MC );
	addObject( initial );
}


void OpeningMenu::EventGenerated( ButtonClickEvent* e ) {
	std::string text = e->getButtonText();

	if( text == " New Campaign " )
		mainMenu->ChangeMenu( NEW_CAMPAIGN_MENU );

	else if( text == " Load Campaign " )
		mainMenu->ChangeMenu( LOAD_CAMPAIGN_MENU );

	else if( text == "Settings" )
		mainMenu->ChangeMenu( SETTINGS_MENU );

	else if( text == "Credits" )
		mainMenu->ChangeMenu( CREDITS_MENU );

	else if( text == "Exit" )
		game->exitBT();
}
