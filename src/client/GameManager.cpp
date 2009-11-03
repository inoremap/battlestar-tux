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


#include <OgreWindowEventUtilities.h>
#include <OgreException.h>

#include "GameManager.h"
#include "GameState.h"
#include "IntroState.h"
#include "PauseState.h"
#include "PlayState.h"

using namespace Ogre;

GameManager* GameManager::mGameManager;

GameManager::GameManager() :
    mOgre( 0 ),
    mInputMgr( 0 ),
    mIntroState( 0 ),
    mPlayState( 0 ),
    mPauseState( 0 ),
    bShutdown( false ) {
}

GameManager::~GameManager() {
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
    mOgre = new Root("resources/plugins.cfg", "resources/ogre.cfg");

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
    }
}


bool GameManager::loadConfiguration() {
    // User may select their preferred renderer.  We will try to find it here.
    if (!mOgre->restoreConfig() && !mOgre->showConfigDialog())
        throw new Ogre::Exception(52, "User canceled the config dialog!", "BattlestarTUX::GameManager::loadConfiguration()");

    // Initialise and create a default rendering window
    std::string appName = "Battlestar T.U.X.";
    mRenderWindow = mOgre->initialise(true, appName);

    // Initialise resources
    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    // Create needed scenemanagers
    mOgre->createSceneManager( ST_GENERIC, "ST_GENERIC" );

    return true;
}

void GameManager::setupResources() {
    // Load resource path - materials and textures found here.
    String secName, typeName, archName;
    ConfigFile cf;
    cf.load("resources/resources.cfg");

    ConfigFile::SectionIterator seci = cf.getSectionIterator();
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }
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

void GameManager::requestShutdown() {
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

GameManager* GameManager::getSingletonPtr() {
    if( !mGameManager ) {
        mGameManager = new GameManager();
    }

    return mGameManager;
}
