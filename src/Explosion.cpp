/* Explosion.cpp
 *
 * Copyright 2006 Eliot Eshelman
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


#include "Explosion.h"
#include "ExplosionList.h"

Explosion::Explosion( ExplosionType e, GLuint t, Game* g ) : Displayable( EFFECT, g ) {
	sizePulse = new Pulse( DOUBLE_ZERO_PULSE, 1, 1 );
	alphaPulse = new Pulse( DOUBLE_ZERO_PULSE, 1, 1 );

	explosionType = e;
	texture = t;
}


void Explosion::Update() {
	size[0] = size[1] = 4 * sizePulse->GetNextPulse();
	color[3] = alphaPulse->GetNextPulse();

	Displayable::Update();
}


void Explosion::Draw() {
	glBindTexture( GL_TEXTURE_2D, texture );

	Displayable::Draw();
}


bool Explosion::done() {
	if( sizePulse->done() && alphaPulse->done() )
		return true;
	else
		return false;
}
