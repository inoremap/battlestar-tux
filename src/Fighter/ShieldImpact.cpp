/* ShieldImpactList.cpp
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


#include "ShieldImpact.h"

ShieldImpact::ShieldImpact( Shield* s, float angle, GLuint t, Game* g ) : Displayable( EFFECT, g ) {

	impactPulse = new Pulse( DOUBLE_ONE_PULSE, 1, 1 );

	rot = angle;
	texture = t;

	float* shieldColor = s->getColor();
	color[0] = shieldColor[0] + .05;
	color[1] = shieldColor[1] + .05;
	color[2] = shieldColor[2] + .05;
	color[3] = shieldColor[3];

	float* shieldPos = s->getPos();
	pos[0] = shieldPos[0];
	pos[1] = shieldPos[1];

	float* shieldSize = s->getSize();
	size[0] = shieldSize[0];
	size[1] = shieldSize[1];
}


ShieldImpact::~ShieldImpact() {
	texture = 0;
}


void ShieldImpact::Update() {
	color[3] = impactPulse->GetNextPulse();

	Displayable::Update();
}


void ShieldImpact::Draw() {
	glBindTexture( GL_TEXTURE_2D, texture );
	Displayable::Draw();
}


bool ShieldImpact::done() { return impactPulse->done(); }
