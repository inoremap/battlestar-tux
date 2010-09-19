/* Battlestar TUX
 * Copyright (C) 2010 Eliot Eshelman <battlestartux@6by9.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <btGeneric6DofConstraint.h>
#include <Ogre.h>
#include <BtOgreExtras.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "WeaponCell.h"
#include "BoltWeaponCell.h"
#include "PhysicsManager.h"


BoltWeaponCell::BoltWeaponCell(const std::string& name, const float mass, const float hitPoints,
                            const float damagePoints, const float energyRequired,
                            const unsigned long restTime) :
    WeaponCell(name, mass, hitPoints, damagePoints, energyRequired, restTime, BOLT_WEAPON)
{
}


BoltWeaponCell::~BoltWeaponCell() {
}


void BoltWeaponCell::activateWeapon() {
    std::cout << "Shoot bolt!" << std::endl;
}


void BoltWeaponCell::createWeaponSphere(const float r, const int nRings, const int nSegments) {
    // Code retrieved from OGRE wiki: ManualSphereMeshes

    std::string strName = "WeaponSphere";

    Ogre::MeshPtr pSphere = Ogre::MeshManager::getSingleton().createManual(strName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::SubMesh *pSphereVertex = pSphere->createSubMesh();

    pSphere->sharedVertexData = new Ogre::VertexData();
    Ogre::VertexData* vertexData = pSphere->sharedVertexData;

    // define the vertex format
    Ogre::VertexDeclaration* vertexDecl = vertexData->vertexDeclaration;
    size_t currOffset = 0;
    // positions
    vertexDecl->addElement(0, currOffset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
    currOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
    // normals
    vertexDecl->addElement(0, currOffset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
    currOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
    // two dimensional texture coordinates
    vertexDecl->addElement(0, currOffset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES, 0);
    currOffset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT2);

    vertexData->vertexCount = (nRings + 1) * (nSegments+1);
    Ogre::HardwareVertexBufferSharedPtr vBuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(vertexDecl->getVertexSize(0), vertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
    Ogre::VertexBufferBinding* binding = vertexData->vertexBufferBinding;
    binding->setBinding(0, vBuf);
    float* pVertex = static_cast<float*>(vBuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

    pSphereVertex->indexData->indexCount = 6 * nRings * (nSegments + 1);
    pSphereVertex->indexData->indexBuffer = Ogre::HardwareBufferManager::getSingleton().createIndexBuffer(Ogre::HardwareIndexBuffer::IT_16BIT, pSphereVertex->indexData->indexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, false);
    Ogre::HardwareIndexBufferSharedPtr iBuf = pSphereVertex->indexData->indexBuffer;
    unsigned short* pIndices = static_cast<unsigned short*>(iBuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

    float fDeltaRingAngle = (M_PI / nRings);
    float fDeltaSegAngle = (2 * M_PI / nSegments);
    unsigned short wVerticeIndex = 0 ;

    // Generate the group of rings for the sphere
    for(int ring = 0; ring <= nRings; ring++) {
        float r0 = r * sinf(ring * fDeltaRingAngle);
        float y0 = r * cosf(ring * fDeltaRingAngle);

        // Generate the group of segments for the current ring
        for(int seg = 0; seg <= nSegments; seg++) {
            float x0 = r0 * sinf(seg * fDeltaSegAngle);
            float z0 = r0 * cosf(seg * fDeltaSegAngle);

            // Add one vertex to the strip which makes up the sphere
            *pVertex++ = x0;
            *pVertex++ = y0;
            *pVertex++ = z0;

            Ogre::Vector3 vNormal = Ogre::Vector3(x0, y0, z0).normalisedCopy();
            *pVertex++ = vNormal.x;
            *pVertex++ = vNormal.y;
            *pVertex++ = vNormal.z;

            *pVertex++ = (float) seg / (float) nSegments;
            *pVertex++ = (float) ring / (float) nRings;

            if (ring != nRings) {
                // each vertex (except the last) has six indices pointing to it
                *pIndices++ = wVerticeIndex + nSegments + 1;
                *pIndices++ = wVerticeIndex;
                *pIndices++ = wVerticeIndex + nSegments;
                *pIndices++ = wVerticeIndex + nSegments + 1;
                *pIndices++ = wVerticeIndex + 1;
                *pIndices++ = wVerticeIndex;
                wVerticeIndex ++;
            }
        }
    }

    // Unlock
    vBuf->unlock();
    iBuf->unlock();
    // Generate face list
    pSphereVertex->useSharedVertices = true;

    pSphere->_setBounds(Ogre::AxisAlignedBox(Ogre::Vector3(-r, -r, -r), Ogre::Vector3(r, r, r)), false);
    pSphere->_setBoundingSphereRadius(r);
    pSphere->load();
}


/*btCollisionShape* BoltWeaponCell::getCollisionShapePtr() {
    if(! mWeaponShape) {
        mWeaponShape = new btSphereShape(0.5);
        btScalar mass = 1;
        btVector3 inertia  = btVector3(0,0,0);
        mWeaponShape->calculateLocalInertia(mass, inertia);
    }

    return mWeaponShape;
}*/

