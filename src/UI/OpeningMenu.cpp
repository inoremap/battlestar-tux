/* OpeningMenu.cpp
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


#include <string>
#include <iostream>

#include "OpeningMenu.h"
#include "Primitives/Button.h"
#include "Primitives/Label.h"

OpeningMenu::OpeningMenu( MainMenu* menu, Game* g, int w, int h ) : GUI( w, h ) {
	mainMenu = menu;
	game = g;
}


OpeningMenu::~OpeningMenu() {}


void OpeningMenu::CreateWidgets() {
	// Create widgets for Opening Menu.
	initial = new VerticalPane( this, true, HORIZ_CENTER );
	Button* button = new Button( this, " New Campaign ", HORIZ_CENTER );
	button->AddListener( this );
	initial->AddWidget( button );
	button = new Button( this, " Load Campaign ", HORIZ_CENTER );
	button->AddListener( this );
	initial->AddWidget( button );
	button = new Button( this, "Settings", HORIZ_CENTER );
	button->AddListener( this );
	initial->AddWidget( button );
	button = new Button( this, "Credits", HORIZ_CENTER );
	button->AddListener( this );
	initial->AddWidget( button );
	button = new Button( this, "Exit", HORIZ_CENTER );
	button->AddListener( this );
	initial->AddWidget( button );
	initial->setPos( CONTAINER_MC );
	currentPane = initial;
	addObject( initial );

	// New campaign.
	newCampaign = new VerticalPane( this, true, HORIZ_CENTER );
	Label* label = new Label( this, "New Campaign", HORIZ_CENTER );
	newCampaign->AddWidget( label );
	newCampaign->setPos( CONTAINER_MC );

	// Load campaign.
	loadCampaign = new VerticalPane( this, true, HORIZ_CENTER );
	label = new Label( this, "Load Campaign", HORIZ_CENTER );
	loadCampaign->AddWidget( label );
	loadCampaign->setPos( CONTAINER_MC );

	// Change Settings
	settings = new VerticalPane( this, true, HORIZ_CENTER );
	label = new Label( this, "Settings", HORIZ_CENTER );
	settings->AddWidget( label );
	settings->setPos( CONTAINER_MC );

	// Display Credits.
	credits = new VerticalPane( this, true, HORIZ_CENTER );
	label = new Label( this, "Battlestar TUX", HORIZ_CENTER );
	credits->AddWidget( label );
	label = new Label( this, " ", HORIZ_LEFT );
	credits->AddWidget( label );
	label = new Label( this, "created by: Eliot Eshelman", HORIZ_LEFT );
	credits->AddWidget( label );
	label = new Label( this, "Copyright 2005-2006 by Eliot Eshelman", HORIZ_LEFT );
	credits->AddWidget( label );
	label = new Label( this, "Released under the GPL, version 2", HORIZ_LEFT );
	credits->AddWidget( label );
	credits->setPos( CONTAINER_MC );
}


void OpeningMenu::EventGenerated( ButtonClickEvent* e ) {
	std::string text = e->getButtonText();

	if( text == " New Campaign " ) {
		remObject( currentPane );
		currentPane = newCampaign;
		addObject( newCampaign );
	}

	else if( text == " Load Campaign " ) {
		remObject( currentPane );
		currentPane = loadCampaign;
		addObject( loadCampaign );
	}

	else if( text == "Settings" ) {
		remObject( currentPane );
		currentPane = settings;
		addObject( settings );
	}

	else if( text == "Credits" ) {
		remObject( currentPane );
		currentPane = credits;
		addObject( credits );
	}

	else if( text == "Exit" ) {
		game->exitBT();
	}
}
