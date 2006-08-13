/* HorizontalContainer.cpp
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


#include "HorizontalContainer.h"
#include "Widget.h"

HorizontalContainer::HorizontalContainer( GUI* g, bool resize, W_Alignment v ) : Container( g ) {
	resizeWidgets = resize;

	vAlign = v;

	preferredSize[0] = size[0] = 50;
	preferredSize[1] = size[1] = 100;
}

HorizontalContainer::~HorizontalContainer() {}


void HorizontalContainer::Draw() {
	// Draw all elements in container.
	Widget* cur = (Widget*) rootObj;

	while( cur ) {
		glLoadIdentity();
		cur->Draw();
		cur = (Widget*) cur->getNext();
	}
}


void HorizontalContainer::Update( int x, int y, int state ) {
	// Update all elements in container.
	Widget* cur = (Widget*) rootObj;

	while( cur ) {
		cur->Update( x, y, state );
		cur = (Widget*) cur->getNext();
	}
}


void HorizontalContainer::ReevaluateElements() {
	preferredSize[0] = - C_WIDGET_PAD;
	preferredSize[1] = 0;
	int offset[2] = { 0, 0 };
	int maxWidgetHeight = 0;
	int containerHeight = 0;
	int* wSize;

	Widget* cur = (Widget*) rootObj;
	// Loop through widgets - determining container size.
	while( cur ) {
		wSize = cur->getPreferredSize();

		if( maxWidgetHeight < wSize[1] ) {
			maxWidgetHeight = wSize[1];
			preferredSize[1] = wSize[1];
		}
		preferredSize[0] += wSize[0] + C_WIDGET_PAD;

		cur = (Widget*) cur->getNext();
	}

	containerHeight = preferredSize[1];
	offset[0] = preferredSize[0];
	offset[1] = 0;

	// Set size of container.
	if( size[0] < preferredSize[0] )
		size[0] = preferredSize[0];
	if( size[1] < preferredSize[1] )
		size[1] = preferredSize[1];

	// Set position of container.
	setContainerPos();

	cur = (Widget*) rootObj;
	// Loop through widgets - setting size and position.
	while( cur ) {
		wSize = cur->getPreferredSize();
		offset[0] -= wSize[0];

		// Vertically align widgets.
		switch( vAlign ) {
			case VERTI_TOP:
				cur->setPos( offset[0] + pos[0], offset[1] + pos[1] + containerHeight - cur->getSize()[1] );
				break;

			case VERTI_CENTER:
				cur->setPos( offset[0] + pos[0], offset[1] + pos[1] + (containerHeight - cur->getSize()[1])/2 );
				break;

			case VERTI_BOTTOM:
			default: 
				cur->setPos( offset[0] + pos[0], offset[1] + pos[1] );
				break;
		}

		if( resizeWidgets )
			cur->setSize( cur->getSize()[0], maxWidgetHeight );

		cur = (Widget*) cur->getNext();
		offset[0] -= C_WIDGET_PAD;
	}
}
