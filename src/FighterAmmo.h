/* FighterAmmo.h
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


#ifndef FIGHTERAMMO_H_
#define FIGHTERAMMO_H_

#include <SDL_opengl.h>

#include "Displayable.h"
#include "FighterAmmoList.h"
#include "Game.h"

class FighterAmmo : public Displayable {
	public:
				FighterAmmo( FighterAmmoType f, float d, float p, GLuint t, Game* g );

				void Draw();

				float getDamage();
				float getPenetration();

	private:
				FighterAmmo( const FighterAmmo &ammo );
				const FighterAmmo & operator= ( const FighterAmmo &ammo );

				// Constant Z position of the ammo.
				static const float zPos = -1.4;

				FighterAmmoType ammoType;

				// Damage dealt by the ammo.
				float damage;

				// Penetrating power of the ammo.
				float penetration;

				GLuint texture;
};


#endif /*FIGHTERAMMO_H_*/
