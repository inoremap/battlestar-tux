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
import uuid

from utils import enum

"""The EntitySystem ties together Entities, Components and Systems.
All in-game objects are represented by EntitySystem objects.

An Entity is nothing more than a unique ID.
Components are added to Entities to define their data.
Systems perform operations on the data contained by Components.
"""

_all_entities = set()
"""Set of all entities"""

_all_entities_readable_names = dict()
"""Matches entity IDs with human-readable names"""

_component_stores = dict()
"""Dictionary of all components"""

_all_systems = set()
"""Dict of all systems."""


ComponentTypes = enum([
     # Macro-level properties
     "AI",
     "Graphics",
     "Music",
     "Physics",
     "SoundEffects",
     # Game object (primarily HexCell) properties
     "Damageable",
     "EnergyConsumer",
     "EnergyGenerator",
     "EnergyStorage",
     "Propulsion",
     "Weapon"
])
"""List of valid component types."""
#TODO: According to Adam, a better choice would be defining DB tables here.
# For the time being, the best bet is to read from the DB at startup and
# not write back until exiting. Each component holds one DB table. Each system
# operates on one or more DB tables.
#TODO: synchronize for multi-threaded support


class Component(dict):
    """Components are added to Entities to define their data.

    If an Entity is the unique ID of a database object, then
    the Component defines the layout of the database table row.
    """

    def __init__(self, component_type):
        if component_type is not None and component_type in ComponentTypes:
            self._component_type = component_type
            """Defines the type of component data."""

            logging.debug("Created Component type: %s", component_type)
        else:
            logging.error("The specified Component type has not been defined.")
            raise AttributeError

    def get_type(self):
        """Defines the type of Component."""
        return self._component_type


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


## Entity Functions ##
def create_entity(name=None):
    """Create a new Entity using a random UUID.
    If a human-readable 'name' is provided, it is assigned to the Entity.
    """
    entity_id = uuid.uuid4()
    _all_entities.add(entity_id)
    if name is not None:
        _all_entities_readable_names[entity_id] = name
    return entity_id

def delete_entity(entity):
    """Remove an Entity and all associated component data."""
    # Delete all component data
    for store in _component_stores:
        try:
            del _component_stores[store][entity]
        except KeyError:
            # An Entity will not have all components
            pass
    # Delete the Entity
    remove_entity_name(entity)
    try:
        del _all_entities[entity]
    except KeyError:
        logging.exception("Entity %s does not exist.", entity)
        return False
    else:
        return True

def delete_all_entities():
    """Remove all Entities and their associated component data."""
    _component_stores.clear()
    _all_entities_readable_names.clear()
    _all_entities.clear()

def set_entity_name(entity, name=None):
    """Assign a human-readable name to an Entity."""
    if name is not None:
        _all_entities_readable_names[entity] = name

def get_entity_name(entity):
    """Get the human-readable name for an Entity (if available)."""
    try:
        return _all_entities_readable_names[entity]
    except KeyError:
        # An Entity is not required to have a human-readable name.
        return None

def remove_entity_name(entity):
    """Remove the human-readable name for an Entity (if it exists)."""
    try:
        del _all_entities_readable_names[entity]
    except KeyError:
        # An Entity is not required to have a human-readable name.
        return


## Component Functions ##
def add_component(entity, component_type, data):
    """Add component data for the specified Entity."""
    try:
        store = _component_stores[component_type]
    except KeyError:
        store = _component_stores[component_type] = Component(component_type)
    store[entity] = data

def get_component(entity, component_type):
    """Returns component data for the specified Entity."""
    try:
        store = _component_stores[component_type]
    except KeyError:
        logging.exception("The component requested has not been initialized.")
        return None
    try:
        return store[entity]
    except KeyError:
        logging.exception("Entity %s does not have the requested component.", entity)
        return None

def remove_component(entity, component_type):
    """Remove component data for the specified Entity."""
    try:
        store = _component_stores[component_type]
    except KeyError:
        logging.exception("The component requested has not been initialized.")
        return False
    try:
        del store[entity]
    except KeyError:
        logging.exception("Entity %s does not have the requested component.", entity)
        return False
    else:
        return True

def has_component(entity, component_type):
    """Check if the specified Entity contains component data."""
    try:
        return entity in _component_stores[component_type]
    except KeyError:
        logging.exception("The component requested has not been initialized.")
        return False

def get_entity_components(entity):
    """Return all component data stored for the specified Entity.
    WARNING: low performance implementation!
    """
    components = set()
    for store in _component_stores:
        try:
            component = _component_stores[store][entity]
            components.add(component)
        except KeyError:
            pass
    return components

def get_component_data(component_type):
    """Return the component data of all entities for the specified component."""
    try:
        store = _component_stores[component_type]
    except KeyError:
        logging.exception("The component requested has not been initialized.")
        return None
    else:
        return store

def get_entity_ids(component_type):
    """Return all Entity IDs for the specified component."""
    try:
        store = _component_stores[component_type]
    except KeyError:
        logging.exception("The component requested has not been initialized.")
        return None
    else:
        return store.keys()


## System Functions ##
def game_step(time_since_last_frame):
    """Systems each process one game tick."""
    #TODO: parallelize for performance
    for system in _all_systems:
        system.game_step(time_since_last_frame)

def add_system(system):
    """Add a System to the set."""
    _all_systems.add(system)

def delete_system(system):
    """Delete a System."""
    try:
        del _all_systems[system]
    except KeyError:
        logging.exception("System %s does not exist.", system)
        return False
    else:
        return True

def delete_all_systems():
    """Delete all Systems."""
    _all_systems.clear()
