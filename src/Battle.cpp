/* Battle.cpp
 *
 * Copyright 2005-2006 Eliot Eshelman
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


#include "Battle.h"
#include "Config.h"
#include "EnemyFighter.h"
#include "FighterAmmo.h"
#include "TextureManager.h"

Battle::Battle( Game* g ) {
	game = g;

	aborted = false;
	finished = false;

	screen = game->getScreen();

	aDown = false;
	uDown = false;

	hud = new HUD( game );
	ground = new Ground( SOLID_GROUND, game );

	hero = new HeroFighter( BASIC_FIGHTER, game );
	game->setFighter( hero );

	heroAmmoList = new FighterAmmoList( game );
	game->setHeroAmmoList( heroAmmoList );

	enemies = new EnemyFighterList( game );
	game->setEnemyFighterList( enemies );

	explosionList = new ExplosionList( game );
	game->setExplosionList( explosionList );

	enemyAmmoList = new FighterAmmoList( game );
	game->setEnemyAmmoList( enemyAmmoList );
}


Battle::~Battle() {
	delete hud;
	delete ground;
	delete hero;
	delete heroAmmoList;
	delete enemies;
	delete explosionList;
	delete enemyAmmoList;
}


void Battle::Update() {
	int x = 0;
	int y = 0;
	float realWidth = 0.0;
	float realHeight = 0.0;

	SDL_Event event;

	// If not paused, update all positions/states.
	if( !game->isPaused() ) {
		EnemyFighter* enemyFighter = 0;

		if( game->getGameFrame()%150 == 0 && game->getGameSpeed() != 0 ) {
			for( int n=0; n < 20; n+=4 ) {
				enemyFighter = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
				enemyFighter->setPos( -40 + 4 * n, 40 );
				enemyFighter->setVel( 0, -0.2, 0 );
				enemyFighter->setRot( 180 );
				enemyFighter->startFiring();
				enemies->addObject( enemyFighter );
			}
		}

		// Get cursor position and then set fighter position.
		SDL_GetMouseState( &x, &y );
		realWidth = (float) x - (float) screen->getWidth() / 2;
		realHeight = (float) y - (float) screen->getHeight() / 2;
		realWidth = realWidth / ((float) screen->getWidth() / 2);
		realHeight = realHeight / ((float) screen->getHeight() / 2);
		hero->setPos( realWidth * game->getBounds()[0], 1.0 - realHeight * game->getBounds()[1] );
		hero->Update();
		if( hero->getHealth() <= 0 )
			FinishBattle();

		heroAmmoList->UpdateObjects();
		heroAmmoList->CullObjects( CULL_TOP );

		enemyAmmoList->UpdateObjects();
		enemyAmmoList->CullObjects( CULL_BOTTOM );

		enemies->UpdateObjects();
		enemies->CullObjects( CULL_BOTTOM );

		enemies->CheckCollisions( heroAmmoList );
		enemyAmmoList->CheckCollisions( hero );
		enemies->CheckCollisions( hero );

		explosionList->Update();

		ground->Update();
	}

	// Read all events off the queue.
	if( aDown )
		hero->getWeaponSystem()->SetTarget( hero->getWeaponSystem()->getTarget() + 0.5 );
	if( uDown )
		hero->getWeaponSystem()->SetTarget( hero->getWeaponSystem()->getTarget() - 0.5 );
	while( !game->isFinished() && !isFinished() && !isAborted() && SDL_PollEvent(&event) ) {
		switch( event.type ) {
			case SDL_KEYDOWN:
				switch( event.key.keysym.sym ) {
					case SDLK_ESCAPE:
						AbortBattle();
						break;

					case SDLK_a:
						aDown = true;
						break;

					case SDLK_u:
						uDown = true;
						break;

					case SDLK_p:
						game->pause();
						break;

					default:
						break;
				}
				break;

			case SDL_KEYUP:
				switch( event.key.keysym.sym ) {
					case SDLK_a:
						aDown = false;
						break;

					case SDLK_u:
						uDown = false;
						break;

					default:
						break;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				if( event.button.button == SDL_BUTTON_LEFT )
					hero->startFiring();
				break;

			case SDL_MOUSEBUTTONUP:
				if( event.button.button == SDL_BUTTON_LEFT )
					hero->stopFiring();
				else if( event.button.button == SDL_BUTTON_WHEELUP )
					screen->setFOVY( screen->getFOVY() - 2 );
				else if( event.button.button == SDL_BUTTON_WHEELDOWN )
					screen->setFOVY( screen->getFOVY() + 2 );
				break;

			case SDL_QUIT:
				game->exitBT();
				break;

			default:
				break;
		}
	}
}


void Battle::Draw() {
	// Disable depth testing.
	// Depth testing isn't needed for the 2.5D drawing.
	glDisable( GL_DEPTH_TEST );

	// Don't need to clear the screen, because the
	// entire area will be drawn again.  +20fps
	// glClear( GL_COLOR_BUFFER_BIT );

	// Set camera position and draw stuff...
	glLoadIdentity();
	glTranslatef( 0, 0, -15 );

	// As long as we draw in order, we don't need depth testing.
	ground->Draw();
	//draw ground units?
	enemyAmmoList->DrawObjects();
	heroAmmoList->DrawObjects();
	enemies->DrawObjects();
	hero->Draw();
	explosionList->Draw();
	//draw power ups
	hud->Draw();
}


void Battle::FinishBattle() { finished = true; }
bool Battle::isFinished() { return finished; }

void Battle::AbortBattle() { aborted = true; }
bool Battle::isAborted() { return aborted; }
