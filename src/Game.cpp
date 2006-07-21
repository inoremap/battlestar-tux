/* Game.cpp
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


#include <math.h>
#include <SDL.h>

#include "Config.h"
#include "Fighter/Fighter.h"
#include "FighterAmmoList.h"
#include "Game.h"
#include "TextureManager.h"


Game::Game() {
	startTime = SDL_GetTicks();
	lastTime = 0;

	finished = false;
	paused = false;

	desiredFps = 50.0;
	fps = desiredFps;

	frame = 0;
	gameFrame = 0;
	lastGameFrame = 0;

	gameSpeed = 1;

	syncSleep = 5;

	bounds[0] = 40;
	bounds[1] = 30;

	scrollSpeed = 0.1;

	config = 0;
	textureManager = 0;

	enemyFighterList = 0;
	explosionList = 0;
	enemyAmmoList = 0;
	heroAmmoList = 0;
	fighter = 0;
}


void Game::newGame() {
	
}


void Game::pause() {
	if( paused ) {
		if( config->getGrabInput() ) {
			// Grab the Keyboard and Mouse
			SDL_WM_GrabInput( SDL_GRAB_ON );

			// Don't actually show the cursor
			SDL_ShowCursor( SDL_DISABLE );
		}

		paused = false;
	}
	else {
		if( config->getGrabInput() ) {
			// Release the Keyboard and Mouse
			SDL_WM_GrabInput( SDL_GRAB_OFF );

			// Show the cursor
			SDL_ShowCursor( SDL_ENABLE );
		}

		paused = true;
	}
}


void Game::startFrame() {
	unsigned int curTime = SDL_GetTicks();

	frame++;
	if( config->getDebug() && frame%200 == 0 ) {
		fps = ((float) frame) / (((float) curTime - (float) startTime) / 1000);
		printf( "Frame: %8u   ---   Game Frame: %8u   ---   Last Frame: %8u   ---   Time: %f   ---   FPS: %f   ---   Sleep: %3i\n", frame, gameFrame, lastGameFrame, (float) (curTime - startTime) / 1000, fps, syncSleep );
	}

	// Calculate how many frames we should have drawn up to now.
	gameFrame = (int) floor( ((float) curTime - (float) startTime) / 1000 * desiredFps );

	// Calculate how much we should be sleeping between frames.
	int lag = gameFrame - lastGameFrame;
	if( lag <= 0 ) {		// We're going too fast.
		//syncSleep++;
		gameSpeed = 0;
	}
	else if( lag == 1 )		// Exactly correct.
		gameSpeed = 1;
	else {					// We need to go faster, if possible.
		//syncSleep--;
		gameSpeed = lag;
	}

	lastTime = curTime;
	SDL_Delay( syncSleep );
}


void Game::stopFrame() {
	lastGameFrame = gameFrame;
}


unsigned int Game::getGameFrame() { return gameFrame; }
int Game::getGameSpeed() { return gameSpeed; }
float* Game::getBounds() { return bounds; }
float Game::getScrollSpeed() { return scrollSpeed; }

Config* Game::getConfig() { return config; }
void Game::setConfig( Config* c ) { config = c; }

TextureManager* Game::getTextureManager() { return textureManager; }
void Game::setTextureManager( TextureManager* t ) { textureManager = t; }

EnemyFighterList* Game::getEnemyFighterList() { return enemyFighterList; }
void Game::setEnemyFighterList( EnemyFighterList* l ) { enemyFighterList = l; }

ExplosionList* Game::getExplosionList() { return explosionList; }
void Game::setExplosionList( ExplosionList* l ) { explosionList = l; }

FighterAmmoList* Game::getEnemyAmmoList() { return enemyAmmoList; }
void Game::setEnemyAmmoList( FighterAmmoList* l ) { enemyAmmoList = l; }

FighterAmmoList* Game::getHeroAmmoList() { return heroAmmoList; }
void Game::setHeroAmmoList( FighterAmmoList* l ) { heroAmmoList = l; }

Fighter* Game::getFighter() { return fighter; }
void Game::setFighter( Fighter* f ) { fighter = f; }
