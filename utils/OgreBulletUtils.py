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

import ogre.renderer.OGRE as ogre
import ogre.physics.bullet as bullet

# Following code adapted from OgreBullet_BasicDemo.py included with Python-Ogre.

class MeshInfo:
    """Provide bounding boxes, as well as mesh conversion from OGRE to Bullet."""

    def __init__(self):
        pass

    @staticmethod
    def GetIndicies(indexData):
        outbuff = []
        numTris = indexData.indexCount
        if numTris == 0 : return outbuff
        else : numTris /= 3

        ibuf = indexData.indexBuffer

        if ibuf.getType() == ogre.HardwareIndexBuffer.IT_32BIT:
            Use32Bit = True
        else:
            Use32Bit = False

        ogre_buffer = ibuf.lock(ogre.HardwareBuffer.HBL_READ_ONLY)
        address = ogre.castAsInt(ogre_buffer)

        for i in range(numTris):
            if Use32Bit:
                l = ogre.getUint32 (ogre.castAsVoidPtr (address), 3)
                address += ibuf.getIndexSize() * 3
            else:
                l = ogre.getUint16 (ogre.castAsVoidPtr (address), 3)
                address += ibuf.getIndexSize() * 3
            outbuff.append(tuple(l))
        ibuf.unlock()
        return outbuff

    @staticmethod
    def GetVerticies(vertex_data, transform):
        outbuff = []

        # get the start of the element
        posElem = vertex_data.vertexDeclaration.findElementBySemantic(ogre.VertexElementSemantic.VES_POSITION)
        vbuf = vertex_data.vertexBufferBinding.getBuffer(posElem.getSource())

        # get the start of the actual buffer
        vertex = vbuf.lock(ogre.HardwareBuffer.HBL_READ_ONLY)

        # What we need is the actual address of the buffer,
        # so we have to check if there's an offset as well.
        # This is basically what baseVertexPointerToElement does.
        newaddress = posElem.getOffset() + ogre.castAsInt(vertex) # note the cast to int to get the address

        for i in range (vertex_data.vertexCount):
            points = ogre.getFloat(ogre.castAsVoidPtr(newaddress), 3) # note the getFloat and Cast back to a pointer :)

            #_transform
            vec = transform * ogre.Vector3(points[0], points[1], points[2])
            outbuff.append(tuple((vec.x, vec.y, vec.z)))
            newaddress += vbuf.getVertexSize()
        vbuf.unlock()
        return outbuff

    @staticmethod
    def getBoundingBox(entity):
        """Mesh Extents AxisAligned Box"""
        vertices = []
        minExtent = ogre.Vector3(9999, 9999, 9999)
        maxExtent = ogre.Vector3(-9999, -9999, -9999)

        if entity.getMesh().sharedVertexData:
            vertices += MeshInfo.GetVerticies(
                      entity.getMesh().sharedVertexData,
                      entity.getParentSceneNode()._getFullTransform())
        for m in range(entity.getMesh().numSubMeshes):
            sm = entity.getMesh().getSubMesh(m)
            if not sm.useSharedVertices:
                vertices += MeshInfo.GetVerticies (
                       sm.vertexData,
                       entity.getParentSceneNode()._getFullTransform())
        for vert in vertices:
            minExtent.x = min(minExtent.x, vert[0])
            minExtent.y = min(minExtent.y, vert[1])
            minExtent.z = min(minExtent.z, vert[2])
            maxExtent.x = max(maxExtent.x, vert[0])
            maxExtent.y = max(maxExtent.y, vert[1])
            maxExtent.z = max(maxExtent.z, vert[2])

        del vertices
        return ogre.AxisAlignedBox(minExtent, maxExtent)

    @staticmethod
    def getExtentsRadius(mesh):
        """Mesh Extents Radius"""
        e = MeshInfo.getBoundingBox(mesh)
        minv = e.getMinimum()
        maxv = e.getMaximum()

        size = ogre.Vector3(abs(maxv.x - minv.x),
                            abs(maxv.y - minv.y),
                            abs(maxv.z - minv.z))
        radius = max(max(size.x, size.y), size.z) / 2.0
        return radius

    @staticmethod
    def createBoxShape(entity, unitScale=True):
        """Bullet Box Shape"""
        ## mesh extents
        e = MeshInfo.getBoundingBox(entity)
        size = bullet.btVector3(e.getHalfSize().x,
                                e.getHalfSize().y,
                                e.getHalfSize().z)
        print size.x(), size.y(), size.z()
        return bullet.btBoxShape(size)

    @staticmethod
    def createSphereShape(entity):
        """Bullet Sphere Shape"""
        ## mesh extents
        radius = MeshInfo.getExtentsRadius(entity)
        return bullet.btSphereShape(radius)

    @staticmethod
    def createCylinderShape(entity, axis):
        """Bullet Cylinder Shape"""
        ## mesh extents
        e = MeshInfo.getBoundingBox(entity)
        size = bullet.btVector3(e.getHalfSize().x,
                                e.getHalfSize().y,
                                e.getHalfSize().z)
        shape = None
        if axis == BulletShapes.CYLINDERX:
            height = size.x()
            radius = max(size.z(), size.y())
            shape = bullet.btCylinderShapeX(bullet.btVector3(height, radius, radius))
        if axis == BulletShapes.CYLINDERY:
            height = size.y()
            radius = max(size.z(), size.x())
            shape = bullet.btCylinderShape(bullet.btVector3(radius, height, radius))
        if axis == BulletShapes.CYLINDERZ:
            height = size.z()
            radius = max(size.x(), size.y())
            shape = bullet.btCylinderShapeZ(bullet.btVector3(radius, radius, height))
        return shape

    @staticmethod
    def createConeShape(entity, axis):
        """Bullet Cone Shape"""
        e = MeshInfo.getBoundingBox(entity)
        size = bullet.btVector3(e.getHalfSize().x,
                                e.getHalfSize().y,
                                e.getHalfSize().z)
        shape = None
        if axis == BulletShapes.CONEX:
            height = size.x()
            radius = max(size.z(), size.y()) / 2.0
            shape = bullet.btConeShapeX(radius, height)
        if axis == BulletShapes.CONEY:
            height = size.y()
            radius = max(size.x(), size.z()) / 2.0
            shape = bullet.btConeShape(radius, height)
        if axis == BulletShapes.CONEZ:
            height = size.z()
            radius = max(size.x(), size.y()) / 2.0
            shape = bullet.btConeShapeZ(radius, height)
        return shape

    @staticmethod
    def createTriMeshShape(entity):
        """Bullet Triangle Mesh Shape"""
        vertices = []
        faces = []

        if entity.getMesh().sharedVertexData:
            vertices += MeshInfo.GetVerticies(entity.getMesh().sharedVertexData,
                              entity.getParentSceneNode()._getFullTransform())

        for m in range(entity.getMesh().numSubMeshes):
            sm = entity.getMesh().getSubMesh(m)
            #print "Entity Shared ", entity.getMesh().sharedVertexData
            #print "Uses Shared Vertices ", sm.useSharedVertices
            #print "Uses Shared Vertices ", dir(sm.parent.sharedVertexData)

            if not sm.useSharedVertices:
                faces += MeshInfo.GetIndicies (sm.indexData)
                vertices += MeshInfo.GetVerticies (sm.vertexData, entity.getParentSceneNode()._getFullTransform())
                #print "ENTITY SUB MESH NO SHARED VERTEX DATA"
            else:
                faces += MeshInfo.GetIndicies (sm.indexData)


        logging.debug("Mesh faces: " + len(faces) + len(vertices))

        mTriMesh = bullet.btTriangleMesh()
        for ind in faces:
            v1 = vertices[ind[0]]
            v2 = vertices[ind[1]]
            v3 = vertices[ind[2]]
            b1 = bullet.btVector3(v1[0], v1[1], v1[2])
            b2 = bullet.btVector3(v2[0], v2[1], v2[2])
            b3 = bullet.btVector3(v3[0], v3[1], v3[2])
            #print b1.x(),b1.y(),b1.z()
            mTriMesh.addTriangle(b1, b2, b3)

        useQuantizedAABB = True
        del vertices
        del faces
        return mTriMesh, bullet.btBvhTriangleMeshShape(mTriMesh, useQuantizedAABB)


