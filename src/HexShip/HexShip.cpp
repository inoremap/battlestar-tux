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

#include "HexShip.h"
#include "PlayState.h"
#include "PhysicsManager.h"

HexShip::HexShip() {
    Ogre::SceneManager *mSceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("ST_GENERIC");
    btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();

    // Create player's ship
    Ogre::Entity *player = mSceneMgr->createEntity( "Player", "HexCell.mesh" );
    mHexShipNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "PlayerHexShipNode", Ogre::Vector3(0, 10, 0) );
    mHexShipNode->attachObject(player);
    mHexCellShape = new btCylinderShapeZ(btVector3(1.3,1.3,0.3));
    btScalar mass = 5;
    btVector3 inertia;
    mHexCellShape->calculateLocalInertia(mass, inertia);
    BtOgre::RigidBodyState *state = new BtOgre::RigidBodyState(mHexShipNode);
    mHexCellRigidBody = new btRigidBody(mass, state, mHexCellShape, inertia);
    btDynamicsWorld->addRigidBody(mHexCellRigidBody);
}

HexShip::~HexShip() {
    Ogre::SceneManager *mSceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("ST_GENERIC");
    mSceneMgr->destroySceneNode("PlayerHexShipNode");
    mSceneMgr->destroyEntity("Player");

    btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();
    btDynamicsWorld->removeRigidBody(mHexCellRigidBody);
    delete mHexCellRigidBody->getMotionState();
    delete mHexCellRigidBody;
    delete mHexCellShape;
}


void HexShip::update( unsigned long lTimeElapsed ) {
}
