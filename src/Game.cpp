/* Game.cpp
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


#include "math.h"
#include "SDL.h"

#include "Game.h"

bool Game::finished = false;
float Game::desiredFps = 50.0;
float Game::fps = desiredFps;
unsigned int Game::frame = 0;
unsigned int Game::gameFrame = 0;
unsigned int Game::lastGameFrame = 0;
float Game::gameSpeed = 1.0;
unsigned int Game::startTime = 0;
unsigned int Game::lastTime = 0;
int Game::syncSleep = 5;
float Game::bounds[2] = { 40, 30 };
float Game::scrollSpeed = 0.1;
Game* Game::instance = 0;


Game::Game() {
	startTime = SDL_GetTicks();
}


Game* Game::getInstance() {
	if( ! instance )
		instance = new Game();

	return instance;
}


void Game::newGame() {
	
}


void Game::startFrame() {
	unsigned int curTime = SDL_GetTicks();

	frame++;
	if( frame%200 == 0 ) {
		fps = ((float) frame) / (((float) curTime - (float) startTime) / 1000);
		printf( "Frame: %8i   ---   Game Frame: %8i   ---   Last Frame: %8i   ---   Time: %f   ---   FPS: %f   ---   Sleep: %3i\n", frame, gameFrame, lastGameFrame, (float) (curTime - startTime) / 1000, fps, syncSleep );
	}

	// Calculate how many frames we should have drawn up to now.
	gameFrame = (int) floor( ((float) curTime - (float) startTime) / 1000 * desiredFps );

	// Calculate how much we should be sleeping between frames.
	int lag = gameFrame - lastGameFrame;
	if( lag <= 0 ) {		// We're going too fast.
		//syncSleep++;
		gameSpeed = 0.0;
	}
	else if( lag == 1 )		// Exactly correct.
		gameSpeed = 1.0;
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


int Game::getGameFrame() { return gameFrame; }
float Game::getGameSpeed() { return gameSpeed; }
float* Game::getBounds() { return bounds; }
float Game::getScrollSpeed() { return scrollSpeed; }
