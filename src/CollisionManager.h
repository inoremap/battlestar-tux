/* CollisionManager.h
 *
 * Copyright 2008 Eliot Eshelman
 * battlestartux@6by9.net
 *
 *
 *  This file is part of Battlestar Tux.
 *
 *  Battlestar Tux is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  Battlestar Tux is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Battlestar Tux; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

#include "BroadphaseCollision/btSimpleBroadphase.h"
#include "CollisionDispatch/btCollisionDispatcher.h"
#include "CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "Dynamics/btDiscreteDynamicsWorld.h"
#include "Dynamics/btRigidBody.h"
#include "LinearMath/btMotionState.h"


/* All object collisions are detected and managed here.
 * Any object in the game will have an entry here.
 */
class CollisionManager {
	public:
				CollisionManager();
				~CollisionManager();


	private:
				CollisionManager( const CollisionManager & );
				const CollisionManager & operator= ( const CollisionManager & );

				btDefaultCollisionConfiguration* collision_configuration;
				btCollisionDispatcher* collision_dispatcher;
				btBroadphaseInterface* broadphase;
				btSequentialImpulseConstraintSolver* constraint_solver;
				btDiscreteDynamicsWorld* dynamics_world;
};


#endif /*COLLISIONMANAGER_H_*/
