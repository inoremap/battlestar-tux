/* PlayerFighterController.cpp
 *
 * Copyright 2007-2008 Eliot Eshelman
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
#include "WeaponSystem.h"

PlayerFighterController::PlayerFighterController( Battle* b, Screen* s, Fighter* f ) : FighterController( f ) {
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

	rampAccelUp = 0;
	rampAccelDown = 0;
	rampAccelLeft = 0;
	rampAccelRight = 0;

	keyramp = 0.1;

	prevCursorPos = screen->getCursorPos();
	prevFighterPos = fighter->getPos();
	mouseSensitivity = 0.075;
}


PlayerFighterController::~PlayerFighterController() {
}


void PlayerFighterController::Update( int speed ) {
	// Check for keypresses and mouse events.
	// Remember that two or three keys/buttons may be down!!
	SDL_Event event;
	while( !game->isFinished() && !battle->isFinished() && !battle->isAborted() && SDL_PollEvent(&event) ) {
		switch( event.type ) {
			case SDL_KEYDOWN:
				if( event.key.keysym.sym == SDLK_ESCAPE )
					battle->AbortBattle();
				else if( event.key.keysym.sym == pause )
					game->pause();
				else if( event.key.keysym.sym == accelUp ) {
					isAccelUpOn = true;
					rampAccelUp += keyramp;
				}
				else if( event.key.keysym.sym == accelDown ) {
					isAccelDownOn = true;
					rampAccelDown += keyramp;
				}
				else if( event.key.keysym.sym == accelLeft ) {
					isAccelLeftOn = true;
					rampAccelLeft += keyramp;
				}
				else if( event.key.keysym.sym == accelRight ) {
					isAccelRightOn = true;
					rampAccelRight += keyramp;
				}
				break;

			case SDL_KEYUP:
				if( event.key.keysym.sym == accelUp ) {
					isAccelUpOn = false;
					rampAccelUp -= keyramp;
				}
				else if( event.key.keysym.sym == accelDown ) {
					isAccelDownOn = false;
					rampAccelDown -= keyramp;
				}
				else if( event.key.keysym.sym == accelLeft ) {
					isAccelLeftOn = false;
					rampAccelLeft -= keyramp;
				}
				else if( event.key.keysym.sym == accelRight ) {
					isAccelRightOn = false;
					rampAccelRight -= keyramp;
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				if( event.button.button == SDL_BUTTON_LEFT )
					fighter->FirePrimary( true );
				else if( event.button.button == SDL_BUTTON_RIGHT )
					fighter->FireSecondary( true );
				break;

			case SDL_MOUSEBUTTONUP:
				if( event.button.button == SDL_BUTTON_LEFT )
					fighter->FirePrimary( false );
				else if( event.button.button == SDL_BUTTON_RIGHT )
					fighter->FireSecondary( false );
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
			direction[1] += rampAccelUp;
		if( isAccelDownOn )
			direction[1] -= rampAccelDown;
		if( isAccelLeftOn )
			direction[0] -= rampAccelLeft;
		if( isAccelRightOn )
			direction[0] += rampAccelRight;
		accel( direction );
	}

	// Update the crosshair position for weapons fire. 
	ivec2 cursorDelta = screen->getCursorPos() - prevCursorPos;
	vec3 targetPos = fighter->getWeaponSystem()->getTarget();
	vec3 fighterPos = fighter->getPos();

	targetPos[0] += (float) cursorDelta[0] * mouseSensitivity + fighterPos[0] - prevFighterPos[0];
	// y-axis is reversed on screen.
	targetPos[1] -= (float) cursorDelta[1] * mouseSensitivity;
	targetPos[1] += fighterPos[1] - prevFighterPos[1];
	fighter->getWeaponSystem()->setTarget( targetPos );

	prevCursorPos = screen->getCursorPos();
	prevFighterPos = fighterPos;
}

