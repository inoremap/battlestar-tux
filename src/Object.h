/* Object.h
 *
 * Copyright 2005-2007 Eliot Eshelman
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

#include "ListItem.h"
#include "Vector.h"

class ObjectList;

enum ObjectType {
	FIGHTER		=	0X0001,				// Entire aircraft
	CELL			=	0x0002,				// Aircraft component
	SHIELD		=	0x0004,				// Aircraft shield
	AMMO			=	0x0008,				// Weapon ammo
	HEROS_AMMO	=	0x0010 | AMMO,		// Hero's ammo
	ENEMY_AMMO	=	0x0020 | AMMO,		// Enemies' ammo
	EFFECTOR		=	0X0040				// Physical effects such as explosions and gravity wells
};


/* Any object which has a physical presence should inherit this. */
class Object : public ListItem {
	public:
				Object( ObjectType );
				virtual ~Object();

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

				// Apply an acceleration to the object.
				void accel( const vec3 & );

				// The maximum length of the object along any plane at any angle.
				// This needs to be updated if the object ever changes size.
				// The size is used to determine the sphere-boundary for collision detection.
				void setSize( float s ) { size = s; }

				// Statically set the position of the object.
				// You don't normally do this.
				void setPos( const vec3 &p ) { pos = p; }

				// Statically set the velocity of the object.
				// You don't normally do this.
				void setVel( const vec3 &v ) { vel = v; }

				void setRot( const vec3 &r ) { rot = r; }
				void setTorque( const vec3 &t ) { torque = t; }

				void setMass( float m ) { mass = m; }

				void setHealth( float h ) { health = h; }
				void setFullHealth( float h ) { fullHealth = h; }

				void setType( ObjectType t ) { type = t; }

				virtual float getSize() { return size; }
				virtual vec3 getPos() { return pos; }
				virtual vec3 getVel() { return vel; }
				virtual vec3 getRot() { return rot; }
				virtual vec3 getTorque() { return torque; }
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
				// Position (X, Y, Z) at center of object (meters).
				vec3 pos;

				// Velocity (X, Y, Z)
				// Number of units to move in each direction each frame.
				// Remember that the game runs at 50 FPS, regardless of what the
				// user's screen is actually displaying.
				vec3 vel;

				// Rotation (Degrees)
				// The angular position of the object (counter-clockwise).
				vec3 rot;

				// Torque (Degrees)
				// The angular velocity of the object (counter-clockwise).
				vec3 torque;

				// Maximum size of object.
				float size;

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
