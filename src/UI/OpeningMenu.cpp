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


#include "OpeningMenu.h"
#include "Primitives/VerticalPane.h"
#include "Primitives/Button.h"

OpeningMenu::OpeningMenu( int w, int h ) : GUI( w, h ) {
}


OpeningMenu::~OpeningMenu() {}


void OpeningMenu::CreateWidgets() {
	// Create widgets for Opening Menu.
	VerticalPane* vPane = new VerticalPane( this, true, HORIZ_CENTER );
	Button* button = new Button( this, " New Campaign ", HORIZ_CENTER );
	vPane->AddWidget( button );
	button = new Button( this, " Load Campaign ", HORIZ_CENTER );
	vPane->AddWidget( button );
	button = new Button( this, "Settings", HORIZ_CENTER );
	vPane->AddWidget( button );
	button = new Button( this, "Credits", HORIZ_CENTER );
	vPane->AddWidget( button );
	button = new Button( this, "Exit", HORIZ_CENTER );
	vPane->AddWidget( button );
	vPane->setPos( CONTAINER_MC );
	addObject( vPane );
}


void OpeningMenu::EventGenerated( Event* e ) {
}
