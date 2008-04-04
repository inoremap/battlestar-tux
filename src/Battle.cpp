/* Battle.cpp
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


#include <math.h>

#include "Battle.h"
#include "Config.h"
#include "EnemyFighter.h"
#include "FighterAmmo.h"
#include "PlayerFighterController.h"
#include "TextureManager.h"
#include "Vector.h"

Battle::Battle( Game* g ) {
	game = g;

	aborted = false;
	finished = false;

	screen = game->getScreen();

	hud = new HUD( game );

	collisionManager = new CollisionManager();

	ground = new Ground( SOLID_GROUND, game );

	hero = new HeroFighter( game );
	game->setFighter( hero );

	playerController = new PlayerFighterController( this, screen, hero, game );

	heroAmmoList = new FighterAmmoList( game );
	game->setHeroAmmoList( heroAmmoList );

	enemies = new EnemyFighterList( game );
	game->setEnemyFighterList( enemies );

	explosionList = new ExplosionList( game );
	game->setExplosionList( explosionList );

	enemyAmmoList = new FighterAmmoList( game );
	game->setEnemyAmmoList( enemyAmmoList );
}


Battle::~Battle() {
	delete hud;
	delete explosionList;
	delete heroAmmoList;
	delete enemyAmmoList;
	delete hero;
	delete playerController;
	delete enemies;
	delete ground;
	delete collisionManager;
}


void Battle::Update() {
	// If not paused, update all positions/states.
	int speed = game->getGameSpeed();
	if( !game->isPaused() ) {
		heroAmmoList->UpdateObjects();
		enemyAmmoList->UpdateObjects();

		heroAmmoList->CheckCollisions( enemies );
		enemyAmmoList->CheckCollisions( hero );

		explosionList->Update( speed );

		hero->Update( speed );
		if( hero->getHealth() <= 0 )
			FinishBattle();

		enemies->UpdateObjects();

		enemies->CheckCollisions( hero );

		ground->Update();
	}
	playerController->Update( speed );
}


void Battle::Draw() {
	// Don't need to clear the screen, because the
	// entire area will be drawn again.  +20fps
	// If we're in wireframe mode, the clear will be necessary.
	if( game->getConfig()->getWireframe() )
		glClear( GL_COLOR_BUFFER_BIT );

	glClear( GL_DEPTH_BUFFER_BIT );

	// Set camera position and draw stuff...
	// We want the camera to follow our fighter.
	vec3 heroPos = hero->getPos();
	glLoadIdentity();
	glTranslatef( -heroPos[0], -heroPos[1], -30 );

	ground->Draw();
	//draw ground units?
	enemyAmmoList->DrawObjects();
	heroAmmoList->DrawObjects();
	enemies->DrawObjects();
	hero->Draw();
	explosionList->Draw();
	//draw power ups
	hud->Draw();
}


void Battle::FinishBattle() { finished = true; }
bool Battle::isFinished() { return finished; }

void Battle::AbortBattle() { aborted = true; }
bool Battle::isAborted() { return aborted; }
