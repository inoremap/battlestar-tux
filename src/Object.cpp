/* Object.cpp
 *
 * Copyright 2005-2008 Eliot Eshelman
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


#include "Object.h"


Object::Object( const ObjectType t, const float m ) {
	m_rigidBody = 0;
	m_motionState = 0;
	collisionManager = 0;
	age = 0;
	mass = m;
	health = 1;
	fullHealth = 1;
	type = t;
}


Object::~Object() {
	// If this Object is in the physics simulation, remove it.
	if( collisionManager ) {
		collisionManager->remObject( m_rigidBody );

		delete m_rigidBody;
		delete m_motionState;
	}
}


void Object::addToWorld() {
	collisionManager = CollisionManager::getCollisionManager();

	btCollisionShape* collisionShape = getCollisionShape();

	btVector3 localInertia( 0, 0, 0 );
	// If the object isn't static, we need its inertia.
	if( mass > 0 )
		collisionShape->calculateLocalInertia( mass, localInertia );

	// The object will start at (0, 0, 0)
	m_motionState = new btDefaultMotionState();

	btRigidBody::btRigidBodyConstructionInfo cInfo( mass, m_motionState, collisionShape, localInertia );
	m_rigidBody = new btRigidBody( cInfo );

	collisionManager->addObject( m_rigidBody );
}


void Object::Update( int speed ) {
	// If the object has no health, it has been destroyed.
	if( health <= 0 )
		destroy();

	age += speed;
}


void Object::Draw() {
	// Set the OpenGL modelview transforms for this object from Bullet physics.
	btScalar m[16];
	m_motionState->m_graphicsWorldTrans.getOpenGLMatrix( m );
	glMultMatrixf( m );
}


float Object::damage( float damage ) {
	if( damage >= health ) {
		damage -= health;
		health = 0;

		return damage;
	}
	else {
		health -= damage;
		return 0;
	}
}


void Object::destroy() { delete this; }


void Object::accel( const vec3 &force ) {}


void Object::torque( const vec3 &t ) {} 


vec3 Object::getPos() {
	btVector3 pos = m_motionState->m_graphicsWorldTrans.getOrigin(); 
	return vec3( pos[0], pos[1], pos[2] );
}

void Object::setPos( vec3 &v ) {
	btVector3 btV( v[0], v[1], v[2] );
	m_motionState->m_graphicsWorldTrans.setOrigin( btV );
}

vec3 Object::getVel() {
	btVector3 vel = ( m_rigidBody->getWorldTransform().getBasis().transpose() *
						m_rigidBody->getLinearVelocity() );
	return vec3( vel[0], vel[1], vel[2] );
}

void Object::setVel( vec3 &v ) {
	btVector3 btV( v[0], v[1], v[2] );
	m_rigidBody->setLinearVelocity( btV );
}

vec3 Object::getRot() {
	float x, y, z;
	m_rigidBody->getWorldTransform().getBasis().getEuler( x, y, z );
	return vec3( x, y, z );
}

