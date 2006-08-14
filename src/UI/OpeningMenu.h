/* OpeningMenu.h
 *
 * Copyright 2006 Eliot Eshelman
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


#ifndef OPENINGMENU_H_
#define OPENINGMENU_H_

#include "GUI.h"
#include "Primitives/ButtonClickEvent.h"
#include "Primitives/EventListener.h"

/* First menu drawn - game first starting. */
class OpeningMenu : public GUI, EventListener {
	public:
				OpeningMenu( int w, int h );
				~OpeningMenu();

				// Create all widgets and bind listeners.
				void CreateWidgets();

				// Button click event.
				void EventGenerated( Event* e );

	private:
				OpeningMenu( const OpeningMenu &menu );
				const OpeningMenu & operator= ( const OpeningMenu &menu );
};

#endif /*OPENINGMENU_H_*/
