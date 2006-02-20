/* main.cpp
 *
 * Copyright 2005-2006 Eliot Eshelman
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Config.h"
#include "EnemyFighterList.h"
#include "Fighter/EnemyFighter.h"
#include "Fighter/HeroFighter.h"
#include "FighterAmmo.h"
#include "FighterAmmoList.h"
#include "Game.h"
#include "Ground.h"
#include "HUD.h"
#include "Screen.h"

using namespace std;

int main(int argc, char* argv[])
{
	int x = 0;
	int y = 0;
	float realWidth = 0.0;
	float realHeight = 0.0;
	Game* game = new Game();
	Config* config = new Config( game );
	Screen* screen = new Screen();
	SDL_Event event;

	// Exit if there is no screen.
	if( screen->isNull() ) {
		game->exitBT();
		return 1;
	}

	HUD* hud = new HUD( game );
	Ground* ground = new Ground( SOLID_GROUND, game );

	HeroFighter* hero = new HeroFighter( BASIC_FIGHTER, game );
	game->setFighter( hero );

	FighterAmmoList* heroAmmoList = new FighterAmmoList( game );
	game->setHeroAmmoList( heroAmmoList );

	EnemyFighterList* enemies = new EnemyFighterList( game );
	game->setEnemyFighterList( enemies );

	FighterAmmoList* enemyAmmoList = new FighterAmmoList( game );
	game->setEnemyAmmoList( enemyAmmoList );

	EnemyFighter* enemyFighter = 0;

	// Loop - drawing until application is finished.
	while( !game->isFinished() ) {
		game->startFrame();

		// If not paused, update all positions/states.
		if( !game->isPaused() ) {
			if( game->getGameFrame()%150 == 0 && game->getGameSpeed() != 0 ) {
				enemyFighter = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
				enemyFighter->setPos( 0, 40 );
				enemyFighter->setVel( 0, -0.2, 0 );
				enemies->addObject( enemyFighter );
				enemyFighter = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
				enemyFighter->setPos( 10, 45 );
				enemyFighter->setVel( 0, -0.2, 0 );
				enemyFighter->startFiring();
				enemies->addObject( enemyFighter );
				enemyFighter = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
				enemyFighter->setPos( -10, 45 );
				enemyFighter->setVel( 0, -0.2, 0 );
				enemies->addObject( enemyFighter );
			}

			// Get cursor position and then set fighter position.
			SDL_GetMouseState( &x, &y );
			realWidth = (float) x - (float) screen->getWidth() / 2;
			realHeight = (float) y - (float) screen->getHeight() / 2;
			realWidth = realWidth / ((float) screen->getWidth() / 2);
			realHeight = realHeight / ((float) screen->getHeight() / 2);
			hero->setPos( realWidth * game->getBounds()[0], 1.0 - realHeight * game->getBounds()[1] );
			hero->Update();

			heroAmmoList->Update();
			heroAmmoList->CullObjects( CULL_TOP );

			enemyAmmoList->Update();
			enemyAmmoList->CullObjects( CULL_BOTTOM );

			enemies->Update();
			enemies->CullObjects( CULL_BOTTOM );

			enemies->CheckCollisions( heroAmmoList );
			enemyAmmoList->CheckCollisions( hero );
			enemies->CheckCollisions( hero );
		}


		// Don't need to clear the screen, because the
		// entire area will be drawn again.  +20fps
		// glClear( GL_COLOR_BUFFER_BIT );

		// Draw stuff...
		glLoadIdentity();

		// As long as we draw in order, we don't need depth testing.
		ground->Draw();
		//draw ground units
		enemyAmmoList->DrawObjects();
		heroAmmoList->DrawObjects();
		enemies->DrawObjects();
		hero->Draw();
		//draw shield
		//draw power ups
		hud->Draw();

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

						case SDLK_p:
							game->pause();
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
		if( SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1) )
			hero->startFiring();
		else
			hero->stopFiring();


		// Check for OpenGL errors.


		game->stopFrame();
	}

	SDL_Quit();

    return 0;
}
