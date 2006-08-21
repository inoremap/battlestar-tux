/* HorizontalPane.cpp
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


#include "HorizontalPane.h"
#include "Widget.h"

HorizontalPane::HorizontalPane( GUI* g, bool resize, W_Alignment v ) : Container( g, false ) {
	resizeWidgets = resize;

	vAlign = v;

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

	// Draw all elements in pane.
	Widget* cur = (Widget*) rootObj;

	while( cur ) {
		glLoadIdentity();
		cur->Draw();
		cur = (Widget*) cur->getNext();
	}
}


void HorizontalPane::Update( int x, int y, int state ) {
	// Update all elements in pane.
	Widget* cur = (Widget*) rootObj;

	while( cur ) {
		cur->Update( x, y, state );
		cur = (Widget*) cur->getNext();
	}
}


void HorizontalPane::ReevaluateElements() {
	preferredSize[0] = - C_WIDGET_PAD;
	preferredSize[1] = 0;
	int offset[2] = { 0, 0 };
	int maxWidgetHeight = 0;
	int paneHeight = 0;
	int* wSize;

	Widget* cur = (Widget*) rootObj;
	// Loop through widgets - determining pane size.
	while( cur ) {
		wSize = cur->getPreferredSize();

		if( maxWidgetHeight < wSize[1] ) {
			maxWidgetHeight = wSize[1];
			preferredSize[1] = wSize[1];
		}
		preferredSize[0] += wSize[0] + C_WIDGET_PAD;

		cur = (Widget*) cur->getNext();
	}

	paneHeight = preferredSize[1];
	preferredSize[0] += C_HORIZ_PAD * 2;
	preferredSize[1] += C_VERTI_PAD * 2;
	offset[0] = preferredSize[0] - C_HORIZ_PAD;
	offset[1] = C_VERTI_PAD;

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
				cur->setPos( offset[0] + pos[0], offset[1] + pos[1] + paneHeight - cur->getSize()[1] );
				break;

			case VERTI_CENTER:
				cur->setPos( offset[0] + pos[0], offset[1] + pos[1] + (paneHeight - cur->getSize()[1])/2 );
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
