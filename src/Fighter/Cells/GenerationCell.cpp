/* GenerationCell.cpp
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


#include "GenerationCell.h"
#include "TextureManager.h"

GenerationCell::GenerationCell( Fighter* f, Game* g, const ivec2 &pos  ) : HexCell( f, g, GENERATION_CELL, pos )  {
	generationRate = 0;
	drawRate = 0;

	texture = game->getTextureManager()->loadTexture( "data/gfx/hex_cell_0001-16.png" );
}


GenerationCell::~GenerationCell() {
	game->getTextureManager()->freeTextures( 1, &texture );
}


void GenerationCell::Update( int speed ) {
	drawRate = 0;

	HexCell::Update( speed );
}


void GenerationCell::Draw() {
	glBindTexture( GL_TEXTURE_2D, texture );

	glColor4f( 0.1, 0.9, 0.1, 1.0 );
	drawHex( HEX_CELL_SIZE[0], HEX_CELL_SIZE[1], HEX_CELL_SIZE[2] );

	glColor4f( 0.3, 0.7, 0.3, 1.0 );
	drawHex( 0.15, HEX_CELL_SIZE[0], HEX_CELL_SIZE[2] );
}


void GenerationCell::setGenerationRate( float r ) { generationRate = r; }
float GenerationCell::getGenerationRate() { return generationRate; }
float GenerationCell::getDrawRate() { return drawRate; }


float GenerationCell::getPower( float power ) {
	if( (drawRate + power) > generationRate ) {
		float available = generationRate - drawRate;
		drawRate = generationRate;
		return available;
	}
	else {
		drawRate += power;
		return power;
	}
}


float GenerationCell::returnPower( float power ) {
	if( power > drawRate ) {
		float available = drawRate;
		drawRate = 0;
		return power - available;
	}
	else {
		drawRate -= power;
		return 0;
	}
}

