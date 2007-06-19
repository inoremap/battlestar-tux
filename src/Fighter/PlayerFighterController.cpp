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

PlayerFighterController::PlayerFighterController( Fighter* f , Game* g ) : FighterController( f, g ) {
}


PlayerFighterController::~PlayerFighterController() {
}


void PlayerFighterController::Update( int speed ) {
	vec3 direction = vec3();

	// get the keypresses and mouse stuff
	// remember that two or three keys mat be down!!
	char keydown;

	// we actually ned to use bools here,
	// because we are using key events,
	// not key states.
	switch( keydown ) {
		case accelUp:
			direction[1] += 1;
			break;

		case accelDown:
			direction[1] -= 1;
			break;

		case accelLeft:
			direction[0] -= 1;
			break;

		case accelRight:
			direction[0] += 1;
			break;
	}

	accel( direction );
}

