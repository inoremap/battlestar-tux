/* Object.h
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


#ifndef OBJECT_H_
#define OBJECT_H_

#include <SDL_opengl.h>
#include "CollisionShapes/btCollisionShape.h"
#include "Dynamics/btRigidBody.h"
#include "btDefaultMotionState.h"


#include "CollisionManager.h"
#include "ListItem.h"
#include "Vector.h"

class ObjectList;

enum ObjectType {
	FIGHTER		=	0x0001,				// Entire aircraft
	CELL		=	0x0002,				// Aircraft component
	SHIELD		=	0x0004,				// Aircraft shield
	AMMO		=	0x0008,				// Weapon ammo
	HEROS_AMMO	=	0x0010 | AMMO,		// Hero's ammo
	ENEMY_AMMO	=	0x0020 | AMMO,		// Enemies' ammo
	EFFECTOR	=	0x0040				// Physical effects such as explosions and gravity wells
};


/* Any object which has a physical presence should inherit this. */
class Object : public ListItem {
	public:
				Object( const ObjectType, const float );
				virtual ~Object();

				// Initialize Object's physical presence and add to world.
				void addToWorld();

				// Update object positioning and other data.
				virtual void Update( int );

				// Draw the object to the screen.
				//
				// Textures are enabled, so you need to bind
				// a null texture if you don't want any textures.
				virtual void Draw();

				// Object has been impacted by damaging energy.
				// If the object cannot absorb this much energy,
				// it must return the amount it didn't absorb.
				virtual float damage( float );

				// The object has sustained too much damage.
				// It has been destroyed.
				virtual void destroy();

				// Apply an acceleration to the object.
				void accel( const vec3 & );

				// Apply a torque to the object.
				void torque( const vec3 & );

				void setHealth( float h ) { health = h; }
				void setFullHealth( float h ) { fullHealth = h; }

				void setType( ObjectType t ) { type = t; }

				// Position and orientation are provided by Bullet physics.
				virtual vec3 getPos();
				virtual void setPos( vec3 & );
				virtual vec3 getVel();
				virtual void setVel( vec3 & );
				virtual vec3 getRot();

				virtual unsigned int getAge() { return age; }
				virtual float getMass() { return mass; }
				virtual float getHealth() { return health; }
				virtual float getFullHealth() { return fullHealth; }
				virtual int getType() { return type; }

				// If this object is actually made up of smaller components,
				// some methods may want to deal with them individually.
				virtual bool hasComponents() { return false; }
				virtual ObjectList* getComponents() { return 0; }


	protected:
				// Bullet physics library handles all dynamics and collisions.
				btRigidBody* m_rigidBody;
				btDefaultMotionState* m_motionState;
				CollisionManager* collisionManager;

				// All objects need to define their collision shape.
				// It is best for that shape to be static, so that all instances
				// may share the same object.
				virtual btCollisionShape* getCollisionShape() = 0;


				// Age of object in frames
				unsigned int age;

				// Mass of the object (kilograms).
				float mass;

				// How much energy damage can still be absorbed before destruction.
				float health;

				// The most energy damage this object can ever absorb.
				float fullHealth;

				// Type of Object.
				int type;

	private:
				Object( const Object & );
				const Object & operator= ( const Object & );
};


#endif /*OBJECT_H_*/
