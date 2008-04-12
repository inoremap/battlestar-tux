/* FighterController.h
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


#ifndef FIGHTERCONTROLLER_H_
#define FIGHTERCONTROLLER_H_

#include "Fighter.h"
#include "Game.h"
#include "Vector.h"


// Each fighter is controlled from here.
// Real people or AI controllers can use this interface.
class FighterController {
	public:
				FighterController( Fighter* );
				virtual ~FighterController();

	protected:
				// Accerate the fighter by a percentage
				// of the engine's total power.
				void accel( vec3 & );

				// Decelerate the fighter by a percentage
				// of the engine's total braking power.
				void decelerate( float );

				// Activate/Deactivate primary offensive/defensive weapons.
				void firePrimary( bool );

				// Activate/Deactivate secondary offensive/defensive weapons.
				void fireSecondary( bool );

				// Activate/Deactivate tertiary offensive/defensive weapons.
				void fireTertiary( bool );

				Fighter* fighter;
				Game* game;

	private:
				FighterController( const FighterController & );
				const FighterController & operator= ( const FighterController & );
};


#endif /*FIGHTERCONTROLLER_H_*/
