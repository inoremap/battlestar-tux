/* Battlestar TUX
 * Copyright (C) 2008-2009 Eliot Eshelman <battlestartux@6by9.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include <Ogre.h>

#include "GameManager.h"
#include "IntroState.h"


int main( int argc, char **argv ) {
	GameManager *gameManager = GameManager::getSingletonPtr();

	try {
		// Initialize the game and open the introduction screen.
		gameManager->startGame( IntroState::getSingletonPtr() );
	}
	catch ( Ogre::Exception &ex ) {
		std::cerr << "An exception has occured: " << ex.getFullDescription();
	}

	delete gameManager;
	return 0;
}

