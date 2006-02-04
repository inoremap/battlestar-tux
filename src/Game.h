/* Game.h
 *
 * Copyright 2005-2006 Eliot Eshelman
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


#ifndef GAME_H_
#define GAME_H_

#include "time.h"

class EnemyFighterList;
class FighterAmmoList;
class Fighter;


/* Stores game states and information. */
class Game {
	public:
				// Return instance of Game
				static Game* getInstance();

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

				int getGameFrame();
				float getGameSpeed();
				float* getBounds();
				float getScrollSpeed();

				EnemyFighterList* getEnemyFighterList();
				FighterAmmoList* getEnemyAmmoList();
				FighterAmmoList* getHeroAmmoList();
				void setEnemyFighterList( EnemyFighterList* l );
				void setEnemyAmmoList( FighterAmmoList* l );
				void setHeroAmmoList( FighterAmmoList* l );
				Fighter* getFighter();
				void setFighter( Fighter* f );

	private:
				// Is Battlestar Tux finished?
				static bool finished;

				// Is Battlestar Tux paused?
				static bool paused;

				// Desired Frames Per Second (FPS).
				static float desiredFps;

				// Current Frames Per Second (FPS).
				static float fps;

				// Number of frames that have been drawn.
				// When frames are dropped, 'frame' will lag behind 'gameFrame'.
				static unsigned int frame;

				// Number of frames that ought to have been drawn.
				// Keep track of accurate game speeds, even if frames are dropped.
				static unsigned int gameFrame;

				// Last game frame that was drawn.
				static unsigned int lastGameFrame;

				// Increases when frames are dropped.
				// Drops to 0 when frames are repeated.
				static float gameSpeed;

				// Time the game started.
				static unsigned int startTime;

				// Time when the last frame started being drawn.
				static unsigned int lastTime;

				// Number of millisec to sleep between frames to remain synced.
				static int syncSleep;

				// Maximum bounds of objects on the screen.
				//
				//  (-40, 30)             (40, 30)
				//
				//  (-40, -30)            (40, -30)
				//
				static float bounds[2];

				// Base scroll speed.  Objects on the ground will move at this speed.
				// Aircraft have their own velocity and may move faster.
				static float scrollSpeed;

				static Game* instance;

				EnemyFighterList* enemyFighterList;
				FighterAmmoList* enemyAmmoList;
				FighterAmmoList* heroAmmoList;
				Fighter* fighter;

				Game();
};


#endif /*GAME_H_*/
