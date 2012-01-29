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

import Application
import EntitySystem
import utils.OgreBulletUtils as OgreBulletUtils
import utils.SimplexTextures as SimplexTextures


def create():
    """Create a procedural Terrain entity."""
    terrain_id = EntitySystem.create_entity()
    logging.debug('Terrain id: ' + str(terrain_id))

    # Generate random terrain points
    width = height = 10
    terrain_heights = [[0 for col in range(width)] for row in range(height)]
    for row in range(height):
        for column in range(width):
            terrain_heights[row][column] = SimplexTextures.marbleNoise2d(
                                                        1, 1, 1, row, column
                                                    )

    # Map the terrain onto an Ogre mesh
    terrain_object = ogre.ManualObject('Manual-' + str(terrain_id))
    terrain_object.estimateVertexCount(width * height)
    terrain_object.estimateIndexCount(width * height)
    for strip in range(height - 1):
        # begin a strip of triangles
        logging.debug('####   Beginning row: ' + str(strip) + '   ####')
        terrain_object.begin(
                                "BaseWhiteNoLighting",
                                ogre.RenderOperation.OT_TRIANGLE_LIST
                            )
        vertexID = 0
        for triangle in range(width - 1):
            logging.debug('    vertex: (' + str(triangle + 1) + ', ' +
                                    str(terrain_heights[triangle+1][strip]) + ', ' +
                                    str(strip) + ')')
            # triangle 0, vertex 0
            terrain_object.position(
                                    triangle + 1,                       # x
                                    terrain_heights[triangle+1][strip], # y
                                    strip                               # z
                                )
            terrain_object.normal(0, 0, 0)
            terrain_object.colour(1, 1, 1, 1)
            # triangle 0, vertex 1
            terrain_object.position(
                                    triangle,                           # x
                                    terrain_heights[triangle][strip],   # y
                                    strip                               # z
                                )
            terrain_object.normal(0, 0, 0)
            terrain_object.colour(1, 1, 1, 1)
            # triangle 0, vertex 2
            terrain_object.position(
                                    triangle,                           # x
                                    terrain_heights[triangle][strip+1], # y
                                    strip + 1                           # z
                                )
            terrain_object.normal(0, 0, 0)
            terrain_object.colour(1, 1, 1, 1)
            terrain_object.triangle(vertexID, vertexID+1, vertexID+2)
            vertexID += 3

            # triangle 1, vertex 0
            terrain_object.position(
                                    triangle + 1,                       # x
                                    terrain_heights[triangle+1][strip], # y
                                    strip                               # z
                                )
            terrain_object.normal(0, 0, 0)
            terrain_object.colour(1, 1, 1, 1)
            # triangle 1, vertex 1
            terrain_object.position(
                                    triangle,                           # x
                                    terrain_heights[triangle][strip+1], # y
                                    strip + 1                           # z
                                )
            terrain_object.normal(0, 0, 0)
            terrain_object.colour(1, 1, 1, 1)
            # triangle 1, vertex 2
            terrain_object.position(
                                    triangle + 1,                        # x
                                    terrain_heights[triangle+1][strip+1],# y
                                    strip + 1                            # z
                                )
            terrain_object.normal(0, 0, 0)
            terrain_object.colour(1, 1, 1, 1)
            terrain_object.triangle(vertexID, vertexID+1, vertexID+2)
            vertexID += 3
        terrain_object.end()
        # end of the strip of triangles
    ogre_node = Application.ogre_root_node.createChildSceneNode(
                          'ogreNode-' + str(terrain_id))
    ogre_node.attachObject(terrain_object)
    terrain_object.setCastShadows(False)
    # collision_object = OgreBulletUtils.CollisionObject(Application.bullet_world)
    # collision_object.setShape(OgreBulletUtils.MeshInfo.createCylinderShape(
    #                                        ogre_entity,
    #                                        OgreBulletUtils.BulletShapes.CYLINDERZ))
    # collision_object.setTransform(bullet.btVector3(terrain_position[0],
    #                                                terrain_position[1],
    #                                                terrain_position[2]))
    # collision_object.setMass(0)
    # Application.collision_objects.append(collision_object)
