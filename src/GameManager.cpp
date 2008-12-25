#include "GameManager.h"
#include "OgreWindowEventUtilities.h"
#include "OgreException.h"

#ifndef PlayState_H
#include "PlayState.h"
#endif
#ifndef GameState_H
#include "GameState.h"
#endif
#ifndef IntroState_H
#include "IntroState.h"
#endif
#ifndef PauseState_H
#include "PauseState.h"
#endif


using namespace Ogre;

GameManager* GameManager::mGameManager;

GameManager::GameManager( void ) :
    mOgre( 0 ),
    mInputMgr( 0 ),
    mIntroState( 0 ),
    mPlayState( 0 ),
    mPauseState( 0 ),
    bShutdown( false ) {
}

GameManager::~GameManager( void ) {
    // Clean up all the states
    while( !mStates.empty() ) {
        mStates.back()->exit();
        mStates.pop_back();
    }

    if( mInputMgr ) {
        delete mInputMgr;
        mInputMgr = 0;
    }

    if( mIntroState ) {
        delete mIntroState;
        mIntroState = 0;
    }

    if( mPlayState ) {
        delete mPlayState;
        mPlayState  = 0;
    }

    if( mPauseState ) {
        delete mPauseState;
        mPauseState = 0;
    }

    if( mOgre ) {
        delete mOgre;
        mOgre = 0;
    }
}

void GameManager::startGame( GameState *gameState ) {
    mOgre = new Root("", "", "~/.battlestartux/battlestartux.log");

    // Setup states
    mIntroState = IntroState::getSingletonPtr();
    mPlayState  = PlayState::getSingletonPtr();
    mPauseState = PauseState::getSingletonPtr();

    // Setup and configure game
    this->setupResources();
    this->loadConfiguration();

    // Setup input
    mInputMgr = InputManager::getSingletonPtr();
    mInputMgr->initialise( mRenderWindow );
	WindowEventUtilities::addWindowEventListener( mRenderWindow, this );

    mInputMgr->addKeyListener( this, "GameManager" );
    mInputMgr->addMouseListener( this, "GameManager" );

    // Change to first state
    this->changeState( gameState );

    // lTimeLastFrame remembers the last time that it was checked
    // We use it to calculate the time since last frame
    unsigned long lTimeLastFrame = 0;

    // Main while-loop
    while( !bShutdown ) {
        // Calculate time since last frame and remember current time for next frame
        unsigned long lTimeCurrentFrame = mOgre->getTimer()->getMilliseconds();
        unsigned long lTimeSinceLastFrame = lTimeCurrentFrame - lTimeLastFrame;
        lTimeLastFrame = lTimeCurrentFrame;

        // Update inputmanager
        mInputMgr->capture();

        // Update current state
        mStates.back()->update( lTimeSinceLastFrame );

		WindowEventUtilities::messagePump();
		// Render next frame
        mOgre->renderOneFrame();

        // Deal with platform specific issues
        //PlatformManager::getSingletonPtr()->messagePump( mRenderWindow );
		//MYmessagePump( mRenderWindow );

		//WindowEventUtilities::addWindowEventListener(mRenderWindow, this);
    }
}


bool GameManager::loadConfiguration( void ) {
	//TODO: load config options from file
	std::string requestedRenderer = "OpenGL Rendering Subsystem";
	int width = 1024;
	int height = 768;
	bool fullscreen = false;
	std::cerr << "what??" << std::endl;
	// User may select their preferred renderer.  We will try to find it here.
	// Run through the list of available renderers and choose selected option.
	mOgre->setRenderSystem(mOgre->getRenderSystemByName(requestedRenderer));

    // Initialise and create a default rendering window
	std::string appName = "Battlestar T.U.X.";
    mRenderWindow = mOgre->initialise(false);
    mRenderWindow = mOgre->createRenderWindow(appName, width, height, fullscreen);

    // Initialise resources
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    // Create needed scenemanagers
    mOgre->createSceneManager( ST_GENERIC, "ST_GENERIC" );

    return true;
}

void GameManager::setupResources( void ) {
    // Load resource path - materials and textures found here.
	ResourceGroupManager::getSingleton().addResourceLocation(
			"resources", "FileSystem", "General", true);
}

void GameManager::changeState( GameState *gameState ) {
    // Cleanup the current state
    if( !mStates.empty() ) {
        mStates.back()->exit();
        mStates.pop_back();
    }

    // Store and init the new state
    mStates.push_back( gameState );
    mStates.back()->enter();
}

void GameManager::pushState( GameState *gameState ) {
    // Pause current state
    if( !mStates.empty() ) {
        mStates.back()->pause();
    }

    // Store and init the new state
    mStates.push_back( gameState );
    mStates.back()->enter();
}

void GameManager::popState() {
    // Cleanup the current state
    if( !mStates.empty() ) {
        mStates.back()->exit();
        mStates.pop_back();
    }

    // Resume previous state
    if( !mStates.empty() ) {
        mStates.back()->resume();
    }
}

void GameManager::requestShutdown( void ) {
    bShutdown = true;
}

bool GameManager::keyPressed( const OIS::KeyEvent &e ) {
    // Call keyPressed of current state
    mStates.back()->keyPressed( e );

    return true;
}

bool GameManager::keyReleased( const OIS::KeyEvent &e ) {
    // Call keyReleased of current state
    mStates.back()->keyReleased( e );

    return true;
}

bool GameManager::mouseMoved( const OIS::MouseEvent &e ) {
    // Call mouseMoved of current state
    mStates.back()->mouseMoved( e );

    return true;
}

bool GameManager::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
    // Call mousePressed of current state
    mStates.back()->mousePressed( e, id );

    return true;
}

bool GameManager::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
    // Call mouseReleased of current state
    mStates.back()->mouseReleased( e, id );

    return true;
}

GameManager* GameManager::getSingletonPtr( void ) {
    if( !mGameManager ) {
        mGameManager = new GameManager();
    }

    return mGameManager;
}
