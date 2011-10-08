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

import abc
import logging

from Component import ComponentTypes

class System(object):
    """Systems determine Entity behavior and take action using the data
    provided by Components. A System is expected to act on a group
    of Components without great concern for any individual Component.
    """
    __metaclass__ = abc.ABCMeta

    _component_types = None
    """Defines the types of components processed by the System."""

    def __init__(self, component_types=None):
        if component_types is not None and component_types.issubset(ComponentTypes):
            self._component_types = component_types
        else:
            logging.error("The specified Component types have not been defined.")
            raise AttributeError

    @abc.abstractmethod
    def get_type(self):
        """Defines the type of System.
        Corresponds to the type of Component processed by the System.
        Must be defined for all Systems.
        """

    @abc.abstractmethod
    def game_step(self, lastFrameTime):
        """Process one game tick.
        Must be defined for all Systems.
        """

    #TODO: may wish to add a dict of callables to be processed at each game step
