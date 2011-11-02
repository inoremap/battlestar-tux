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

import Component

class EntityManager(object):
    """EntityManager ties together the Entities, Components and Systems.
    
    An Entity is nothing more than a unique ID.
    """

    def __init__(self):
        self._all_entities = set()
        """Set of all entities"""

        self._all_entities_readable_names = dict()
        """Matches entity IDs with human-readable names"""

        self._component_stores = dict()
        """Dictionary of all components"""

    def create_entity(self, name=None):
        """Create a new Entity using a random UUID.
        If a human-readable 'name' is provided, it is assigned to the Entity.
        """
        uuid = uuid.uuid4()
        self._all_entities.add(uuid)
        if name is not None:
            self._all_entities_readable_names[uuid] = name
        return uuid

    def delete_entity(self, entity):
        """Remove an Entity and all associated component data."""
        #TODO: synchronize

        # Delete all component data
        for store in self._component_stores:
            try:
                del store[entity]
            except KeyError:
                pass
        # Delete the Entity
        try:
            del self._all_entities_readable_names[entity]
            del self._all_entities[entity]
        except KeyError:
            pass

    def set_entity_name(self, entity, name=None):
        """Assign a human-readable name to an Entity."""
        if name is not None:
            self._all_entities_readable_names[uuid] = name

    def get_entity_name(self, entity):
        """Get the human-readable name for an Entity (if available)."""
        try:
            return self._all_entities_readable_names[entity]
        except KeyError:
            # An Entity is not required to have a human-readable name.
            return None

    def add_component(self, entity, component_type, data):
        """Add component data for the specified Entity."""
        #TODO: synchronize

        try:
            store = self._component_stores[component_type]
        except KeyError:
            self._component_stores[component_type] = Component(component_type)
            store = self._component_stores[component_type]
        store[entity] = data

    def get_component(self, entity, component_type):
        """Returns component data for the specified Entity."""
        #TODO: synchronize

        try:
            store = self._component_stores[component_type]
        except KeyError:
            logging.exception("The component requested has not been initialized.")
            return None
        try:
            return store[entity]
        except KeyError:
            logging.exception("Entity %s does not have the requested component.", entity)
            return None

    def remove_component(self, entity, component_type):
        """Remove component data for the specified Entity."""
        #TODO: synchronize

        try:
            store = self._component_stores[component_type]
        except KeyError:
            logging.exception("The component requested has not been initialized.")
            return False
        try:
            del store[entity]
            return True
        except KeyError:
            logging.exception("Entity %s does not have the requested component.", entity)
            return False

    def has_component(self, entity, component_type):
        """Check if the specified Entity contains component data."""
        #TODO: synchronize

        try:
            store = self._component_stores[component_type]
        except KeyError:
            logging.exception("The component requested has not been initialized.")
            return False
        return entity in store

    def get_entity_components(self, entity):
        """Return all component data stored for the specified Entity.
        WARNING: low performance implementation!
        """
        #TODO: synchronize

        components = set()
        for store in self._component_stores:
            try:
                component = store[entity]
                components.add(component)
            except KeyError:
                pass
        return components

    def get_component_data(self, component_type):
        """Return the component data of all entities for the specified component."""
        #TODO: synchronize

        try:
            store = self._component_stores[component_type]
        except KeyError:
            logging.exception("The component requested has not been initialized.")
            return None
        return store.values()

    def get_entity_ids(self, component_type):
        """Return all Entity IDs for the specified component."""
        #TODO: synchronize

        try:
            store = self._component_stores[component_type]
        except KeyError:
            logging.exception("The component requested has not been initialized.")
            return None
        return store.keys()
