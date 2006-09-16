/* ShieldImpact.h
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


#ifndef SHIELDIMPACT_H_
#define SHIELDIMPACT_H_

#include <SDL_opengl.h>

#include "Shield.h"
#include "../Displayable.h"
#include "../Game.h"
#include "../Pulse.h"

class ShieldImpact : public Displayable {
	public:
				ShieldImpact( Shield* s, float angle, GLuint t, Game* g );
				~ShieldImpact();

				void Update();

				void Draw();

				// Returns true when the impact has faded.
				bool done();

	private:
				Pulse* impactPulse;

				GLuint texture;
};

#endif /*SHIELDIMPACT_H_*/
