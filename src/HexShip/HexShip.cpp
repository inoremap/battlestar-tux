/* Battlestar TUX
 * Copyright (C) 2008-2009 Eliot Eshelman <battlestartux@6by9.net>
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

    Ogre::SceneManager *sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("ST_GENERIC");
    mOgreNode = sceneMgr->getRootSceneNode()->createChildSceneNode(mName + "Node", pos);
}

HexShip::~HexShip() {
    delete mCoreCell;

    btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();
    btDynamicsWorld->removeRigidBody(mHexShipRigidBody);
    delete mHexShipRigidBody->getMotionState();
    delete mHexShipRigidBody;

    delete mOgreNode;
}


void HexShip::addHexCell(HexCell* cell, const Ogre::Vector3& offset) {
    // Calculate world position of cell using provided offset.
    cell->attachCell(this, offset);
    mShipCells.push_back(cell);

    mMass += cell->getMass();
    rebuildCollisionHull();
}


void HexShip::addCoreHexCell(HexCell* cell, const Ogre::Vector3& offset) {
    mCoreCell = cell;
    this->addHexCell(cell, offset);
}


void HexShip::removeHexCell(HexCell* cell) {
    assert(cell != mCoreCell);

    // Find and remove the correct HexCell.
    std::vector<HexCell*>::iterator iter;
    for(iter = mShipCells.begin(); iter != mShipCells.end(); iter++) {
        if(*iter == cell)
            mShipCells.erase(iter);
    }

    mMass -= cell->getMass();
    rebuildCollisionHull();

    cell->separateCell();
}


void HexShip::update( unsigned long lTimeElapsed ) {
    // Update each HexCell
    std::vector<HexCell*>::iterator iter;
    for(iter = mShipCells.begin(); iter != mShipCells.end(); iter++) {
        (*iter)->update(mOgreNode->getPosition(), lTimeElapsed);
    }
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
        btTransform cellShapeTrans(btQuaternion(),
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

