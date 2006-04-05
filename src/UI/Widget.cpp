/* Widget.cpp
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


#include "Widget.h"

Widget::Widget( GUI* gui ) {
	font = gui->getFont();

	pos[0] = 0;
	pos[1] = 0;
	preferredSize[0] = size[0] = 10;
	preferredSize[1] = size[1] = 10;

	hover = false;
	clicked = false;
}


Widget::~Widget() {}


void Widget::Draw() {}


void Widget::Update( int x, int y, int state ) {}


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
