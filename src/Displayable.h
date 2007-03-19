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

#include "Game.h"
#include "ListItem.h"
#include "Vector.h"

enum DisplayableType {
	GROUND		=	0x0001,				// Ground segment
	EFFECT		=	0x0002				// Special effect - not a real object
};


/* Any item which appears on the screen is Displayable.
 * Note that objects which have a physical presence should be of type Object.
 */
class Displayable : public ListItem {
	public:
				Displayable( DisplayableType t, Game* g );
				virtual ~Displayable();

				// Move object to its new position and update other elements.
				virtual void Update();

				// Draw the object to the screen.
				//
				// Textures are enabled, so you need to bind
				// a null texture if you don't want any textures.
				virtual void Draw();

				void setSize( vec2 & );

				// Some (all?) objects have a set Z position.
				// In this case, just set X and Y positions.
				void setPos( vec2 & );
				void setPos( vec3 & );

				void setVel( vec3 & );

				void setRot( float r );
				void setTorque( float t );

				void setColor( float r, float g, float b, float a );

				void incrAge();

				void setType( int t );

				void setCircular( bool circle );

				void setPolygon( int numPoints, float points[][2] );

				void setStayOnScreen( bool stay );

				vec2 & getSize();
				vec3 & getPos();
				vec3 & getVel();
				float getRot();
				float getTorque();
				float* getColor();
				unsigned int getAge();
				int getType();
				bool getCircular();
				float** getPolygon();
				int getNumPolygonPoints();
				bool getStayOnScreen();

	protected:
				// Size (width and height) of object.
				vec2 size;

				// Position (X, Y, Z) at center of object.
				vec3 pos;

				// Velocity (X, Y, Z)
				// Number of units to move in each direction each frame.
				// Remember that the game runs at 50 FPS, regardless of what the
				// user's screen is actually displaying.
				vec3 vel;

				// Rotation (Degrees)
				// The angular position of the object (counter-clockwise).
				float rot;

				// Torque (Degrees)
				// The rotational velocity of the object (counter-clockwise).
				float torque;

				// Color (Red, Green, Blue, Alpha)
				float color[4];

				// Age of item in frames
				unsigned int age;

				// Type of displayable object.
				int type;

				// Is the object a circle or a polygon?
				// Needed for collision detection.
				bool circular;

				// If the object is a polygon, the points (X, Y)
				// of the polygon must be defined. Points must be
				// specified in counter-clockwise order.
				// These points will be offsets from the object's current position.
				float** polygon;
				int numPolygonPoints;

				// Must the object remain on the screen at all times?
				bool stayOnScreen;

				Game* game;

	private:
				Displayable( const Displayable &displayable );
				const Displayable & operator= ( const Displayable &displayable );
};


#endif /*DISPLAYABLE_H_*/
