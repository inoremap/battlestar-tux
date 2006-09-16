/* HorizontalPane.cpp
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

#include "HorizontalPane.h"
#include "Widget.h"

HorizontalPane::HorizontalPane( GUI* g, bool resize, W_HAlignment h, W_VAlignment v ) : Container( g, resize, h, v, false ) {
	preferredSize[0] = size[0] = 10;
	preferredSize[1] = size[1] = 10;
}

HorizontalPane::~HorizontalPane() {}


void HorizontalPane::Draw() {
	// Draw pane.
	// Translate to pane position.
	glTranslatef( pos[0], pos[1], 0.0 );

	// Draw background.
	glColor4fv( C_BG );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glBegin( GL_POLYGON );
		glVertex3f( 0.0, 0.0, 0.0 );
		glVertex3f( size[0] - C_EDGE_OFFSET, 0.0, 0.0 );
		glVertex3f( size[0], C_EDGE_OFFSET, 0.0 );
		glVertex3f( size[0], size[1], 0.0 );
		glVertex3f( C_EDGE_OFFSET, size[1], 0.0 );
		glVertex3f( 0.0, size[1] - C_EDGE_OFFSET, 0.0 );
	glEnd();

	// Draw edge.
	glColor4fv( C_EDGE );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glBegin( GL_LINE_LOOP );
		glVertex3f( 0.0, 0.0, 0.0 );
		glVertex3f( size[0] - C_EDGE_OFFSET, 0.0, 0.0 );
		glVertex3f( size[0], C_EDGE_OFFSET, 0.0 );
		glVertex3f( size[0], size[1], 0.0 );
		glVertex3f( C_EDGE_OFFSET, size[1], 0.0 );
		glVertex3f( 0.0, size[1] - C_EDGE_OFFSET, 0.0 );
	glEnd();

	Container::Draw();
}


void HorizontalPane::ReevaluateElements() {
	preferredSize[0] = - C_WIDGET_PAD;
	preferredSize[1] = 0;
	int xOffset = 0;
	int xCorrection = 0;
	int* wSize;
	int numWidgets = 0;

	Widget* cur = (Widget*) rootObj;
	// Loop through widgets - determining container size.
	while( cur ) {
		wSize = cur->getPreferredSize();
		++numWidgets;

		if( preferredSize[1] < wSize[1] )
			preferredSize[1] = wSize[1];
		preferredSize[0] += wSize[0] + C_WIDGET_PAD;

		cur = (Widget*) cur->getNext();
	}
	preferredSize[0] += C_HORIZ_PAD * 2;
	preferredSize[1] += C_VERTI_PAD * 2;

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
			int widgetSpacing = (int) floorf( (size[0] - preferredSize[0] - xCorrection)/(numWidgets - i) );
			cur->setSize( wSize[0] + widgetSpacing, size[1] - C_VERTI_PAD * 2 );

			cur->setPos( xOffset + pos[0] + C_HORIZ_PAD, pos[1] + C_VERTI_PAD );

			xOffset += C_WIDGET_PAD + widgetSpacing + cur->getSize()[0];
			xCorrection += cur->getSize()[0] - wSize[0];
		}
		else {
			// Horizontally align widgets.
			switch( hAlign ) {
				case HORIZ_LEFT:
				default:
					cur->setPos( xOffset + pos[0] + C_HORIZ_PAD, cur->getPos()[1] );
					break;

				case HORIZ_CENTER:
					cur->setPos( xOffset + pos[0] + C_HORIZ_PAD + (size[0] - preferredSize[0])/2 , cur->getPos()[1] );
					break;

				case HORIZ_RIGHT:
					cur->setPos( xOffset + pos[0] + C_HORIZ_PAD + size[0] - preferredSize[0], cur->getPos()[1] );
					break;
			}

			// Vertically align widgets.
			switch( vAlign ) {
				case VERTI_TOP:
					cur->setPos( cur->getPos()[0], pos[1] - C_VERTI_PAD + size[1] - wSize[1] );
					break;

				case VERTI_CENTER:
					cur->setPos( cur->getPos()[0], pos[1] + (size[1] - wSize[1])/2 );
					break;

				case VERTI_BOTTOM:
				default: 
					cur->setPos( cur->getPos()[0], pos[1] + C_VERTI_PAD );
					break;
			}

			xOffset += C_WIDGET_PAD + wSize[0];
		}

		cur = (Widget*) cur->getNext();
	}
}
