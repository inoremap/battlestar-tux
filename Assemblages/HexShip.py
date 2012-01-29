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
import ogre.physics.bullet as bullet
import ogre.renderer.OGRE as ogre

import Application
import EntitySystem
import utils.OgreBulletUtils as OgreBulletUtils


def create(ship_position=(0, 0, 0)):
    """Create a HexShip entity."""
    ship_id = EntitySystem.create_entity()
    logging.debug("HexShip id: " + str(ship_id) + "   pos: (" +
                   str(ship_position[0]) + ", " +
                   str(ship_position[1]) + ", " +
                   str(ship_position[2]) + ")"
                  )

    ogre_entity = Application.ogre_scene_manager.createEntity(
                          'ogreEntity-' + str(ship_id), 'HexCell.mesh')
    ogre_node = Application.ogre_root_node.createChildSceneNode(
                          'ogreNode-' + str(ship_id))
    ogre_node.attachObject(ogre_entity)
    ogre_entity.setCastShadows(False)
    ogre_node.setScale(ogre.Vector3(1.0, 1.0, 1.0))
    collision_object = OgreBulletUtils.CollisionObject(Application.bullet_world)
    collision_object.setShape(OgreBulletUtils.MeshInfo.createCylinderShape(
                                           ogre_entity,
                                           OgreBulletUtils.BulletShapes.CYLINDERZ))
    collision_object.setTransform(bullet.btVector3(ship_position[0],
                                                   ship_position[1],
                                                   ship_position[2]))
    collision_object.setMass(1.0)
    collision_object.setInertia(bullet.btVector3(0.0, 0.0, 0.0))
    collision_object.setMotion(ogre_entity.getParentSceneNode())
    Application.collision_objects.append(collision_object)
