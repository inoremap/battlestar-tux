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


#ifndef GameManager_H
#define GameManager_H

#include <Ogre.h>//#include <OgreRoot.h>
#include <OgreConfigFile.h>
//#include <OgreRenderWindow.h>
//#include <OgrePlatformManager.h>//yys
#include <OgreWindowEventUtilities.h>

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>
//#include <OISMouse.h>
//#include <OISKeyboard.h>


#ifndef InputManager_H
#include "InputManager.h"
#endif

class GameState;

class GameManager : public OIS::KeyListener, OIS::MouseListener ,  public Ogre::WindowEventListener {
public:
    ~GameManager();

    void startGame( GameState *gameState );

    void changeState( GameState *gameState );
    void pushState( GameState *gameState );
    void popState();
    void requestShutdown();

    static GameManager* getSingletonPtr();

private:
    GameManager();
    GameManager( const GameManager& ) { }
    GameManager & operator = ( const GameManager& );

    bool loadConfiguration();
    void setupResources();

    bool keyPressed( const OIS::KeyEvent &e );
    bool keyReleased( const OIS::KeyEvent &e );

    bool mouseMoved( const OIS::MouseEvent &e );
    bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

    Ogre::Root         *mOgre;
    Ogre::RenderWindow *mRenderWindow;
    InputManager       *mInputMgr;

    GameState          *mIntroState;
    GameState          *mPlayState;
    GameState          *mPauseState;

    bool bShutdown;
    std::vector<GameState*> mStates;
    static GameManager *mGameManager;
};
#endif
