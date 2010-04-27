/* Battlestar TUX
 * Copyright (C) 2008-2010 Eliot Eshelman <battlestartux@6by9.net>
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

#include <assert.h>
#include <btGeneric6DofConstraint.h>
#include <Ogre.h>
#include <BtOgreExtras.h>

#include "HexShip.h"
#include "PhysicsManager.h"


HexShip::HexShip(const std::string& name, const Ogre::Vector3& pos) :
    mName(name),
    mShipCells()
{
    mMass = 0;

    mHexShipRigidBody = NULL;
    mHexShipShape = NULL;

    Ogre::SceneManager *sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("ST_GENERIC");
    mOgreNode = sceneMgr->getRootSceneNode()->createChildSceneNode(mName + "Node", pos);
}

HexShip::~HexShip() {
    btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();
    btDynamicsWorld->removeRigidBody(mHexShipRigidBody);
    delete mHexShipRigidBody->getMotionState();
    delete mHexShipRigidBody;

    // Clean up all hex cells
    std::vector<HexCell*>::iterator iter;
    for(iter = mShipCells.begin(); iter != mShipCells.end();) {
        delete *iter;
        iter = mShipCells.erase(iter);
    }

    //XXX: removing mOgreNode causes segfault.  Memory leak.
}


void HexShip::addHexCell(HexCell* cell, const int offsetX, const int offsetY) {
    // Although cells are added with 2D coordinates, the game is 3D.
    // In the game world, the ground plane is along the X and Z axis, with Y
    // pointing into the sky.  So Y offset is actually used for the Z position.

    // Calculate world position of cell using provided cell-sized offsets.
    float compensateZ = 0.0;
    if(offsetX % 2)
        compensateZ = 1.3;

    Ogre::Vector3 offset(
            2.25 * (float) offsetX,
            0,
            2.6 * (float) offsetY + compensateZ);

    cell->attachCell(this, offset);
    mShipCells.push_back(cell);

    mMass += cell->getMass();
    rebuildCollisionHull();
}


void HexShip::addCoreHexCell(HexCell* cell, const int offsetX, const int offsetY) {
    mCoreCell = cell;
    this->addHexCell(cell, offsetX, offsetY);
}


void HexShip::removeHexCell(HexCell* cell) {
    assert(cell != mCoreCell);

    // Find and remove the correct HexCell.
    std::vector<HexCell*>::iterator iter;
    for(iter = mShipCells.begin(); iter != mShipCells.end(); iter++) {
        if(*iter == cell) {
            mShipCells.erase(iter);
            break;
        }
    }

    mMass -= cell->getMass();
    rebuildCollisionHull();

    cell->separateCell();
}


void HexShip::update( unsigned long lTimeElapsed ) {
    // Update each HexCell
    std::vector<HexCell*>::iterator iter;
    for(iter = mShipCells.begin(); iter != mShipCells.end(); iter++)
        (*iter)->update(lTimeElapsed);
}


void HexShip::applyCentralImpulse(const Ogre::Vector3& impulse) {
    mHexShipRigidBody->activate(true);
    mHexShipRigidBody->applyCentralImpulse(BtOgre::Convert::toBullet(impulse));
}


void HexShip::toXml(TiXmlElement* node) const {
    TiXmlElement* shipNode = new TiXmlElement("HexShip");

    //shipNode->SetAttribute("name", mName);

    std::vector<HexCell*>::const_iterator iter;
    for(iter = mShipCells.begin(); iter != mShipCells.end(); iter++) {
        (*iter)->toXml(shipNode);
    }

    // If a valid XML element wasn't passed, return one.
    // If a valid XML element was passed, link to it.
    if(!node)
        node = shipNode;
    else
        node->LinkEndChild(shipNode);
}


void HexShip::rebuildCollisionHull() {
    btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();

    // If the collision shape already exists, remove it and create a new one.
    if(mHexShipRigidBody) {
        btDynamicsWorld->removeRigidBody(mHexShipRigidBody);
        delete mHexShipRigidBody->getMotionState();
        delete mHexShipRigidBody;
    }

    mHexShipShape = new btCompoundShape();

    // Add the collision shape of each HexCell.
    std::vector<HexCell*>::iterator iter;
    for(iter = mShipCells.begin(); iter != mShipCells.end(); iter++) {
        btTransform cellShapeTrans(
                btQuaternion(),
                BtOgre::Convert::toBullet((*iter)->getOffset()));
        mHexShipShape->addChildShape(cellShapeTrans, (*iter)->getCollisionShapePtr());
    }

    BtOgre::RigidBodyState *state = new BtOgre::RigidBodyState(mOgreNode);
    mHexShipRigidBody = new btRigidBody(mMass, state, mHexShipShape);
    mHexShipRigidBody->setDamping(0.1, 0.5);
    btDynamicsWorld->addRigidBody(mHexShipRigidBody);

    // Limit all HexShips to a single "gameplay" plane
    mHexShipRigidBody->setLinearFactor(btVector3(1,0,1));
    // Limit rotations of HexShips to keep them close to the plane
    btRigidBody *mGround = PhysicsManager::getSingletonPtr()->getGroundRigidBody();
    btGeneric6DofConstraint* smallTilt = new btGeneric6DofConstraint(
            *mHexShipRigidBody,
            *mGround,
            btTransform::getIdentity(),
            btTransform::getIdentity(),
            true);
    smallTilt->setLinearLowerLimit(btVector3(1,1,1));
    smallTilt->setLinearUpperLimit(btVector3(0,0,0));
    smallTilt->setAngularLowerLimit(btVector3(0,0,0));
    smallTilt->setAngularUpperLimit(btVector3(0,0,0));
    btDynamicsWorld->addConstraint(smallTilt);
}

