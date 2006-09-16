/* Pulse.h
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


#ifndef PULSE_H_
#define PULSE_H_

#include "Game.h"


static const int CYCLE_SIZE = 50;

/* List of possible functions. */
enum PULSE_FUNCTION {
	DOUBLE_ONE_PULSE,			// 1 - 0 - 1 in 2 cycles.
	DOUBLE_ZERO_PULSE			// 0 - 1 - 0 in 2 cycles.
};


/* Pulse functions - values (0, 1).
 * Each function has 50 values per cycle, but some functions
 * span more than one cycle (for example, transitioning from 1
 * to 0 and then back to 1 in two cycles). */
class Pulse {
	public:
				Pulse( PULSE_FUNCTION func, int reps, int s );
				~Pulse();

				// Update the pulse value.
				void Update();

				// Retrieve the current pulse value.
				float GetPulse();

				// Update and return the pulse value.
				float GetNextPulse();

				// Returns true when all pulse cycles have finished.
				// Never returns true if cycles is 0 (infinite).
				bool done();

	private:
				// What pulse function to use.
				const float* function;

				// Current pulse value.
				float pulseValue;

				// Number of values in the function.
				int functionSize;

				// How many cycles to repeat the pulse.
				// 0 will repeat infinitely.
				int cycles;

				// Current cycle
				int cycleNum;

				// Position in the cycle.
				int position;

				// Relative speedup of the function.
				int scale;
};


/* Pulse function from 1 to 0 to 1.  y=cos(x)^4  */
static const float DOUBLE_ONE_PULSE_FUNC[100] = {
	1.00000000, 0.99802770, 0.99213025, 0.98236569, 0.96882992,
	0.95165538, 0.93100932, 0.90709152, 0.88013169, 0.85038637,
	0.81813562, 0.78367929, 0.74733313, 0.70942474, 0.67028933,
	0.63026550, 0.58969099, 0.54889849, 0.50821165, 0.46794120,
	0.42838137, 0.38980661, 0.35246860, 0.31649372, 0.28238092,
	0.25000000, 0.21959040, 0.19126049, 0.16508728, 0.14111672,
	0.11936438, 0.09981665, 0.08243236, 0.06714481, 0.05386419,
	0.04248025, 0.03286534, 0.02487763, 0.01836450, 0.01316604,
	0.00911863, 0.00605845, 0.00382501, 0.00226447, 0.00123284,
	0.00059887, 0.00024675, 0.00007844, 0.00001554, 0.00000097,
	0.00000000, 0.00000097, 0.00001554, 0.00007844, 0.00024675,
	0.00059887, 0.00123284, 0.00226447, 0.00382501, 0.00605845,
	0.00911863, 0.01316604, 0.01836450, 0.02487763, 0.03286534,
	0.04248025, 0.05386419, 0.06714481, 0.08243236, 0.09981665,
	0.11936438, 0.14111672, 0.16508728, 0.19126049, 0.21959040,
	0.25000000, 0.28238092, 0.31659372, 0.35246860, 0.38980661,
	0.42838137, 0.46794120, 0.50821165, 0.54889849, 0.58969099,
	0.63026500, 0.67028933, 0.70942474, 0.74733313, 0.78367929,
	0.81813562, 0.85038637, 0.88013169, 0.90709152, 0.93100932,
	0.95165538, 0.96882992, 0.98236569, 0.99213025, 0.99802770
};

/* Pulse function from 0 to 1 to 0.  y=cos(x)^4  */
static const float DOUBLE_ZERO_PULSE_FUNC[100] = {
	0.00000000, 0.00000097, 0.00001554, 0.00007844, 0.00024675,
	0.00059887, 0.00123284, 0.00226447, 0.00382501, 0.00605845,
	0.00911863, 0.01316604, 0.01836450, 0.02487763, 0.03286534,
	0.04248025, 0.05386419, 0.06714481, 0.08243236, 0.09981665,
	0.11936438, 0.14111672, 0.16508728, 0.19126049, 0.21959040,
	0.25000000, 0.28238092, 0.31659372, 0.35246860, 0.38980661,
	0.42838137, 0.46794120, 0.50821165, 0.54889849, 0.58969099,
	0.63026500, 0.67028933, 0.70942474, 0.74733313, 0.78367929,
	0.81813562, 0.85038637, 0.88013169, 0.90709152, 0.93100932,
	0.95165538, 0.96882992, 0.98236569, 0.99213025, 0.99802770,
	1.00000000, 0.99802770, 0.99213025, 0.98236569, 0.96882992,
	0.95165538, 0.93100932, 0.90709152, 0.88013169, 0.85038637,
	0.81813562, 0.78367929, 0.74733313, 0.70942474, 0.67028933,
	0.63026550, 0.58969099, 0.54889849, 0.50821165, 0.46794120,
	0.42838137, 0.38980661, 0.35246860, 0.31649372, 0.28238092,
	0.25000000, 0.21959040, 0.19126049, 0.16508728, 0.14111672,
	0.11936438, 0.09981665, 0.08243236, 0.06714481, 0.05386419,
	0.04248025, 0.03286534, 0.02487763, 0.01836450, 0.01316604,
	0.00911863, 0.00605845, 0.00382501, 0.00226447, 0.00123284,
	0.00059887, 0.00024675, 0.00007844, 0.00001554, 0.00000097
};

#endif /*PULSE_H_*/
