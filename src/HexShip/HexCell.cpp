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
#include "PhysicsManager.h"

btCollisionShape* HexCell::mHexCellShape;

HexCell::HexCell() { HexCell("HexCell", Ogre::Vector3(0,0,0)); }

HexCell::HexCell(const Ogre::String& name, const Ogre::Vector3& pos) {
    Ogre::SceneManager *sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("ST_GENERIC");
    btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();

    // Create hex cell
    mHexCell = sceneMgr->createEntity(name, "HexCell.mesh");
    mHexCellNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name + "Node", pos);
    mHexCellNode->attachObject(mHexCell);
    btCollisionShape *hexCellShape = getCollisionShapePtr();
    BtOgre::RigidBodyState *state = new BtOgre::RigidBodyState(mHexCellNode);
    btScalar mass = 1;
    mHexCellRigidBody = new btRigidBody(mass, state, hexCellShape);
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

HexCell::~HexCell() {
    btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();
    btDynamicsWorld->removeRigidBody(mHexCellRigidBody);
    delete mHexCellRigidBody->getMotionState();
    delete mHexCellRigidBody;

    //XXX: delete OGRE objects
}


void HexCell::update( unsigned long lTimeElapsed ) {
}


void HexCell::applyCentralImpulse(const Ogre::Vector3& impulse) {
    mHexCellRigidBody->activate(true);
    mHexCellRigidBody->applyCentralImpulse(BtOgre::Convert::toBullet(impulse));
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

