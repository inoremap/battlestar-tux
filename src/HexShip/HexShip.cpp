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

#include <btGeneric6DofConstraint.h>
#include <Ogre.h>
#include <BtOgreExtras.h>

#include "HexShip.h"
#include "PlayState.h"
#include "PhysicsManager.h"

HexShip::HexShip() { HexShip("HexShip", Ogre::Vector3(0,0,0)); }

HexShip::HexShip(const Ogre::String& name, const Ogre::Vector3& pos) {
    Ogre::SceneManager *sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("ST_GENERIC");
    btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();

    // Create player's ship
    mHexShip = sceneMgr->createEntity(name, "HexCell.mesh");
    mHexShipNode = sceneMgr->getRootSceneNode()->createChildSceneNode(name + "Node", pos);
    mHexShipNode->attachObject(mHexShip);
    mHexCellShape = new btCylinderShape(btVector3(1.3,0.3,1.3));
    btScalar mass = 1;
    btVector3 inertia;
    mHexCellShape->calculateLocalInertia(mass, inertia);
    BtOgre::RigidBodyState *state = new BtOgre::RigidBodyState(mHexShipNode);
    mHexCellRigidBody = new btRigidBody(mass, state, mHexCellShape, inertia);
    mHexCellRigidBody->setDamping(0.1, 0.5);
    btDynamicsWorld->addRigidBody(mHexCellRigidBody);

    // Limit all HexShips to a single "gameplay" plane
    mHexCellRigidBody->setLinearFactor(btVector3(1,0,1));
    // Limit rotations of HexShips to keep them close to the plane
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

HexShip::~HexShip() {
    btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();
    btDynamicsWorld->removeRigidBody(mHexCellRigidBody);
    delete mHexCellRigidBody->getMotionState();
    delete mHexCellRigidBody;
    delete mHexCellShape;
}


void HexShip::update( unsigned long lTimeElapsed ) {
}


void HexShip::applyCentralImpulse(const Ogre::Vector3& impulse) {
    mHexCellRigidBody->applyCentralImpulse(BtOgre::Convert::toBullet(impulse));
}
