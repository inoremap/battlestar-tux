/* SpaceGroup.h
 *
 * Copyright 2007 Eliot Eshelman
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


#ifndef SPACEGROUP_H_
#define SPACEGROUP_H_

#include "List.h"


/* A SpaceGroup is a list of SpaceObjects.
 * Often times, this will be the planets in a solar system.  However, planets
 * also have a list of moons, and solar systems can contain other objects.
 */
class SpaceGroup : public List {
	public:
				SpaceGroup();
				virtual ~SpaceGroup();

				virtual void UpdateObjects();

				virtual void DrawObjects();

	private:
				SpaceGroup( const SpaceGroup & );
				const SpaceGroup & operator= ( const SpaceGroup & );
};


#endif /*SPACEGROUP_H_*/
