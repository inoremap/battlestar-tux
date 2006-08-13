/* GUI.cpp
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


#include <SDL.h>

#include "GUI.h"
#include "Primitives/Widget.h"

GUI::GUI( int w, int h ) {
	screenW = w;
	screenH = h;

	// Load normal font.
	char* normalFontFile = "data/fonts/forgottenfuturist.ttf";
	normalFont = new FTGLTextureFont( normalFontFile );
	if( normalFont->Error() )
		printf( "Unable to open font file: %s\n", normalFontFile );
	normalFont->FaceSize( 30 );
	normalFont->CharMap( ft_encoding_unicode );
	if( normalFont->Error() )
		printf( "Unable to set font parameters: %s\n", normalFontFile );

	// Load italic font.
	char* italicFontFile = "data/fonts/forgottenfuturist_i.ttf";
	italicFont = new FTGLTextureFont( italicFontFile );
	if( italicFont->Error() )
		printf( "Unable to open font file: %s\n", italicFontFile );
	italicFont->FaceSize( 30 );
	italicFont->CharMap( ft_encoding_unicode );
	if( italicFont->Error() )
		printf( "Unable to set font parameters: %s\n", italicFontFile );

	// Load bold font.
	char* boldFontFile = "data/fonts/forgottenfuturist_b.ttf";
	boldFont = new FTGLTextureFont( boldFontFile );
	if( boldFont->Error() )
		printf( "Unable to open font file: %s\n", boldFontFile );
	boldFont->FaceSize( 30 );
	boldFont->CharMap( ft_encoding_unicode );
	if( boldFont->Error() )
		printf( "Unable to set font parameters: %s\n", boldFontFile );
}


GUI::~GUI() {
	Widget* cur = (Widget*) rootObj;
	Widget* next = 0;

	while( cur ) {
		next = (Widget*) cur->getNext();
		delete cur;
		cur = next;
	}

	delete normalFont;
	delete italicFont;
	delete boldFont;
}


void GUI::Draw() {
	// Use orthographic projection for GUI
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
		glLoadIdentity();
		glOrtho( 0, screenW, 0, screenH, -10, 10 );

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
			// Begin drawing GUI elements.
			Widget* cur = (Widget*) rootObj;

			while( cur ) {
				glLoadIdentity();
				cur->Draw();
				cur = (Widget*) cur->getNext();
			}
			// Stop drawing GUI elements.

			// Return projection and modelview matrices to their in-game states.
		glPopMatrix();

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
}


void GUI::Update() {
	int x;
	int y;
	int state;
	state = SDL_GetMouseState( &x, &y );
	Widget* cur = (Widget*) rootObj;

	// Re-arrange y coordinate.
	y = screenH - y;

	while( cur ) {
		cur->Update( x, y, state );
		cur = (Widget*) cur->getNext();
	}
}


FTFont* GUI::getFont() { return normalFont; }
FTFont* GUI::getItalicFont() { return italicFont; }
FTFont* GUI::getBoldFont() { return boldFont; }
