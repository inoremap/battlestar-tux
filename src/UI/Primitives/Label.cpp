/* Label.cpp
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


#include "Label.h"

Label::Label( GUI* gui, char* s ) : Widget( gui ) {
	string = s;
}


Label::~Label() {}


void Label::Draw() {
	float descender = font->Descender();

	glTranslatef( 0.0, -descender, 0.0 );
	glColor4f( 1.0, 1.0, 1.0, 1.0 );
	glBindTexture( GL_TEXTURE_2D, 0 );
	font->Render( string );
}
