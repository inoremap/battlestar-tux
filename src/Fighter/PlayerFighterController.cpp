/* PlayerFighterController.cpp
 *
 * Copyright 2007 Eliot Eshelman
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


#include "PlayerFighterController.h"

PlayerFighterController::PlayerFighterController( Battle* b, Screen* s, Fighter* f , Game* g ) : FighterController( f, g ) {
	battle = b;
	screen = s;

	// TODO: replace static settings with configuration panel
	pause = SDLK_p;
	accelUp = SDLK_COMMA;
	accelDown = SDLK_o;
	accelLeft = SDLK_a;
	accelRight = SDLK_u;

	isAccelUpOn = false;
	isAccelDownOn = false;
	isAccelLeftOn = false;
	isAccelRightOn = false;
}


PlayerFighterController::~PlayerFighterController() {
}


void PlayerFighterController::Update( int speed ) {
	// check for keypresses and mouse events
	// remember that two or three keys/buttons may be down!!
	SDL_Event event;
	while( !game->isFinished() && !battle->isFinished() && !battle->isAborted() && SDL_PollEvent(&event) ) {
		switch( event.type ) {
			case SDL_KEYDOWN:
				if( event.key.keysym.sym == SDLK_ESCAPE )
					battle->AbortBattle();
				else if( event.key.keysym.sym == pause )
					game->pause();
				else if( event.key.keysym.sym == accelUp )
					isAccelUpOn = true;
				else if( event.key.keysym.sym == accelDown )
					isAccelDownOn = true;
				else if( event.key.keysym.sym == accelLeft )
					isAccelLeftOn = true;
				else if( event.key.keysym.sym == accelRight )
					isAccelRightOn = true;
				break;

			case SDL_KEYUP:
				if( event.key.keysym.sym == accelUp )
					isAccelUpOn = false;
				else if( event.key.keysym.sym == accelDown )
					isAccelDownOn = false;
				else if( event.key.keysym.sym == accelLeft )
					isAccelLeftOn = false;
				else if( event.key.keysym.sym == accelRight )
					isAccelRightOn = false;
				break;

			case SDL_MOUSEBUTTONDOWN:
				if( event.button.button == SDL_BUTTON_LEFT )
					fighter->startFiring();
				break;

			case SDL_MOUSEBUTTONUP:
				if( event.button.button == SDL_BUTTON_LEFT )
					fighter->stopFiring();
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

	// move fighter
	if( ! game->isPaused() ) {
		vec3 direction = vec3();
		if( isAccelUpOn )
			direction[1] += 1;
		if( isAccelDownOn )
			direction[1] -= 1;
		if( isAccelLeftOn )
			direction[0] -= 1;
		if( isAccelRightOn )
			direction[0] += 1;
		accel( direction );
	}
}