class DebugDrawer(bullet.btIDebugDraw):
    """DebugDrawer using Ogre ManualObject

    This kills the frame rate, but shows actual body positions for bullet
    objects and is therefore useful for debugging.
"""

    def __init__(self, sceneManager):
        bullet.btIDebugDraw.__init__(self)

        self.mDebugMode = bullet.btIDebugDraw.DBG_DrawWireframe
        self.beginLineUpdates = False
        self.beginTriUpdates = False
        self.mContactPoints = []

        mLines = ogre.ManualObject("Bullet Physics lines")
        mTriangles = ogre.ManualObject("Bullet Physics triangles")
        mLines.setDynamic(True)
        mTriangles.setDynamic(True)
        self.mSceneManager = sceneManager
        self.mSceneManager.getRootSceneNode().attachObject(mLines)
        self.mSceneManager.getRootSceneNode().attachObject(mTriangles)

        matName = "OgreBulletCollisionsDebugDefault"
        mtl = ogre.MaterialManager.getSingleton().getDefaultSettings().clone(matName)
        mtl.setReceiveShadows(False)
        mtl.setSceneBlending(ogre.SBT_TRANSPARENT_ALPHA)
        mtl.setDepthBias(0.1, 0)
        tu = mtl.getTechnique(0).getPass(0).createTextureUnitState()
        tu.setColourOperationEx(ogre.LBX_SOURCE1, ogre.LBS_DIFFUSE)
        mtl.getTechnique(0).setLightingEnabled(False)
        ##mtl.getTechnique(0).setSelfIllumination( ogre.ColourValue().White )

        mLines.begin(matName, ogre.RenderOperation.OT_LINE_LIST)
        mLines.position(ogre.Vector3().ZERO)
        mLines.colour(ogre.ColourValue().Blue)
        mLines.position(ogre.Vector3().ZERO)
        mLines.colour(ogre.ColourValue().Blue)

        mTriangles.begin(matName, ogre.RenderOperation.OT_TRIANGLE_LIST)
        mTriangles.position(ogre.Vector3().ZERO)
        mTriangles.colour(ogre.ColourValue().Blue)
        mTriangles.position(ogre.Vector3().ZERO)
        mTriangles.colour(ogre.ColourValue().Blue)
        mTriangles.position(ogre.Vector3().ZERO)
        mTriangles.colour(ogre.ColourValue().Blue)

        self.mLines = mLines
        self.mTriangles = mTriangles

    def __del__(self):
        self.mSceneManager.getRootSceneNode().detachObject(self.mLines)
        self.mSceneManager.getRootSceneNode().detachObject(self.mTriangles)
        del self.mLines
        del self.mTriangles

    def frameRenderingQueued(self, evt):
        self.mLines.end()
        self.mLines.beginUpdate(0)

        now = ogre.Root.getSingleton().getTimer().getMilliseconds()

        newCP = []
        for p in self.mContactPoints:
            self.mLines.position(p._from)
            self.mLines.colour(p.colour)
            self.mLines.position(p._to)
            self.mLines.colour(p.colour)
            if now <= p.dieTime:
                newCP.append(p)
        self.mContactPoints = newCP

    def frameEnded(self, evt):
        self.beginLineUpdates = False
        self.beginTriUpdates = False

    def showdebugContactInfo(self, p):
        #print ("Start (%f,%f,%f) End (%f,%f,%f)" %(p._from.x,p._from.y,p._from.z,
