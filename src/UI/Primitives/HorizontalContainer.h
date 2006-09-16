/* HorizontalContainer.h
 *
 * Copyright 2006 Eliot Eshelman
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


#ifndef HORIZONTALCONTAINER_H_
#define HORIZONTALCONTAINER_H_

#include "Container.h"

/* A row of horizontal widgets. */
class HorizontalContainer : public Container {
	public:
				HorizontalContainer( GUI* g, bool resize, W_HAlignment h, W_VAlignment v );
				~HorizontalContainer();

	protected:
				// Re-Align elements in container.
				void ReevaluateElements();

	private:
				HorizontalContainer( const HorizontalContainer &hc );
				const HorizontalContainer & operator= ( const HorizontalContainer &hc );
};

#endif /*HORIZONTALCONTAINER_H_*/
