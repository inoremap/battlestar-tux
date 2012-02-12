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

import logging

from Component import ComponentTypes

class System(object):
    """Systems determine Entity behavior and take action using the data
    provided by Components. A System is expected to act on a group
    of Components without great concern for any individual Component.
    """

    def __init__(self, component_type=None):
        if component_type is not None and component_type in ComponentTypes:
            self._component_type = component_type
            """Defines the type of component processed by the System."""

            logging.debug("System created for Component type: %s", component_type)
        else:
            logging.error("The specified Component type has not been defined.")
            raise AttributeError

    def get_type(self):
        """Defines the type of System.
        Corresponds to the type of Component processed by the System.
        Must be defined for all Systems.
        """
        return self._component_type

    def game_step(self, time_since_last_frame):
        """Process one game tick.
        Must be defined for all Systems.
        """
        pass

    #TODO: may wish to add a dict of callables to be processed at each game step
