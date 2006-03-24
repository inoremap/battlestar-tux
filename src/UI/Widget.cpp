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
	font = gui->getBoldFont();
}


Widget::~Widget() {}


void Widget::Draw() {
	float llx = 0.0;
	float lly = 0.0;
	float llz = 0.0;
	float urx = 0.0;
	float ury = 0.0;
	float urz = 0.0;
	float descender = font->Descender();
	char* string = "Test";
	font->BBox( string, llx, lly, llz, urx, ury, urz );

	glPushMatrix();
		glTranslatef( 10.0, -descender, 0.0 );
		glColor4f( 1.0, 1.0, 1.0, 1.0 );
		glBindTexture( GL_TEXTURE_2D, 0 );
		font->Render( string );
	glPopMatrix();

	glTranslatef( 10.0, -descender, 0.0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glBegin( GL_LINE_LOOP );
		glVertex3f( llx - 8 + 6, lly - 3, 0.0 );
		glVertex3f( urx + 8, lly - 3, 0.0 );
		glVertex3f( urx + 8, ury + 3 - 6, 0.0 );
		glVertex3f( urx + 8 - 6, ury + 3, 0.0 );
		glVertex3f( llx - 8, ury + 3, 0.0 );
		glVertex3f( llx - 8, lly - 3 + 6, 0.0 );
	glEnd();
}


void Widget::Update( int x, int y, int state ) {
}


void Widget::setSize( float s[2] ) {
	size[0] = s[0];
	size[1] = s[1];
}
