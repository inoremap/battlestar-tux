/* Pulse.cpp
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


#include "Pulse.h"

Pulse::Pulse( PULSE_CHANNELS chan, PULSE_FUNCTION func, int reps, int s, DisplayableType t, Game* g ) : Displayable( t, g ) {
	channels = chan;

	switch( func ) {
		case DOUBLE_ONE_PULSE:
			function = DOUBLE_ONE_PULSE_FUNC;
			functionSize = 100;
			break;
		case DOUBLE_ZERO_PULSE:
		default:
			function = DOUBLE_ZERO_PULSE_FUNC;
			functionSize = 100;
			break;
	}

	cycles = reps;
	cycleNum = 0;
	position = 0;
	scale = s;
}


Pulse::~Pulse() {}


void Pulse::Update() {
	float newValue = 0.0;

	Displayable::Update();

	// Reached the end of a cycle.
	if( position > 0 && (position % CYCLE_SIZE) == 0 ) {
		cycleNum++;

		// Is this the end of the function?
		if( position == functionSize ) {
			// If the pulse is done, return last value in function.
			if( done() )
				newValue = function[position - 1];
			// Start again at the beginning of the function.
			else {
				newValue = function[0];
				position = 1;
			}
		}
		// Continue in function.
		else {
			// If the pulse is done, return last value in cycle.
			if( done() )
				newValue = function[position - 1];
			else {
				newValue = function[position];
				position++;
			}
		}
	}
	// Continue existing cycle.
	else {
		newValue = function[position];
		position++;
	}

	if( channels & RED )
		color[0] = newValue;
	if( channels & GREEN )
		color[1] = newValue;
	if( channels & BLUE )
		color[2] = newValue;
	if( channels & ALPHA )
		color[3] = newValue;
}


bool Pulse::done() {
	// Infinite cycles?
	if( cycles == 0 )
		return false;
	// Completed all cycles?
	else if( cycleNum >= cycles )
		return true;
	else
		return false;
}
