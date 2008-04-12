/* Battle.h
 *
 * Copyright 2006-2008 Eliot Eshelman
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


#ifndef BATTLE_H_
#define BATTLE_H_

#include "CollisionManager.h"
#include "EnemyFighterList.h"
#include "ExplosionList.h"
#include "FighterAmmoList.h"
#include "Game.h"
#include "Ground.h"
#include "HeroFighter.h"
#include "HUD.h"
#include "Screen.h"

class PlayerFighterController;


/* The Hero's fighter is launched to battle a set of enemies. */
class Battle {
	public:
				Battle();
				~Battle();

				// Update battle status.
				void Update();

				// Draw battle.
				void Draw();

				// Finish the battle.
				void FinishBattle();
				bool isFinished();

				// Abort the battle - hero forfeits.
				void AbortBattle();
				bool isAborted();

	private:
				Battle( const Battle &battle );
				const Battle & operator= ( const Battle &battle );

				// Is battle still raging?
				bool finished;

				// Has the battle been aborted?
				bool aborted;

				Game* game;


				// Battle variables.
				Screen* screen;

				HUD* hud;

				CollisionManager* collisionManager;

				Ground* ground;

				HeroFighter* hero;
				PlayerFighterController* playerController;

				FighterAmmoList* heroAmmoList;
				FighterAmmoList* enemyAmmoList;

				EnemyFighterList* enemies;

				ExplosionList* explosionList;
};


#endif /*BATTLE_H_*/
