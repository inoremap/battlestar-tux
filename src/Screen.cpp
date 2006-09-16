/* Screen.cpp
 *
 * Copyright 2005-2006 Eliot Eshelman
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
#include <SDL_opengl.h>
#include <iostream>

#include "Screen.h"
#include "Config.h"

Screen::Screen( Game* g ) {
	screen = NULL;

	// Try to initialize SDL. If it fails, then give up.
	if( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
		std::cout << "Can't initialize SDL: " << SDL_GetError() << "\n";
		return;
	}

	// Safety first. If the program exits in an unexpected
	// way the atexit() call should ensure that SDL will be
	// shut down properly and the screen returned to a
	// reasonable state.
	atexit( SDL_Quit );

	// Request 8 bits per channel and double buffering.
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE,     8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE,   8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE,    8 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	// Open a window 1024x768.
	// For fullscreen, use 'SDL_OPENGL | SDL_FULLSCREEN'
	width = 1024;
	height = 768;
	fovy = 110;
	screen = SDL_SetVideoMode( width, height, 0, SDL_OPENGL );

	if( g->getConfig()->getGrabInput() ) {
		// Grab the Keyboard and Mouse
		SDL_WM_GrabInput( SDL_GRAB_ON );

		// Don't actually show the cursor
		SDL_ShowCursor( SDL_DISABLE );
	}

	if( g->getConfig()->getWireframe() ) {
		// Draw all polygons in wireframe mode.
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}

	// If the window couldn't be created at all, we're done.
	if( screen == NULL )
	{
		std::cout << "Can't create SDL screen: " << SDL_GetError() << "\n";
		return;
	}

	// Setup window at current size.
	Resize( screen->w, screen->h );

	// The background color is black.
	glClearColor( 0.0, 0.0, 0.0, 1.0 );

	// Points and lines 1 pixel wide.
	glPointSize( 1.0 );
	glLineWidth( 1.0 );

	// High quality perspective calculations.
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	// High quality point smoothing.
	glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
	glShadeModel( GL_SMOOTH );

	// Enable 2D textures.
	glEnable( GL_TEXTURE_2D );

	// Don't need normalization.
	glDisable( GL_NORMALIZE );

	// Enable blending.
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glDisable( GL_ALPHA_TEST );

	SDL_WM_SetCaption( "Battlestar T.U.X.", "Battlestar T.U.X." );
}


bool Screen::isNull() {
	if( screen == NULL )
		return true;
	else
		return false;
}


void Screen::Resize( int w, int h ) {
	width = w;
	height = h;

	// Configure the OpenGL screen for a 2D scrolling engine.
	// Objects are drawn in 3D, with the z-axis perpendicular to the viewing plane.
	//
	// The coordinate system is configured so that ( 0, 0, 0 ) is at the center of the screen.
	glViewport( 0, 0, width, height );
	setFOVY( fovy );
}


void Screen::setFOVY( float fov ) {
	fovy = fov;

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective( fovy, (float) width/height, 1, 30 );
	glMatrixMode( GL_MODELVIEW );
}


int Screen::getWidth() { return width; }
int Screen::getHeight() { return height; }
float Screen::getFOVY() { return fovy; }
