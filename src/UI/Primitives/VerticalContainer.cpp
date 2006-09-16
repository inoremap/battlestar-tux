/* VerticalContainer.cpp
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


#include <math.h>

#include "VerticalContainer.h"
#include "Widget.h"

VerticalContainer::VerticalContainer( GUI* g, bool resize, W_HAlignment h, W_VAlignment v ) : Container( g, resize, h, v, false ) {
	preferredSize[0] = size[0] = 10;
	preferredSize[1] = size[1] = 10;
}

VerticalContainer::~VerticalContainer() {}


void VerticalContainer::ReevaluateElements() {
	preferredSize[0] = 0;
	preferredSize[1] = - C_WIDGET_PAD;
	int yOffset = 0;
	int yCorrection = 0;
	int* wSize;
	int numWidgets = 0;

	Widget* cur = (Widget*) rootObj;
	// Loop through widgets - determining container size.
	while( cur ) {
		wSize = cur->getPreferredSize();
		++numWidgets;

		if( preferredSize[0] < wSize[0] )
			preferredSize[0] = wSize[0];
		preferredSize[1] += wSize[1] + C_WIDGET_PAD;

		cur = (Widget*) cur->getNext();
	}

	// Enlarge container, if it is currently too small.
	if( size[0] < preferredSize[0] )
		size[0] = preferredSize[0];
	if( size[1] < preferredSize[1] )
		size[1] = preferredSize[1];

	// Set position of container.
	setContainerPos();

	cur = (Widget*) rootObj;
	// Loop through widgets - setting size and position.
	for( int i = 0; i < numWidgets && cur; ++i ) {
		wSize = cur->getPreferredSize();

		if( resizeWidgets ) {
			int widgetSpacing = (int) floorf( (size[1] - preferredSize[1] - yCorrection)/(numWidgets - i) );
			cur->setSize( size[0], wSize[1] + widgetSpacing );

			cur->setPos( pos[0], yOffset + pos[1] );

			yOffset += C_WIDGET_PAD + cur->getSize()[1];
			yCorrection += cur->getSize()[1] - wSize[1];
		}
		else {
			// Horizontally align widgets.
			switch( hAlign ) {
				case HORIZ_LEFT:
				default:
					cur->setPos( pos[0], cur->getPos()[1] );
					break;

				case HORIZ_CENTER:
					cur->setPos( pos[0] + (size[0] - wSize[0])/2 , cur->getPos()[1] );
					break;

				case HORIZ_RIGHT:
					cur->setPos( pos[0] + size[0] - wSize[0], cur->getPos()[1] );
					break;
			}

			// Vertically align widgets.
			switch( vAlign ) {
				case VERTI_TOP:
					cur->setPos( cur->getPos()[0], yOffset + pos[1] + size[1] - preferredSize[1] );
					break;

				case VERTI_CENTER:
					cur->setPos( cur->getPos()[0], yOffset + pos[1] + (size[1] - preferredSize[1])/2 );
					break;

				case VERTI_BOTTOM:
				default: 
					cur->setPos( cur->getPos()[0], yOffset + pos[1] );
					break;
			}

			yOffset += C_WIDGET_PAD + wSize[1];
		}

		cur = (Widget*) cur->getNext();
	}
}
