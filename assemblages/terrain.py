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

import logging
import ogre.physics.bullet as bullet
import ogre.renderer.OGRE as ogre

import application
import entitysystem
import utils.OgreBulletUtils as OgreBulletUtils
import procedural.simplexnoise as simplexnoise

def create():
    """Create a procedural Terrain entity."""
    terrain_id = entitysystem.create_entity()
    logging.debug('Terrain id: ' + str(terrain_id))

    # Map the terrain onto an Ogre mesh
    width = height = 100
    offsetX = width / 2.0
    offsetY = height / 2.0
    terrain_object = ogre.ManualObject('Manual-' + str(terrain_id))
    terrain_object.estimateVertexCount(width * height)
    terrain_object.estimateIndexCount(width * height)

    # Generate heights and input the indices into OGRE.
    terrain_object.begin(
                        "Terrain_Azul",
                        ogre.RenderOperation.OT_TRIANGLE_LIST
                    )
    for row in range(height):
        for column in range(width):
            terrain_height = simplexnoise.scaled_octave_noise_2d(
                                3, 0.3, 0.05,    # Noise settings
                                -20, 0,          # Height range
                                column - offsetX,
                                row - offsetY
                            )
            terrain_object.position(
                                    column - offsetX,   # x
                                    terrain_height,     # y
                                    row - offsetY       # z
                                )
            #terrain_object.normal(0, 0, 0)
            terrain_object.colour(
                                    abs(terrain_height/20),
                                    abs(terrain_height/20),
                                    abs(terrain_height/20),
                                    1
                                )

    # Build a mesh of vertices.
    vertexID = 0
    for strip in range(height - 1):
        for quad in range(width - 1):
            terrain_object.quad(vertexID,             # top-left
                                vertexID + width,     # bottom-left
                                vertexID + width + 1, # bottom-right
                                vertexID + 1          # top-right
                                )
            vertexID += 1
        vertexID += 1
    terrain_object.end()

    # Attach mesh to OGRE scene.
    terrain_object.convertToMesh('Mesh-' + str(terrain_id))
    ogre_entity = application.ogre_scene_manager.createEntity(
                            'ogreEntity-' + str(terrain_id),
                            'Mesh-' + str(terrain_id)
                        )
    ogre_node = application.ogre_root_node.createChildSceneNode(
                            'ogreNode-' + str(terrain_id))
    ogre_node.attachObject(ogre_entity)
    ogre_entity.setCastShadows(False)
    entitysystem.add_component( terrain_id,
                                entitysystem.ComponentTypes.Graphics,
                                ogre_node)

    # Setup terrain collisions.
    collision_object = OgreBulletUtils.CollisionObject(application.bullet_world)
    triangle_mesh, collision_shape = OgreBulletUtils.MeshInfo.createTriMeshShape(ogre_entity)
    collision_object.setShape(collision_shape)
    collision_object.setMotion(None)
    entitysystem.add_component( terrain_id,
                                entitysystem.ComponentTypes.Physics,
                                (collision_object, triangle_mesh))
