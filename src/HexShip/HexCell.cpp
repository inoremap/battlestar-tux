/* Battlestar TUX
 * Copyright (C) 2009 Eliot Eshelman <battlestartux@6by9.net>
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

#include "HexCell.h"
#include "HexShip.h"
#include "PhysicsManager.h"

btCollisionShape* HexCell::mHexCellShape;


HexCell::HexCell(const std::string& name, const float mass, const float hitPoints) :
    mName(name),
    mMass(mass),
    mMaxHp(hitPoints),
    mHp(hitPoints),
    mOffset()
{
    Ogre::SceneManager *sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("ST_GENERIC");
    btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();

    // Create HexCell visual entity.
    mOgreEntity = sceneMgr->createEntity(mName, "HexCell.mesh");
    mOgreNode = sceneMgr->getRootSceneNode()->createChildSceneNode(mName + "Node", Ogre::Vector3());
    mOgreNode->attachObject(mOgreEntity);

    mHexCellRigidBody = NULL;
    mShip = NULL;
}


HexCell::~HexCell() {
    // Delete the Bullet collision object, if this cell had one.
    if(mHexCellRigidBody) {
        btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();
        btDynamicsWorld->removeRigidBody(mHexCellRigidBody);
        delete mHexCellRigidBody->getMotionState();
        delete mHexCellRigidBody;
    }

    delete mOgreNode;
    delete mOgreEntity;
}


void HexCell::update( unsigned long lTimeElapsed ) {
}


void HexCell::update(const Ogre::Vector3& shipPos, unsigned long lTimeElapsed) {
    //XXX: This will only set position, not orientation.
    mOgreNode->setPosition(shipPos + mOffset);
    this->update(lTimeElapsed);
}


void HexCell::damage(const float hitpoints) {
    mHp -= hitpoints;

    // This cell has been destroyed if there are no remaining hitpoints.
    if(mHp <= 0)
        destroy();
}


void HexCell::destroy() {
    //TODO: Create explosion and detach this cell from the ship.
    //Once the explosion has finished, this cell may be deleted.
}


void HexCell::attachCell(HexShip* ship, const Ogre::Vector3& offset) {
    // If this cell has been managing its own collisions, we must cease.
    if(mHexCellRigidBody) {
        btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();
        btDynamicsWorld->removeRigidBody(mHexCellRigidBody);
        delete mHexCellRigidBody->getMotionState();
        delete mHexCellRigidBody;
        mHexCellRigidBody = NULL;
    }

    mShip = ship;
    mOffset = offset;

    mOgreNode->setPosition(mShip->getOgreNode()->getPosition() + mOffset);
}


void HexCell::separateCell() {
    // This HexCell should not already have a rigidbody, as this would indicate
    // that this function was called multiple times.
    assert(!mHexCellRigidBody);

    mShip = NULL;
    mOffset = Ogre::Vector3();

    btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();

    // Add this individual HexCell to the collision world.
    BtOgre::RigidBodyState *state = new BtOgre::RigidBodyState(mOgreNode);
    mHexCellRigidBody = new btRigidBody(mMass, state, this->getCollisionShapePtr());
    mHexCellRigidBody->setDamping(0.1, 0.5);
    btDynamicsWorld->addRigidBody(mHexCellRigidBody);

    // Limit all HexCells to a single "gameplay" plane
    mHexCellRigidBody->setLinearFactor(btVector3(1,0,1));
    // Limit rotations of HexCells to keep them close to the plane
    btRigidBody *mGround = PhysicsManager::getSingletonPtr()->getGroundRigidBody();
    btGeneric6DofConstraint* smallTilt = new btGeneric6DofConstraint(
            *mHexCellRigidBody,
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


void HexCell::toXml(TiXmlElement* node) const {
    TiXmlElement* cellNode = new TiXmlElement("HexCell");

    //node->SetAttribute("name", mName);
    //node->SetDoubleAttribute("mass", mMass);

    // If a valid XML element wasn't passed, return one.
    // If a valid XML element was passed, link to it.
    if(!node)
        node = cellNode;
    else
        node->LinkEndChild(cellNode);
}


btCollisionShape* HexCell::getCollisionShapePtr() {
    if( !mHexCellShape ) {
        mHexCellShape = new btCylinderShape(btVector3(1.3,0.3,1.3));
        btScalar mass = 1;
        btVector3 inertia  = btVector3(0,0,0);
        mHexCellShape->calculateLocalInertia(mass, inertia);
    }

    return mHexCellShape;
}

