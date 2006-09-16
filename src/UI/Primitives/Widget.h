/* Widget.h
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


#ifndef WIDGET_H_
#define WIDGET_H_

#include "../../Structures/ListItem.h"
#include "../GUI.h"

/* Default color/alpha for widgets. */
static const float W_BG[4] = { 0.0, 0.0, 0.0, 0.6 };
static const float W_FG[4] = { 0.396, 0.607, 0.831, 0.9 };
static const float W_EDGE[4] = { 0.396, 0.607, 0.831, 0.9 };
static const float W_BG_HOVER[4] = { 0.396, 0.607, 0.831, 0.9 };
static const float W_FG_HOVER[4] = { 0.0, 0.0, 0.0, 1.0 };
static const float W_EDGE_HOVER[4] = { 0.396, 0.607, 0.831, 0.9 };
static const float W_BG_CLICKED[4] = { 0.282, 0.431, 0.588, 0.9 };
static const float W_FG_CLICKED[4] = { 0.0, 0.0, 0.0, 1.0 };
static const float W_EDGE_CLICKED[4] = { 0.396, 0.607, 0.831, 0.9 };

/* Default padding for widgets. */
static const int W_EDGE_OFFSET = 6;
static const int W_HORIZ_PAD = 6;
static const int W_VERTI_PAD = 2;

// Widget Alignments - Horizontal and Vertical
enum W_HAlignment {
	HORIZ_RIGHT,
	HORIZ_CENTER,
	HORIZ_LEFT
};
enum W_VAlignment {
	VERTI_TOP,
	VERTI_CENTER,
	VERTI_BOTTOM
};

/* Basic UI Widget. */
class Widget : public ListItem {
	public:
				Widget( GUI* gui, W_HAlignment h, W_VAlignment v );
				virtual ~Widget();

				virtual void Draw() {}

				// Second draw function - usually for lighting reasons.
				virtual void SecondDraw() {}

				// Update widget given the (x, y) position of the mouse cursor
				// and the state of the mouse buttons.
				virtual void Update( int x, int y, int state );

				// The mouse is hovering over the widget.
				virtual void HoverEvent() {}

				// The widget was clicked.
				virtual void ClickEvent() {}

				void setFont( FTFont* f );

				virtual void setPos( int p[2] );
				virtual void setPos( int x, int y );
				int* getPos();

				int* getPreferredSize();

				virtual void setSize( int s[2] );
				virtual void setSize( int w, int h );
				int* getSize();

				void setSecondDraw( bool d );
				bool getSecondDraw();

	protected:
				FTFont* font;

				// Position of widget.
				int pos[2];

				// Preferred (minimum) size of widget.
				int preferredSize[2];

				// Actual drawn size of widget.
				int size[2];

				// Mouse cursor is over widget.
				bool hover;

				// Mouse cursor is over widget with button down.
				bool clicked;

				// Needs to be drawn in two sections - usually for lighting reasons.
				bool secondDraw;

				// Horizontal alignment of widget's contents (left, center, right).
				W_HAlignment hAlign; 

				// Vertical alignment of widget's contents (top, center, bottom).
				W_VAlignment vAlign;

	private:
				Widget( const Widget &widget );
				const Widget & operator= ( const Widget &widget );
};


#endif /*WIDGET_H_*/
