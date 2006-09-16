/* Widget.cpp
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


#include <SDL.h>

#include "Widget.h"

Widget::Widget( GUI* gui, W_HAlignment h, W_VAlignment v ) {
	font = gui->getFont();

	pos[0] = 0;
	pos[1] = 0;
	preferredSize[0] = size[0] = 10;
	preferredSize[1] = size[1] = 10;

	hover = false;
	clicked = false;

	secondDraw = false;

	hAlign = h;
	vAlign = v;
}


Widget::~Widget() {}


void Widget::Update( int x, int y, int state ) {
	// Mouse wasn't clicked previously.
	if( !clicked ) {
		// Mouse is over widget.
		if( pos[0] < x && x < (pos[0] + size[0]) && pos[1] < y && y < (pos[1] + size[1]) ) {
			// Mouse is clicked.
			if( state & SDL_BUTTON(1) ) {
				// Mouse was clicked while over widget.
				if( hover )
					clicked = true;
			}
			// Mouse isn't clicked.
			else
				hover = true;
		}
		// Mouse is outside of widget.
		else
			hover = false;
	}
	// Mouse was clicked previously.
	else {
		// Mouse is over widget.
		if( pos[0] < x && x < (pos[0] + size[0]) && pos[1] < y && y < (pos[1] + size[1]) ) {
			// Mouse was released.
			if( ! state & SDL_BUTTON(1) ) {
				// Mouse was released while over widget.
				if( hover ) {
					clicked = false;

					//// WIDGET CLICKED ////
					ClickEvent();
					//// WIDGET CLICKED ////
				}
				// Mouse was released while outside widget.
				else
					clicked = false;
			}

			hover = true;
		}
		// Mouse is outside of widget.
		else {
			// Mouse was released.
			if( ! state & SDL_BUTTON(1) )
				clicked = false;

			hover = false;
		}
	}

	if( hover ) {
		//// HOVER OVER WIDGET ////
		HoverEvent();
		//// HOVER OVER WIDGET ////
	}
}


void Widget::setFont( FTFont* f ) { font = f; }


void Widget::setPos( int p[2] ) {
	pos[0] = p[0];
	pos[1] = p[1];
}

void Widget::setPos( int x, int y ) {
	pos[0] = x;
	pos[1] = y;
}

int* Widget::getPos() { return pos; }


int* Widget::getPreferredSize() { return preferredSize; }


void Widget::setSize( int s[2] ) {
	size[0] = s[0];
	size[1] = s[1];
}

void Widget::setSize( int w, int h ) {
	size[0] = w;
	size[1] = h;
}

int* Widget::getSize() { return size; }

void Widget::setSecondDraw( bool d ) { secondDraw = d; }

bool Widget::getSecondDraw() { return secondDraw; }
