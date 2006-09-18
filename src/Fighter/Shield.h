/* Shield.h
 *
 * Copyright 2006 Eliot Eshelman
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


#ifndef SHIELD_H_
#define SHIELD_H_

#include <SDL_opengl.h>

#include "Displayable.h"
#include "Game.h"
#include "ShieldImpactList.h"

class Fighter;

/* Shield protection surrounding a fighter. */
class Shield : public Displayable {
	public:
				Shield( Fighter* f, float full, Game* g );
				~Shield();

				void Draw();

				// Update shield systems.
				void Update();

				// Do 'damage' amount of damage to shield.
				// Damage occurs at point ( X, Y )
				// Returns the amount of damage the shield couldn't stop.
				float damage( float damage, float* point );

				float getShields();
				float getShieldsFull();

	private:
				Shield( const Shield &shield );
				const Shield & operator= ( const Shield &shield );

				// Remaining shield strength
				float shields;

				// Maximum shield strength
				float shieldsFull;

				// List of impacts on the shield
				ShieldImpactList* impactList;

				// Fighter that has shield mounted
				Fighter* fighter;

				GLuint texture;
};


#endif /*SHIELD_H_*/
