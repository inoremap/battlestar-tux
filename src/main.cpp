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

#include "EnemyFighterList.h"
#include "EnemyFighter.h"
#include "Fighter.h"
#include "FighterAmmo.h"
#include "FighterAmmoList.h"
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

	HUD* hud = new HUD( game );
	Ground* ground = new Ground( SOLID_GROUND, game );
	Fighter* fighter = new Fighter( BASIC_FIGHTER, game );
	game->setFighter( fighter );
	FighterAmmoList* fighterAmmoList = new FighterAmmoList( game );
	EnemyFighterList* enemies = new EnemyFighterList( game );

	EnemyFighter* enemyFighter = 0;
	FighterAmmo* fighterAmmo = 0;

	// Loop - drawing until application is finished.
	while( !game->isFinished() ) {

		// Check for OpenGL errors.

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

		// Don't need to clear the screen, because the
		// entire area will be drawn again.  +20fps
		// glClear( GL_COLOR_BUFFER_BIT );


		if( game->getGameFrame()%150 == 0 && game->getGameSpeed() != 0 ) {
			enemyFighter = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
			enemyFighter->setPos( 0, 40 );
			enemyFighter->setVel( 0, -0.2, 0 );
			enemies->addObject( enemyFighter );
			enemyFighter = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
			enemyFighter->setPos( 10, 45 );
			enemyFighter->setVel( 0, -0.2, 0 );
			enemies->addObject( enemyFighter );
			enemyFighter = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
			enemyFighter->setPos( -10, 45 );
			enemyFighter->setVel( 0, -0.2, 0 );
			enemies->addObject( enemyFighter );

			fighterAmmo = new FighterAmmo( BASIC_LASER, fighterAmmoList, game );
			fighterAmmo->setPos( fighter->getPos()[0], fighter->getPos()[1] );
			fighterAmmo->setVel( 0.0, 1.0, 0.0 );
			fighterAmmoList->addObject( fighterAmmo );
		}


		// Draw stuff...
		glLoadIdentity();

		// Get cursor position and then set fighter position.
		SDL_GetMouseState( &x, &y );
		realWidth = (float) x - (float) screen->getWidth() / 2;
		realHeight = (float) y - (float) screen->getHeight() / 2;
		realWidth = realWidth / ((float) screen->getWidth() / 2);
		realHeight = realHeight / ((float) screen->getHeight() / 2);
		fighter->setPos( realWidth * game->getBounds()[0], 1.0 - realHeight * game->getBounds()[1] );
		fighter->UpdatePos();

		fighterAmmoList->UpdatePositions();
		fighterAmmoList->CullObjects();

		enemies->UpdatePositions();
		enemies->CullObjects();
		enemies->CheckCollisions( fighter );

		// As long as we draw in order, we don't need depth testing.
		ground->Draw();
		//draw ground units
		//draw power ups
		//draw enemy ammo
		fighterAmmoList->DrawObjects();
		enemies->DrawObjects();
		fighter->Draw();
		//draw shield
		hud->Draw();

		// Swap buffers - the newly drawn items will appear.
		SDL_GL_SwapBuffers();

		game->stopFrame();
	}

	SDL_Quit();

    return 0;
}
