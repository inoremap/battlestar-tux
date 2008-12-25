#include <Ogre.h>

#ifndef GameManager_H
#include "GameManager.h"
#endif

#ifndef IntroState_H
#include "IntroState.h"
#endif


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

