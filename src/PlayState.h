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


#ifndef PlayState_H
#define PlayState_H

#include <Ogre.h>//#include <OgreCamera.h>


#ifndef GameState_H
#include "GameState.h"
#endif
#ifndef PauseState_H
#include "PauseState.h"
#endif

class PlayState : public GameState {
public:
    ~PlayState();

    void enter();
    void exit();

    void pause();
    void resume();
    void update( unsigned long lTimeElapsed );

    void keyPressed( const OIS::KeyEvent &e );
    void keyReleased( const OIS::KeyEvent &e );

    void mouseMoved( const OIS::MouseEvent &e );
    void mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
    void mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

    static PlayState* getSingletonPtr();
private:
    PlayState() { }
    PlayState( const PlayState& ) { }
    PlayState & operator = ( const PlayState& );

    Ogre::Root           *mRoot;
    Ogre::Camera         *mCamera;
    Ogre::SceneManager   *mSceneMgr;
    Ogre::Viewport       *mViewport;
    Ogre::OverlayManager *mOverlayMgr;
    Ogre::Overlay        *mInfoOverlay;
    Ogre::Overlay        *mPlayOverlay;
    Ogre::Overlay        *mMouseOverlay;
    Ogre::OverlayElement *mMousePointer;
    Ogre::OverlayElement *mInfoInstruction;
    Ogre::OverlayElement *mInfoNotification;

    OIS::Keyboard        *mInputDevice;

    static PlayState *mPlayState;
};
#endif

