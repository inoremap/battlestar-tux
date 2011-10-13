# Copyright (c) 2011 Eliot Eshelman
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

class SystemManager(object):
    """SystemManager oversees the operations of each System.
    
    Systems perform operations on the data contained by Components.
    """

    def __init__(self):
        self._all_systems = set()
        """Dict of all systems."""

    def game_step(self, time_since_last_frame):
        """Systems each process one game tick."""
        #TODO: parallelize for performance
        for system in self._all_systems:
            system.game_step(time_since_last_frame)

    def add_system(self, system):
        """Add a System to the set."""
        self._all_systems.add(system)

    def remove_system(self, system):
        """Remove a System from the set."""
        self._all_systems.remove(system)
