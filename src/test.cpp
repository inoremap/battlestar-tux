/* test.cpp
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


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include "SDL.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "EnemyFighterList.h"
#include "Fighter/EnemyFighter.h"
#include "Fighter/HeroFighter.h"
#include "FighterAmmo.h"
#include "FighterAmmoList.h"
#include "Game.h"
#include "Ground.h"
#include "HUD.h"
#include "Screen.h"

using namespace std;

int main(int argc, char* argv[])
{
	Screen* screen = new Screen();
	int x = 0;
	int y = 0;
	float realWidth = 0.0;
	float realHeight = 0.0;
	Game* game = Game::getInstance();
	SDL_Event event;

	// Exit if there is no screen.
	if( screen->isNull() ) {
		game->exitBT();
		return 1;
	}

	HUD* hud = new HUD( game );
	Ground* ground = new Ground( SOLID_GROUND, game );

	HeroFighter* hero = new HeroFighter( BASIC_FIGHTER, game );
	game->setFighter( hero );

	FighterAmmoList* heroAmmoList = new FighterAmmoList( game );
	game->setHeroAmmoList( heroAmmoList );

	EnemyFighterList* enemies = new EnemyFighterList( game );
	game->setEnemyFighterList( enemies );

	FighterAmmoList* enemyAmmoList = new FighterAmmoList( game );
	game->setEnemyAmmoList( enemyAmmoList );


	printf( "Testing Battlestar TUX...\n\n" );
////// Test suite.

	//// Test Displaylist:
	printf( "\nAdding 1000 enemies...\n" );
	for( int n=0; n < 1000; n++ ) {
		EnemyFighter* f = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
		f->setPos( 0, n );
		enemies->addObject( f );
		enemies->DrawObjects();
	}
	enemies->printList();

	printf( "Removing all enemies...\n" );
	EnemyFighter* root = (EnemyFighter*) enemies->getRoot();
	while( root ) {
		EnemyFighter* next = (EnemyFighter*) root->getNext();

		enemies->DrawObjects();

		enemies->remObject( root );

		root = next;
	}
	enemies->printList();

	printf( "\nAdding 1000 enemies...\n" );
	for( int n=0; n < 1000; n++ ) {
		EnemyFighter* f = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
		f->setPos( 0, n );
		enemies->addObject( f );
		enemies->DrawObjects();
	}
	enemies->printList();

	printf( "Removing all enemies in reverse order...\n" );
	root = (EnemyFighter*) enemies->getRoot();
	EnemyFighter* last = 0;
	while( root ) {
		last = root;
		root = (EnemyFighter*) root->getNext();
	}
	while( last ) {
		EnemyFighter* next = (EnemyFighter*) last->getPrev();

		enemies->DrawObjects();

		enemies->remObject( last );

		last = next;
	}
	enemies->printList();

	printf( "\nAdding 1000 enemies...\n" );
	for( int n=0; n < 1000; n++ ) {
		EnemyFighter* f = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
		f->setPos( 0, n );
		enemies->addObject( f );
		enemies->DrawObjects();
	}
	enemies->printList();

	printf( "Removing all enemies in random order...\n" );
	root = 0;
	last = 0;
	unsigned int rand = 0;
	int count = 0;
	srandom( time(NULL) );
	while( root = (EnemyFighter*) enemies->getRoot() ) {
		last = root;
		rand = (unsigned int) (1000.0 * random() / RAND_MAX);

		// Remove the first entry every once in a while.
		if( count % 100 == 0 ) {}
		else {
			// Flip through a random number of enemies.
			for( unsigned int i = 0; i < rand; i++ ) {
				root = (EnemyFighter*) last->getNext();

				if( root )
					last = root;
				else
					break;
			}
		}

		enemies->DrawObjects();

		enemies->remObject( last );
		count++;
	}
	enemies->printList();
	//// Done testing DisplayList

	//// Test culling:
	printf( "\nTesting culling...\n" );
	EnemyFighter* top = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
	top->setPos( 0, 100 );
	enemies->addObject( top );

	EnemyFighter* right = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
	right->setPos( 100, 0 );
	enemies->addObject( right );

	EnemyFighter* bottom = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
	bottom->setPos( 0, -100 );
	enemies->addObject( bottom );

	EnemyFighter* left = new EnemyFighter( BASIC_ENEMY_FIGHTER, enemies, game );
	left->setPos( -100, 0 );
	enemies->addObject( left );

	enemies->printList();

	printf( "Culling top...\n" );
	enemies->CullObjects( CULL_TOP );
	enemies->printList();

	printf( "Culling right...\n" );
	enemies->CullObjects( CULL_RIGHT );
	enemies->printList();

	printf( "Culling bottom...\n" );
	enemies->CullObjects( CULL_BOTTOM );
	enemies->printList();

	printf( "Culling left...\n" );
	enemies->CullObjects( CULL_LEFT );
	enemies->printList();
	//// Done testing culling.

////// End Test suite.

	SDL_Quit();

    return 0;
}
