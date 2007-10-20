/* Displayable.h
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


#ifndef DISPLAYABLE_H_
#define DISPLAYABLE_H_

#include <SDL_opengl.h>

#include "ListItem.h"
#include "Vector.h"

enum DisplayableType {
	GROUND		=	0x0001,				// Ground segment
	EFFECT		=	0x0002,				// Special effect - not a real object
	HUD			=	0x0004				// Items drawn as part of the UI
};


/* Any item which appears on the screen is Displayable.
 * Note that objects which have a physical presence should be of type Object.
 */
class Displayable : public ListItem {
	public:
				Displayable( DisplayableType );
				virtual ~Displayable();

				// Update item positioning and other data.
				virtual void Update( int );

				// Draw the item to the screen.
				//
				// Textures are enabled, so you need to bind
				// a null texture if you don't want any textures.
				virtual void Draw();

				// Apply an acceleration to the item.
				void accel( const vec3 & );

				// Apply a torque to the item.
				void torque( const vec3 & );

				// The maximum length of the item along any plane at any angle.
				// This needs to be updated if the object ever changes size.
				// The size is used to determine the sphere-boundary for collision detection.
				void setSize( float s ) { size = s; }

				// Statically set the position of the item.
				// You don't normally do this.
				void setPos( const vec3 &p ) { pos = p; }

				// Statically set the velocity of the item.
				// You don't normally do this.
				void setVel( const vec3 &v ) { vel = v; }

				// Statically set the rotational position of the item.
				// You don't normally do this.
				void setRot( const vec3 &r ) { rot = r; }

				// Statically set the angular momentum of the item.
				// You don't normally do this.
				void setTorque( const vec3 &t ) { torq = t; }

				void setMass( float m ) { mass = m; }

				void setType( DisplayableType t ) { type = t; }

				virtual float getSize() { return size; }
				virtual vec3 getPos() { return pos; }
				virtual vec3 getVel() { return vel; }
				virtual vec3 getRot() { return rot; }
				virtual vec3 getTorque() { return torq; }
				virtual unsigned int getAge() { return age; }
				virtual float getMass() { return mass; }
				virtual int getType() { return type; }


	protected:
				// RGBA Color of the item.
				float color[4];

				// Position (X, Y, Z) at center of item (meters).
				vec3 pos;

				// Velocity (X, Y, Z)
				// Number of meters to move in each direction each frame.
				// Remember that the game runs at 50 FPS, regardless of what the
				// user's screen is actually displaying.
				vec3 vel;

				// Rotation (Degrees)
				// The angular position of the item (counter-clockwise).
				vec3 rot;

				// Torque (Degrees)
				// The angular velocity of the item (counter-clockwise).
				vec3 torq;

				// Maximum size of item.
				float size;

				// Age of item in frames
				unsigned int age;

				// Mass of the item (kilograms).
				float mass;

				// Type of item.
				int type;


	private:
				Displayable( const Displayable &displayable );
				const Displayable & operator= ( const Displayable &displayable );
};


#endif /*DISPLAYABLE_H_*/