#p._to.x,p._to.y,p._to.z) )
        pass

    def drawContactPoint(self, PointOnB, normalOnB, distance, lifeTime, color):
        p = ContactPoint()
        p._from = ogre.Vector3(PointOnB.x(), PointOnB.y(), PointOnB.z())
        p._to = p._from + ogre.Vector3(normalOnB.x(), normalOnB.y(), normalOnB.z()) * distance
        p.dieTime = ogre.Root.getSingleton().getTimer().getMilliseconds() + lifeTime
        p.colour.r = color.x()
        p.colour.g = color.y()
        p.colour.b = color.z()
        self.mContactPoints.append(p)

    def drawLine(self, btVectorFrom , btVectorTo, colour):
        mLines = self.mLines
        c = ogre.ColourValue(colour.getX(), colour.getY(), colour.getZ())
        c.saturate()
        mLines.position(btVectorFrom.x(), btVectorFrom.y(), btVectorFrom.z())
        mLines.colour(c)
        mLines.position(btVectorTo.x(), btVectorTo.y(), btVectorTo.z())
        mLines.colour(c)

    def drawTriangle(self, v0, v1, v2, colour, alpha):
        #if not self.beginTriUpdates:
        #    self.beginTriUpdates = True
        #    self.mTriangles.beginUpdate(0)
        #mTriangles = self.mTriangles
        #c = ogre.ColourValue(colour.getX(), colour.getY(), colour.getZ(), alpha)
        #c.saturate()
        #mTriangles.position(v0.x(), v0.y(), v0.z())
        #mTriangles.colour(c)
        #mTriangles.position(v1.x(), v1.y(), v1.z())
        #mTriangles.colour(c)
        #mTriangles.position(v2.x(), v2.y(), v2.z())
        #mTriangles.colour(c)
        pass

    def drawAabb(self, btVecFrom, btVecTo, btVecColor):
        bullet.btIDebugDraw.drawAabb(self, btVecFrom, btVecTo, btVecColor)

    def reportErrorWarning(self, warningString):
        logging.debug("Bullet DebugDrawer: " + warningString)

    def draw3dText(self, btVecLocation, textString):
        pass

    def setDebugMode(self, idebugMode):
        self.mDebugMode = idebugMode

    def getDebugMode(self):
        return self.mDebugMode


