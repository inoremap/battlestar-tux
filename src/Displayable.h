/* Displayable.h
 *
 * Copyright 2005-2006 Eliot Eshelman
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
#include "Structures/ListItem.h"


enum DisplayableType {
	GROUND		=	0x0001,				// Ground segment
	FIGHTER		=	0x0002,				// Aircraft
	SHIELD		=	0x0004,				// Aircraft shield
	AMMO		=	0x0008,				// Weapon ammo
	HEROS_AMMO	=	0x0010 | 0x0008,	// Hero's ammo
	ENEMY_AMMO	=	0x0020 | 0x0008,	// Enemies' ammo
	EFFECT		=	0x0040				// Special effect - not a real object
};


/* Any item which appears on the screen is Displayable. */
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

				void setSize( float w, float h );

				// Some (all?) objects have a set Z position.
				// In this case, just set X and Y positions.
				void setPos( float x, float y );
				void setPos( float x, float y, float z );

				void setVel( float x, float y, float z );

				void setRot( float r );
				void setTorque( float t );

				void setColor( float r, float g, float b, float a );

				void incrAge();

				void setType( int t );

				void setCircular( bool circle );

				void setPolygon( int numPoints, float points[][2] );

				void setStayOnScreen( bool stay );

				float* getSize();
				float* getPos();
				float* getVel();
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
				float size[2];

				// Position (X, Y, Z) at center of object.
				float pos[3];

				// Velocity (X, Y, Z)
				// Number of units to move in each direction each frame.
				// Remember that the game runs at 50 FPS, regardless of what the
				// user's screen is actually displaying.
				float vel[3];

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
