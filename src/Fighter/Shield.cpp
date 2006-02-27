/* Shield.cpp
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


#include "Shield.h"
#include "Fighter.h"
#include "../TextureManager.h"

Shield::Shield( Fighter* f, float full, Game* g ) : Displayable( SHIELD, g ) {
	fighter = f;
	float width = fighter->getSize()[0];
	float height = fighter->getSize()[1];

	texture = game->getTextureManager()->loadTexture( "data/gfx/shields_0001-64.png" );

	if( width >= height )
		size[0] = size[1] = width + 2.5;
	else
		size[0] = size[1] = height + 2.5;

	color[0] = 0.223;
	color[1] = 0.400;
	color[2] = 0.717;
	color[3] = 0.4;

	shields = shieldsFull = full;
}


Shield::~Shield() {}


void Shield::Draw() {
	float mx = size[0] / 2;
	float my = size[1] / 2;

	glBindTexture( GL_TEXTURE_2D, texture );
	glBegin( GL_QUADS );
		glColor4f( color[0], color[1], color[2], color[3] );
		glTexCoord2f( 0, 1 );
		glVertex3f( pos[0] - mx, pos[1] - my, pos[2] );
		glTexCoord2f( 1, 1 );
		glVertex3f( pos[0] + mx, pos[1] - my, pos[2] );
		glTexCoord2f( 1, 0 );
		glVertex3f( pos[0] + mx, pos[1] + my, pos[2] );
		glTexCoord2f( 0, 0 );
		glVertex3f( pos[0] - mx, pos[1] + my, pos[2] );
	glEnd();
}


void Shield::Update() {
	float* fighterPos = fighter->getPos();
	pos[0] = fighterPos[0];
	pos[1] = fighterPos[1];
	pos[2] = fighterPos[2];
}


float Shield::damage( float damage ) {
	float remainder = 0.0;

	remainder = damage - shields;
	shields -= damage;

	if( shields < 0 )
		shields = 0;

	if( remainder < 0 )
		remainder = 0;

	return remainder;
}


float Shield::getShields() { return shields; }
float Shield::getShieldsFull() { return shieldsFull; }
