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

#include <Ogre.h>

#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::mPhysicsManager;

PhysicsManager::PhysicsManager() {
     btVector3 worldAabbMin(-10000, -10000, -10000);
     btVector3 worldAabbMax(10000, 10000, 10000);
     int maxProxies = 1024;
     mBroadphase = new btAxisSweep3(worldAabbMin, worldAabbMax, maxProxies);

     mCollisionConfiguration = new btDefaultCollisionConfiguration();
     mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);

     mSolver = new btSequentialImpulseConstraintSolver;

     mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfiguration);

     mDynamicsWorld->setGravity(btVector3(0, -10, 0));

     // Setup Bullet physics debug drawing
     mBtDebugDrawer = new BtOgre::DebugDrawer(
             Ogre::Root::getSingletonPtr()->getSceneManager("ST_GENERIC")->getRootSceneNode(),
             mDynamicsWorld);
     mDynamicsWorld->setDebugDrawer(mBtDebugDrawer);

     // Ground plane
     mGroundShape = new btStaticPlaneShape(btVector3(0,1,0), 1);
     btDefaultMotionState *groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
     btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(
             0, groundMotionState, mGroundShape, btVector3(0,0,0));
     mGroundRigidBody = new btRigidBody(groundRigidBodyCI);
     mDynamicsWorld->addRigidBody(mGroundRigidBody);
}


PhysicsManager::~PhysicsManager() {
    // Remove ground plane
    mDynamicsWorld->removeRigidBody(mGroundRigidBody);
    delete mGroundRigidBody->getMotionState();
    delete mGroundRigidBody;
    delete mGroundShape;

    // Cleanup Bullet simulation objects
    delete mDynamicsWorld;
    delete mSolver;
    delete mCollisionConfiguration;
    delete mDispatcher;
    delete mBroadphase;
}


void PhysicsManager::update( unsigned long lTimeElapsed ) {
    mDynamicsWorld->stepSimulation(1/60.f,10);
    mBtDebugDrawer->step();
}


PhysicsManager* PhysicsManager::getSingletonPtr() {
    if( !mPhysicsManager ) {
        mPhysicsManager = new PhysicsManager();
    }

    return mPhysicsManager;
}

