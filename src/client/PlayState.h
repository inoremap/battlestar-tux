/* Battlestar TUX
 * Copyright (C) 2008-2010 Eliot Eshelman <battlestartux@6by9.net>
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

#include <Ogre.h>

#include "GameState.h"
#include "HexShip/HexShip.h"
#include "PauseState.h"
#include "PhysicsManager.h"

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
    Ogre::Light          *mLight;
    Ogre::SceneManager   *mSceneMgr;
    Ogre::Viewport       *mViewport;
    Ogre::OverlayManager *mOverlayMgr;
    Ogre::Overlay        *mInfoOverlay;
    Ogre::Overlay        *mMouseOverlay;
    Ogre::OverlayElement *mMousePointer;
    Ogre::OverlayElement *mInfoInstruction;

    OIS::Keyboard        *mInputDevice;

    /** Store the world coordinates of the location of the mouse cursor in (x,z)
      * space.  This point is on the same plane the HexShips are on.
      */
    void updateMouseWorldCoords(const OIS::MouseState &mouseState);

    /// World coordinates of the location of the mouse cursor.
    Ogre::Vector3 mMouseWorldCoords;

    /// Imaginary plane for calculating cursor world coordinates.
    Ogre::Plane mCoordPlane;

    PhysicsManager *mPhysicsManager;

    HexShip *mPlayer;

    static PlayState *mPlayState;
};

#endif