class OgreMotionState(bullet.btMotionState):
    """Update OGRE SceneNodes from Collision Objects"""

    def __init__(self, initalPosition, node):
        bullet.btMotionState.__init__(self)
        self.mWorldTrans = initalPosition
        self.mParentNode = node

    def getWorldTransform(self, WorldTrans):
        WorldTrans.setOrigin(self.mWorldTrans.getOrigin())
        WorldTrans.setBasis(self.mWorldTrans.getBasis())

    def setWorldTransform(self, WorldTrans):
        x = WorldTrans.getOrigin().x()
        y = WorldTrans.getOrigin().y()
        z = WorldTrans.getOrigin().z()
        p = ogre.Vector3(x, y, z)
        q = ogre.Quaternion(WorldTrans.getRotation().w(),
                            WorldTrans.getRotation().x(),
                            WorldTrans.getRotation().y(),
                            WorldTrans.getRotation().z())
        self.mParentNode.setOrientation(q)
        self.mParentNode.setPosition(x, y , z)


class CollisionObject():
    """Collision Objects"""

    def __init__(self, dynamicsWorld):
        """Base Collision Object for Testing"""
        self.mShape = None
        self.dynamicsWorld = dynamicsWorld
        self.mRigidBody = None
        self.mTransform = bullet.btTransform()
        self.mTransform.setIdentity()
        self.mInertia = bullet.btVector3(0, 0, 0)
        self.mMotionState = None
        self.mMass = 0.0
        self.mTriMesh = None

    def __del__(self):
        self.dynamicsWorld.removeRigidBody(self.mRigidBody)
        if self.mTriMesh:
            del self.mTriMesh
        if self.mShape:
            del self.mShape
        del self.mRigidBody
        del self.mMotionState

    def isDynamic(self):
        if (self.mMass != 0.0):
            return True
        return False

    def setInertia(self, inertia):
        self.mInertia = inertia
        if self.isDynamic():
            self.mShape.calculateLocalInertia(self.mMass, self.mInertia)

    def setShape(self, shape):
        self.mShape = shape

    def setMass(self, mass):
        # A Bullet rigidbody is dynamic if and only if mass is non zero.
        self.mMass = mass

    def setTransform(self, origin, rot=None):
        self.mTransform.setOrigin(origin)
        if (rot):
            self.mTransform.setRotation(rot)

    def setMotion(self, mParentNode):
        if not self.isDynamic():
            self.mMotionState = bullet.btDefaultMotionState(self.mTransform)
        else:
            self.mMotionState = OgreMotionState(self.mTransform, mParentNode)

        rigidbody_info = bullet.btRigidBody.btRigidBodyConstructionInfo(
                                                        self.mMass,
                                                        self.mMotionState,
                                                        self.mShape,
                                                        self.mInertia)
        self.mRigidBody = bullet.btRigidBody(rigidbody_info)
        self.dynamicsWorld.addRigidBody(self.mRigidBody)
        self.mRigidBody.setUserData(mParentNode)


class BulletShapes:
    """Bullet built-in shapes."""
    PLANE, BOX, SPHERE, CYLINDERX, CYLINDERY, CYLINDERZ, CONEX, CONEY, CONEZ, TRIMESH = range(10)

