/* CollisionManager.cpp
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


#include "CollisionManager.h"


CollisionManager* CollisionManager::collisionManager = 0;

CollisionManager* CollisionManager::getCollisionManager() {
	if( collisionManager == 0 )
		collisionManager = new CollisionManager();

	return collisionManager;
}


CollisionManager::CollisionManager() {
	collision_configuration = new btDefaultCollisionConfiguration();
	collision_dispatcher = new btCollisionDispatcher(collision_configuration);
	broadphase = new btSimpleBroadphase();
	constraint_solver = new btSequentialImpulseConstraintSolver();
	dynamics_world = new btDiscreteDynamicsWorld(collision_dispatcher, broadphase, constraint_solver, collision_configuration);

	dynamics_world->setGravity(btVector3(0, 0, 0));
}


CollisionManager::~CollisionManager() {
	delete dynamics_world;
	delete constraint_solver;
	delete broadphase;
	delete collision_dispatcher;
	delete collision_configuration;

	collisionManager = 0;
}


void CollisionManager::Update() {
	dynamics_world->stepSimulation( 1.f/60.f, 0 );
}


void CollisionManager::addObject( btRigidBody* body ) {
	dynamics_world->addRigidBody( body );
}

void CollisionManager::remObject( btRigidBody* body ) {
	dynamics_world->removeRigidBody( body );
}

