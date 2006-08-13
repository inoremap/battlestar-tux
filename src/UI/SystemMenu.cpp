/* SystemMenu.cpp
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


#include <SDL_opengl.h>

#include "SystemMenu.h"
#include "Primitives/PlanetButton.h"
#include "../TextureManager.h"

SystemMenu::SystemMenu( Game* g ) {
	game = g;
}


SystemMenu::~SystemMenu() {}


void SystemMenu::ShowMenu() {
	SDL_Event event;

	PlanetButton* p1 = new PlanetButton( 3, 35, 1.0, 30.0, 0.0, game );
	PlanetButton* p2 = new PlanetButton( 2.5, 35, 2.0, -70.0, 0.0, game );

	// Enable lighting.
	glShadeModel( GL_SMOOTH );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	float lightPos[] = { 100, 0.0, 40.0, 0.0 };
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDif[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, lightPos );

	// Depth testing is needed for 3D spheres.
	glEnable( GL_DEPTH_TEST );

	// Continue displaying menu until the menu is closed or the game is exited.
	while( !game->isFinished() ) {
		game->startFrame();

		// Update information.
		p1->Update();
		p2->Update();

		// Don't need to clear the screen, because the
		// entire area will be drawn again.  +20fps
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// Set camera position and draw stuff...
		glLoadIdentity();
		glTranslatef( 0, 0, -15 );

		// As long as we draw in order, we don't need depth testing.
		glPushMatrix();
			glTranslatef( 0.0, 8.0, 0.0 );
			p1->Draw();
		glPopMatrix();
		p2->Draw();

		// Swap buffers - the newly drawn items will appear.
		SDL_GL_SwapBuffers();

		// Read all events off the queue.
		while( !game->isFinished() && SDL_PollEvent(&event) ) {
			switch( event.type ) {
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym ) {
						case SDLK_ESCAPE:
							game->exitBT();
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

	// SystemMenu is finished or was aborted.
}
