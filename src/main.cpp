/* main.cpp
 *
 * Copyright 2005 Eliot Eshelman
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


#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "EnemyFighter.h"
#include "Fighter.h"
#include "Game.h"
#include "Ground.h"
#include "HUD.h"
#include "Screen.h"

using namespace std;

int main(int argc, char* argv[])
{
	Screen* screen = new Screen();
	int x = 0;
	int y = 0;
	float realWidth = 0.0;
	float realHeight = 0.0;
	Game* game = Game::getInstance();
	SDL_Event event;

	// Exit if there is no screen.
	if( screen->isNull() ) {
		game->exitBT();
		return 1;
	}

	Ground* ground = new Ground( SOLID_GROUND, game );
	Fighter* fighter = new Fighter( BASIC_FIGHTER, game );

	EnemyFighter* enemyFighter = new EnemyFighter( BASIC_ENEMY_FIGHTER, game );
	enemyFighter->setPos( 0, 40 );
	enemyFighter->setVel( 0, -0.2, 0 );

	// Loop - drawing until application is finished.
	while( !game->isFinished() ) {

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

		game->startFrame();

		// Clear screen before redrawing.
		glClear( GL_COLOR_BUFFER_BIT );


		// Draw stuff...
		glLoadIdentity();

		ground->Draw();

		// Get cursor position and then set fighter position.
		SDL_GetMouseState( &x, &y );
		realWidth = (float) x - (float) screen->getWidth() / 2;
		realHeight = (float) y - (float) screen->getHeight() / 2;
		realWidth = realWidth / ((float) screen->getWidth() / 2);
		realHeight = realHeight / ((float) screen->getHeight() / 2);
		fighter->setPos( realWidth * game->getBounds()[0], 1.0 - realHeight * game->getBounds()[1] );
		fighter->Draw();

		enemyFighter->UpdatePos();
		enemyFighter->Draw();

		// Swap buffers - the newly drawn items will appear.
		SDL_GL_SwapBuffers();

		game->stopFrame();
	}

	SDL_Quit();

    return 0;
}
