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

from Component import Component

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


#TODO: synchronize for multi-threaded support


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
