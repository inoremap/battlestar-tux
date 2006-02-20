/* GroundSegment.h
 *
 * Copyright 2005 Eliot Eshelman
 * eliot@6by9.net
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


#ifndef GROUNDSEGMENT_H_
#define GROUNDSEGMENT_H_

#include "SDL_opengl.h"

#include "Displayable.h"
#include "Game.h"
#include "Ground.h"

/* One portion of the entire ground. */
class GroundSegment : public Displayable {
	public:
				GroundSegment( GroundType type, Ground* gr, Game* ga );

				void Draw();

	private:
				GroundSegment( const GroundSegment &segment );
				const GroundSegment & operator= ( const GroundSegment &segment );

				// Particular variation of ground texturing.
				GroundType groundType;

				// Parent Ground object
				Ground* ground;

				// Segment texture
				GLuint texture;
};


#endif /*GROUNDSEGMENT_H_*/
