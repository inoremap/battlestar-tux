/* HUD.cpp
 *
 * Copyright 2005 Eliot Eshelman
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


#include "SDL.h"
#include "SDL_opengl.h"

#include "Fighter.h"
#include "GfxUtils.h"
#include "HUD.h"

HUD::HUD( Game* g ) {
	healthTexture = shieldsTexture = loadTexture( "data/gfx/hud_shields-64.png", GL_NEAREST );

	game = g;
}


HUD::~HUD() {
	if( healthTexture == shieldsTexture ) {
		glDeleteTextures( 1, &healthTexture );
		glDeleteTextures( 1, &shieldsTexture );
	}
	else
		glDeleteTextures( 1, &healthTexture );

	game = 0;
}


void HUD::Draw() {
	// Use orthographic projection for HUD
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
		glLoadIdentity();
		glOrtho( -10, 10, -10, 10, -10, 10 );

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
			// Begin drawing HUD elements.
			glLoadIdentity();

			// Draw HUD background.
			glBindTexture( GL_TEXTURE_2D, 0 );
			glBegin( GL_QUADS );
				glColor4f( 0.0, 0.0, 0.0, 0.3 );

				glVertex3f( -10, -10, -2.0 );
				glVertex3f( -8, -10, -2.0 );
				glVertex3f( -8, 10, -2.0 );
				glVertex3f( -10, 10, -2.0 );

				glVertex3f( 8, -10, -2.0 );
				glVertex3f( 10, -10, -2.0 );
				glVertex3f( 10, 10, -2.0 );
				glVertex3f( 8, 10, -2.0 );
			glEnd();

			// Armor/Shield Translation and Rotation
			glLoadIdentity();
			glTranslatef( -9.0, 0.0, 0.0 );
			glRotatef( 20, 1.0, 0.0, 0.0 );
			glRotatef( game->getGameFrame() % 360, 0.0, 1.0, 0.0 );

			// Draw armor status.
			float healthHeight = game->getFighter()->getHealth() / game->getFighter()->getHealthFull() * 10;
			float healthUnitHeight = game->getFighter()->getHealth() / game->getFighter()->getHealthFull();
			glBindTexture( GL_TEXTURE_2D, healthTexture );
			glBegin( GL_QUAD_STRIP );
				glColor4f( 0.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 0.0, 0.0 );
				glVertex3f( -0.6, 0.0, 0.6 );
				glColor4f( 1.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 0.0, healthUnitHeight );
				glVertex3f( -0.6, -healthHeight, 0.6 );
				glColor4f( 0.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 1.0, 0.0 );
				glVertex3f( 0.6, 0.0, 0.6 );
				glColor4f( 1.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 1.0, healthUnitHeight );
				glVertex3f( 0.6, -healthHeight, 0.6 );
				glColor4f( 0.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 2.0, 0.0 );
				glVertex3f( 0.6, 0.0, -0.6 );
				glColor4f( 1.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 2.0, healthUnitHeight );
				glVertex3f( 0.6, -healthHeight, -0.6 );
				glColor4f( 0.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 3.0, 0.0 );
				glVertex3f( -0.6, 0.0, -0.6 );
				glColor4f( 1.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 3.0, healthUnitHeight );
				glVertex3f( -0.6, -healthHeight, -0.6 );
				glColor4f( 0.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 4.0, 0.0 );
				glVertex3f( -0.6, 0.0, 0.6 );
				glColor4f( 1.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 4.0,  healthUnitHeight );
				glVertex3f( -0.6, -healthHeight, 0.6 );
			glEnd();

			// Draw shield status.
			float shieldHeight = game->getFighter()->getShields() / game->getFighter()->getShieldsFull() * 10;
			float shieldUnitHeight = game->getFighter()->getShields() / game->getFighter()->getShieldsFull();
			glBindTexture( GL_TEXTURE_2D, shieldsTexture );
			glBegin( GL_QUAD_STRIP );
				glColor4f( 0.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 0.0, 0.0 );
				glVertex3f( -0.6, 0.0, 0.6 );
				glColor4f( 0.0, 0.64, 1.0, 0.7 );
				glTexCoord2f( 0.0, shieldUnitHeight );
				glVertex3f( -0.6, shieldHeight, 0.6 );
				glColor4f( 0.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 1.0, 0.0 );
				glVertex3f( 0.6, 0.0, 0.6 );
				glColor4f( 0.0, 0.64, 1.0, 0.7 );
				glTexCoord2f( 1.0, shieldUnitHeight );
				glVertex3f( 0.6, shieldHeight, 0.6 );
				glColor4f( 0.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 2.0, 0.0 );
				glVertex3f( 0.6, 0.0, -0.6 );
				glColor4f( 0.0, 0.64, 1.0, 0.7 );
				glTexCoord2f( 2.0, shieldUnitHeight );
				glVertex3f( 0.6, shieldHeight, -0.6 );
				glColor4f( 0.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 3.0, 0.0 );
				glVertex3f( -0.6, 0.0, -0.6 );
				glColor4f( 0.0, 0.64, 1.0, 0.7 );
				glTexCoord2f( 3.0, shieldUnitHeight );
				glVertex3f( -0.6, shieldHeight, -0.6 );
				glColor4f( 0.0, 0.0, 0.0, 0.7 );
				glTexCoord2f( 4.0, 0.0 );
				glVertex3f( -0.6, 0.0, 0.6 );
				glColor4f( 0.0, 0.64, 1.0, 0.7 );
				glTexCoord2f( 4.0, shieldUnitHeight );
				glVertex3f( -0.6, shieldHeight, 0.6 );
			glEnd();

			// Draw capacitor status.

			// Stop drawing HUD elements.
			// Return projection and modelview matrices to their in-game states.
		glPopMatrix();

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
}
