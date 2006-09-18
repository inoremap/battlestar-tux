/* GUI.cpp
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
#include <iostream>
#include <string>

#include "GUI.h"
#include "Widget.h"

GUI::GUI( int w, int h, MainMenu* menu ) {
	screenW = w;
	screenH = h;

	normalFont = menu->getFont();
	italicFont = menu->getItalicFont();
	boldFont = menu->getBoldFont();
}


GUI::~GUI() {
	Widget* cur = (Widget*) rootObj;
	Widget* next = 0;

	while( cur ) {
		next = (Widget*) cur->getNext();
		delete cur;
		cur = next;
	}
}


void GUI::CreateWidgets() {}


void GUI::beforeDraw() {
	// Use orthographic projection for GUI
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
		glLoadIdentity();
		glOrtho( 0, screenW, 0, screenH, -screenW, screenW );

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
}


void GUI::afterDraw() {
		// Return projection and modelview matrices to their in-game states.
		glPopMatrix();

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
}


void GUI::Draw() {
	beforeDraw();

	Widget* cur = (Widget*) rootObj;

	while( cur ) {
		glLoadIdentity();
		cur->Draw();
		cur = (Widget*) cur->getNext();
	}

	afterDraw();
}


void GUI::SecondDraw() {
	beforeDraw();

	Widget* cur = (Widget*) rootObj;

	while( cur ) {
		if( cur->getSecondDraw() ) {
			glLoadIdentity();
			cur->SecondDraw();
		}
		cur = (Widget*) cur->getNext();
	}

	afterDraw();
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


int GUI::getScreenWidth() { return screenW; }
int GUI::getScreenHeight() { return screenH; }

FTFont* GUI::getFont() { return normalFont; }
FTFont* GUI::getItalicFont() { return italicFont; }
FTFont* GUI::getBoldFont() { return boldFont; }
