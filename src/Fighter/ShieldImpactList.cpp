/* ShieldImpactList.cpp
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


#include <math.h>

#include "Shield.h"
#include "ShieldImpact.h"
#include "ShieldImpactList.h"
#include "../TextureManager.h"

ShieldImpactList::ShieldImpactList( Shield* s, Game* g ) {
	texture = g->getTextureManager()->loadTexture( "data/gfx/shield_impact_0001-64.png" );
	shield = s;
	game = g;
}


ShieldImpactList::~ShieldImpactList() {
	texture = 0;
	shield = 0;
}


void ShieldImpactList::Draw() {
	ShieldImpact* cur = (ShieldImpact*) rootObj;
	ShieldImpact* next = 0;

	// Draw each impact, if there are any.
	while( cur ) {
		next = (ShieldImpact*) cur->getNext();

		cur->Draw();

		cur = next;
	}
}


void ShieldImpactList::Update() {
	ShieldImpact* cur = (ShieldImpact*) rootObj;
	ShieldImpact* next = 0;
	float* position = shield->getPos();

	// Update each impact, if there are any.
	while( cur ) {
		next = (ShieldImpact*) cur->getNext();

		// Remove finished impact.
		if( cur->done() )
			remObject( cur );
		else {
			cur->Update();

			// Set the position to match the shield.
			cur->setPos( position[0], position[1] );
		}

		cur = next;
	}
}


void ShieldImpactList::Impact( float* point ) {
	float angle = 0.0;
	float* shieldPosition = shield->getPos();

	// Normalized height from (0, 0)
	float height = point[1] - shieldPosition[1];
	height /= (shield->getSize()[0] / 2);

	// Calculate the proper angle.
	angle = acos( height ) * (180 / M_PI);

	// The value is 0-90, so an offset is needed.
	// No offset needed if in quadrant 2.
	if( point[0] < shieldPosition[0] && point[1] < shieldPosition[1] )
		angle += 90;
	else if( point[0] > shieldPosition[0] && point[1] < shieldPosition[1] )
		angle = (90 - angle) + 180;
	else if( point[0] > shieldPosition[0] && point[1] > shieldPosition[1] )
		angle = (90 - angle) + 270;

	if( angle < 270 && angle > 90 )
		cout		<< "Angle: " << angle << "\tShield: (" << shieldPosition[0] << ", " << shieldPosition[1]
				<< ")\tImpact: (" << point[0] << ", " << point[1] << ")\n";

	ShieldImpact* impact = new ShieldImpact( shield, angle, texture, game );
	addObject( impact );
}
