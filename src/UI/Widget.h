/* Widget.h
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


#ifndef WIDGET_H_
#define WIDGET_H_

#include "../Structures/ListItem.h"
#include "GUI.h"

/* Basic UI Widget. */
class Widget : public ListItem {
	public:
				Widget( GUI* gui );
				virtual ~Widget();

				virtual void Draw();

				// Update widget given the (x, y) position of the mouse cursor
				// and the state of the mouse buttons.
				virtual void Update( int x, int y, int state );

				virtual void setSize( float s[2] );

	protected:
				FTFont* font;

				// Size of widget.
				float size[2];

				// Mouse cursor is over widget.
				bool hover;

				// Mouse cursor is over widget with button down.
				bool clicked;

	private:
				Widget( const Widget &widget );
				const Widget & operator= ( const Widget &widget );
};


#endif /*WIDGET_H_*/
