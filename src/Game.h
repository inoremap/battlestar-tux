/* Game.h
 *
 * Copyright 2005-2008 Eliot Eshelman
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


#ifndef GAME_H_
#define GAME_H_

#include <time.h>

#include "Vector.h"

class Config;
class EnemyFighterList;
class ExplosionList;
class FighterAmmoList;
class Fighter;
class Screen;
class TextureManager;

/* Stores game states and information. */
class Game {
	public:
				static Game* getGame();

				// Create a new game
				void newGame();

				// Game finished
				inline bool isFinished() { return finished; }

				// Temporarily pause a game in mid-motion.
				void pause();

				inline bool isPaused() { return paused; }

				// Exit game
				inline void exitBT() { finished = true; }

				// Mark time before beginning to draw next frame.
				void startFrame();

				// Mark time when done drawing frame.
				void stopFrame();

				unsigned int getGameFrame();
				int getGameSpeed();
				float* getBounds();
				vec3 getPos();

				Config* getConfig();
				void setConfig( Config* c );

				TextureManager* getTextureManager();
				void setTextureManager( TextureManager* t );

				EnemyFighterList* getEnemyFighterList();
				ExplosionList* getExplosionList();
				FighterAmmoList* getEnemyAmmoList();
				FighterAmmoList* getHeroAmmoList();
				Fighter* getFighter();
				Screen* getScreen();
				void setEnemyFighterList( EnemyFighterList* l );
				void setExplosionList( ExplosionList* l );
				void setEnemyAmmoList( FighterAmmoList* l );
				void setHeroAmmoList( FighterAmmoList* l );
				void setFighter( Fighter* f );
				void setScreen( Screen* s );

	private:
				// Constructor needs to be private, because Game is a singleton.
				Game();
				Game( const Game &game );
				const Game & operator= ( const Game &game );

				// We only need one copy of the game object.
				static Game* game;

				// Is Battlestar Tux finished?
				bool finished;

				// Is Battlestar Tux paused?
				bool paused;

				// Desired Frames Per Second (FPS).
				float desiredFps;

				// Current Frames Per Second (FPS).
				float fps;

				// Number of frames that have been drawn.
				// When frames are dropped, 'frame' will lag behind 'gameFrame'.
				unsigned int frame;

				// Number of frames that ought to have been drawn.
				// Keep track of accurate game speeds, even if frames are dropped.
				unsigned int gameFrame;

				// Last game frame that was drawn.
				unsigned int lastGameFrame;

				// Increases when frames are dropped.
				// Drops to 0 when frames are repeated.
				int gameSpeed;

				// Time the game started.
				unsigned int startTime;

				// Time when the last frame started being drawn.
				unsigned int lastTime;

				// Number of millisec to sleep between frames to remain synced.
				int syncSleep;

				// Maximum bounds of objects on the screen.
				// Bounds are always centered on (0, 0).
				float bounds[2];

				// Last known position of the fighter.
				// This is where the screen is centered.
				vec3 position;

				// Stores game configuration
				Config* config;

				// Manages all image textures.
				TextureManager* textureManager;

				EnemyFighterList* enemyFighterList;
				ExplosionList* explosionList;
				FighterAmmoList* enemyAmmoList;
				FighterAmmoList* heroAmmoList;
				Fighter* fighter;
				Screen* screen;
};


#endif /*GAME_H_*/
