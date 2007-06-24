/* PlayerFighterController.h
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


#ifndef PLAYERFIGHTERCONTROLLER_H_
#define PLAYERFIGHTERCONTROLLER_H_

#include "Battle.h"
#include "FighterController.h"
#include "Game.h"
#include "Screen.h"
#include "Vector.h"


// Real people controller the fighter from here.
class PlayerFighterController : public FighterController {
	public:
				PlayerFighterController( Battle*, Screen*, Fighter*, Game* );
				virtual ~PlayerFighterController();

				void Update( int );

	private:
				PlayerFighterController( const PlayerFighterController & );
				const PlayerFighterController & operator= ( const PlayerFighterController & );

				Battle* battle;
				Screen* screen;

				// Key bindings for controlling fighter.
				char pause;
				char accelUp;
				char accelDown;
				char accelLeft;
				char accelRight;

				// State variables - are the keys pressed?
				bool isAccelUpOn;
				bool isAccelDownOn;
				bool isAccelLeftOn;
				bool isAccelRightOn;

				// Helps to smooth the controls.
				// When a key is pressed, it doesn't immediately go to 100%.
				float keyramp;

				float rampAccelUp;
				float rampAccelDown;
				float rampAccelLeft;
				float rampAccelRight;
};


#endif /*PLAYERFIGHTERCONTROLLER_H_*/
