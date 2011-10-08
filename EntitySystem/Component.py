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

import utils

ComponentTypes = utils.enum(["HexCell",
                            "HexShip",
                            "Graphics",
                            "Physics"
                            ])
"""List of valid component types."""

class Component(dict):
    """Components are added to Entities to define their data.
    
    If an Entity is the unique ID of a database object, then
    the Component defines the layout of the database table row.
    """

    _component_types = None
    """Defines the type of component data."""

    def __init__(self, component_types=None):
        if component_types is not None and component_types in ComponentTypes:
            self._component_types = component_types
        else:
            logging.error("The specified Component type has not been defined.")
            raise AttributeError

    def get_type(self):
        """Defines the type of Component."""
        return self._component_types
