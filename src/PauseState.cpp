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


#include "PauseState.h"

using namespace Ogre;

PauseState* PauseState::mPauseState;

void PauseState::enter() {
    mRoot            = Root::getSingletonPtr();
    mOverlayMgr      = OverlayManager::getSingletonPtr();
    mViewport        = mRoot->getAutoCreatedWindow()->getViewport( 0 );

    mInfoOverlay     = mOverlayMgr->getByName( "Overlay/Info" );
    mPauseOverlay    = mOverlayMgr->getByName( "Overlay/PauseState" );
    mMouseOverlay    = mOverlayMgr->getByName( "Overlay/MousePointer" );

    mInfoInstruction = mOverlayMgr->getOverlayElement( "Info/Instruction" );
    mMousePointer    = mOverlayMgr->getOverlayElement( "MousePointer/Pointer" );

    mInfoOverlay->show();
    mPauseOverlay->show();
    mMouseOverlay->show();

    mInfoInstruction->setCaption( "Press space to return" );
    Ogre::ColourValue newColor = mInfoInstruction->getColour();
    newColor.a = 1;
    mInfoInstruction->setColour(newColor);
}

void PauseState::exit() {
    mInfoOverlay->hide();
    mPauseOverlay->hide();
    mMouseOverlay->hide();
}

void PauseState::pause() {
    mInfoOverlay->hide();
    mPauseOverlay->hide();
    mMouseOverlay->hide();
}

void PauseState::resume() {
    mInfoOverlay->show();
    mPauseOverlay->show();
    mMouseOverlay->show();

    mInfoInstruction->setCaption( "Press space to return" );
    Ogre::ColourValue newColor = mInfoInstruction->getColour();
    newColor.a = 1;
    mInfoInstruction->setColour(newColor);
}

void PauseState::update( unsigned long lTimeElapsed ) {
}

void PauseState::keyPressed( const OIS::KeyEvent &e ) {
}

void PauseState::keyReleased( const OIS::KeyEvent &e ) {
    if( e.key == OIS::KC_SPACE ) {
        this->popState();
    }
    else if( e.key == OIS::KC_ESCAPE ) {
        this->requestShutdown();
    }
}

void PauseState::mouseMoved( const OIS::MouseEvent &e ) {
    const OIS::MouseState &mouseState = e.state;
    mMousePointer->setTop( mouseState.Y.abs );
    mMousePointer->setLeft( mouseState.X.abs );
}

void PauseState::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
}

void PauseState::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
}

PauseState* PauseState::getSingletonPtr() {
    if( !mPauseState ) {
        mPauseState = new PauseState();
    }

    return mPauseState;
}

