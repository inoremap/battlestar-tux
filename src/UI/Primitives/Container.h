/* Container.h
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


#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "../../Structures/List.h"
#include "../../Structures/ListItem.h"
#include "Widget.h"

/* Default color/alpha for containers. */
static const float C_BG[4] = { 0.0, 0.0, 0.0, 0.4 };
static const float C_FG[4] = { 0.396, 0.607, 0.831, 0.9 };
static const float C_EDGE[4] = { 0.396, 0.607, 0.831, 0.9 };

/* Default padding for containers. */
static const int C_EDGE_OFFSET = 20;
static const int C_HORIZ_PAD = 15;
static const int C_VERTI_PAD = 15;
static const int C_WIDGET_PAD = 10;

/* Object for containing and placing sets of widgets. */
class Container : protected List, public Widget {
	public:
				Container( GUI* g ) : Widget( g ) { gui = g; }
				virtual ~Container() {}

				virtual void AddWidget( Widget* w ) {
					addObject(w);
					ReevaluateElements();
				}

				virtual void RemWidget( Widget* w ) {
					remObject(w);
					ReevaluateElements();
				}

				void setPos( int p[2] ) {
					Widget::setPos( p );
					ReevaluateElements();
				}

				void setPos( int x, int y ) {
					Widget::setPos( x, y );
					ReevaluateElements();
				}

				void setSize( int s[2] ) {
					Widget::setSize( s );
					ReevaluateElements();
				}

				void setSize( int w, int h ) {
					Widget::setSize( w, h );
					ReevaluateElements();
				}

	protected:
				// Re-align elements in container.
				virtual void ReevaluateElements() {}

				// GUI which contains the container.
				GUI* gui;

	private:
				Container( const Container &c );
				const Container & operator= ( const Container &c );
};


#endif /*CONTAINER_H_*/
