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


#ifndef GameState_H
#define GameState_H

#include <Ogre.h>//#include <OgreRoot.h>
//#include <OgreRenderWindow.h>
//#include <OgreOverlayElement.h>
//#include <OgreOverlayManager.h>
#include <OgreStringConverter.h>

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>
//#include <OISMouse.h>
//#include <OISKeyboard.h>
#ifndef GameManager_H
#include "GameManager.h"
#endif
#ifndef InputManager_H
#include "InputManager.h"
#endif

class GameState {
public:
    ~GameState() { }

    virtual void enter()  = 0;
    virtual void exit()   = 0;

    virtual void pause()  = 0;
    virtual void resume() = 0;
    virtual void update( unsigned long lTimeElapsed ) = 0;
    
    virtual void keyPressed( const OIS::KeyEvent &e )  = 0;
    virtual void keyReleased( const OIS::KeyEvent &e ) = 0;

    virtual void mouseMoved( const OIS::MouseEvent &e ) = 0;
    virtual void mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )  = 0;
    virtual void mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) = 0;

    void changeState( GameState *state );
    void pushState( GameState *state );
    void popState();
    void requestShutdown();
protected:
    GameState() { }
private:
    GameState( const GameState& ) { }
    GameState & operator = ( const GameState& );
};
#endif

