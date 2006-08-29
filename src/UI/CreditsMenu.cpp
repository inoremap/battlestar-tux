/* CreditsMenu.cpp
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

#include "CreditsMenu.h"
#include "Primitives/Button.h"
#include "Primitives/HorizontalContainer.h"
#include "Primitives/Label.h"
#include "Primitives/VerticalPane.h"

CreditsMenu::CreditsMenu( MainMenu* menu, Game* g, int w, int h ) : GUI( w, h ) {
	mainMenu = menu;
	game = g;
}


CreditsMenu::~CreditsMenu() {}


void CreditsMenu::CreateWidgets() {
	// Display Credits.
	VerticalPane* credits = new VerticalPane( this, true, HORIZ_CENTER );
	Label* label = new Label( this, "Battlestar TUX", HORIZ_CENTER );
	credits->AddWidget( label );
	label = new Label( this, " ", HORIZ_LEFT );
	credits->AddWidget( label );
	label = new Label( this, "created by: Eliot Eshelman", HORIZ_LEFT );
	credits->AddWidget( label );
	label = new Label( this, "Copyright 2005-2006 by Eliot Eshelman", HORIZ_LEFT );
	credits->AddWidget( label );
	label = new Label( this, "Released under the GPL, version 2", HORIZ_LEFT );
	credits->AddWidget( label );

	HorizontalContainer* closePanel = new HorizontalContainer( this, false, VERTI_CENTER );
	Button* button = new Button( this, "Close", HORIZ_RIGHT );
	button->AddListener( this );
	closePanel->AddWidget( button );
	credits->AddWidget( closePanel );

	credits->setPos( CONTAINER_MC );
	addObject( credits );
}


void CreditsMenu::EventGenerated( ButtonClickEvent* e ) {
	std::string text = e->getButtonText();

	if( text == "Close" )
		mainMenu->ChangeMenu( OPENING_MENU );
}
