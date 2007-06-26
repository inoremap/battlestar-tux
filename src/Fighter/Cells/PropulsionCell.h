/* PropulsionCell.h
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


#ifndef PROPULSIONCELL_H_
#define PROPULSIONCELL_H_

#include "HexCell.h"
#include "Vector.h"


// Move the fighter.
class PropulsionCell : public HexCell {
	public:
				PropulsionCell( Fighter*, const ivec2 & );
				~PropulsionCell();

				void Update( int );

				void Draw();

				// Apply acceleration forces to the fighter.
				// Return the amount of acceleration that wasn't performed.
				vec3 accelerate( const vec3 & );

				void setAccelerationRate( float );
				float getAccelerationRate(); 
				void setPowerRate( float );

	private:
				// How much (maximum) force this cell can exert.
				// Remember that acceleration can occur 50 times per second.
				float accelerationRate;

				// The amount of power the cell uses for each unit of acceleration force.
				float powerRate;

				PropulsionCell( const PropulsionCell & );
				const PropulsionCell & operator= ( const PropulsionCell & );
};


#endif /*PROPULSIONCELL_H_*/
