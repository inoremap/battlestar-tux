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


#ifndef PhysicsManager_H
#define PhysicsManager_H

#include <btBulletDynamicsCommon.h>
#include <BtOgrePG.h>
#include <BtOgreGP.h>

class PhysicsManager {
public:
    ~PhysicsManager();

    void update( unsigned long lTimeElapsed );

    btDiscreteDynamicsWorld* getDynamicsWorld() { return mDynamicsWorld; }
    btRigidBody* getGroundRigidBody() { return mGroundRigidBody; }

    static PhysicsManager* getSingletonPtr();

private:
    PhysicsManager();
    PhysicsManager( const PhysicsManager& );
    PhysicsManager & operator = ( const PhysicsManager& );

    btAxisSweep3 *mBroadphase;
    btDefaultCollisionConfiguration *mCollisionConfiguration;
    btCollisionDispatcher *mDispatcher;
    btSequentialImpulseConstraintSolver *mSolver;
    btDiscreteDynamicsWorld *mDynamicsWorld;

    BtOgre::DebugDrawer *mBtDebugDrawer;

    // Ground upon which the game falls.
    // In bullet, objects need a static object upon which to base their
    // motion constraints.  If there isn't a real ground (such as outer space),
    // this should be an imaginary plane below the gameplay.
    btCollisionShape *mGroundShape;
    btRigidBody *mGroundRigidBody;

    static PhysicsManager *mPhysicsManager;
};

#endif
