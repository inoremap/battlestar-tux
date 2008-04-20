/* GenerationCell.h
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


#ifndef GENERATIONCELL_H_
#define GENERATIONCELL_H_

#include "HexCell.h"


// Create energy for the fighter to use.
class GenerationCell : public HexCell {
	public:
				GenerationCell( float );
				~GenerationCell();

				void Update( int );

				void Draw();

				void setGenerationRate( float );
				float getGenerationRate(); 
				float getDrawRate();

				// Transfer power to another component.
				// The amount of power being transferred is returned.
				float getPower( float );

				// Return power to the cell.
				// If a component ends up not using the
				// power, it needs to be put back.
				// Any power that doesn't fit is returned.
				float returnPower( float );

	private:
				GenerationCell( const GenerationCell & );
				const GenerationCell & operator= ( const GenerationCell & );

				// How much power this cell generates per unit time.
				float generationRate;

				// The amount of power being drawn during each unit of time.
				// This value is built up over the course of updating the fighter.
				// The only thing it can really be trusted for is seeing if the
				// generator has power left for use.
				float drawRate;

				GLuint texture;
};


#endif /*GENERATIONCELL_H_*/
