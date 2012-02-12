#!/usr/bin/env python
#
# Copyright (c) 2012 Eliot Eshelman
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
###############################################################################

import simplexnoise
import simplextextures

if __name__ == '__main__':
    iterations = 5;

    print(  "Generating " +
            str(iterations*iterations*iterations*iterations) +
            " iterations.")

    for h in range(iterations):
        for i in range(iterations):
            for j in range(iterations):
                for k in range(iterations):
                    print simplexnoise.octave_noise_4d(3, 0.5, 1, h, i, j, k)
                    print simplextextures.marble_noise_4d(3, 0.5, 1, h, i, j, k)
