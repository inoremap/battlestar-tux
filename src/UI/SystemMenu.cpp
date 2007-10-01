/* SystemMenu.cpp
 *
 * Copyright 2006-2007 Eliot Eshelman
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


#include <SDL_opengl.h>

#include "HorizontalPane.h"
#include "SystemMenu.h"

SystemMenu::SystemMenu( MainMenu* menu, Game* g, int w, int h ) : GUI( w, h, menu ) {
	solarSystem = new SolarSystem( vec3(1, 1, 1) );
	std::cout << solarSystem;
	mainMenu = menu;
	game = g;
}


SystemMenu::~SystemMenu() {}


void SystemMenu::CreateWidgets() {
	// Create widgets for System Menu.
}


void SystemMenu::EventGenerated( ButtonClickEvent* e ) {
	std::string text = e->getButtonText();
}


void SystemMenu::Draw() {
	// Draw GUI objects that don't need lighting.
	GUI::Draw();

	// Set star system OpenGL lighting requirements.
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	float lightPos[] = { -1000, 0.0, 100.0, 0.0 };
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDif[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, lightPos );

	// Draw GUI objects that need lighting.
	GUI::SecondDraw();

	// Return to standard OpenGL settings.
	glDisable( GL_LIGHT0 );
	glDisable( GL_LIGHTING );

	solarSystem->Update();
	solarSystem->Draw();
}
