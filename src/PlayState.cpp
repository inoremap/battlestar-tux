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


#include <OgreTextureUnitState.h>

#include "PlayState.h"

using namespace Ogre;

PlayState* PlayState::mPlayState;

void PlayState::enter() {
    mRoot             = Root::getSingletonPtr();
    mOverlayMgr       = OverlayManager::getSingletonPtr();
    mInputDevice      = InputManager::getSingletonPtr()->getKeyboard();
    mSceneMgr         = mRoot->getSceneManager( "ST_GENERIC" );
    mCamera           = mSceneMgr->createCamera( "PlayCamera" );
    mViewport         = mRoot->getAutoCreatedWindow()->addViewport( mCamera );

    // Configure camera
    mCamera->setAspectRatio(
    		Real(mViewport->getActualWidth()) /
    		Real(mViewport->getActualHeight())
    		);
    mCamera->setPosition(Vector3(0, 0, 30));
    // TODO: poor clipping distances impinge performance
    mCamera->setNearClipDistance(Real(20));
    mCamera->setFarClipDistance(Real(0));

    // Configure lighting
    mSceneMgr->setAmbientLight(ColourValue( 1, 1, 1 ));
    mViewport->setBackgroundColour(ColourValue(105.0/255, 105.0/255, 105.0/255));
    mLight = mSceneMgr->createLight("SunLight");
    mLight->setType(Light::LT_DIRECTIONAL);
    mLight->setDiffuseColour(ColourValue(0.85, 0.85, 0.75));
    mLight->setSpecularColour(ColourValue(0.35, 0.35, 0.25));
    mLight->setDirection(Vector3( 0, -1, -1 ));

    // Configure overlays
    mInfoOverlay      = mOverlayMgr->getByName( "Overlay/Info" );
    mMouseOverlay     = mOverlayMgr->getByName( "Overlay/MousePointer" );
    mInfoInstruction  = mOverlayMgr->getOverlayElement( "Info/Instruction" );
    mMousePointer     = mOverlayMgr->getOverlayElement( "MousePointer/Pointer" );
    mInfoInstruction->setCaption( "Press space for pause" );
    mInfoOverlay->show();
    mMouseOverlay->show();

    // Create player's ship
    Entity *player = mSceneMgr->createEntity( "Player", "HexCell.mesh" );
    SceneNode *playerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "PlayerNode" );
    playerNode->attachObject(player);
    mCamera->lookAt(playerNode->getPosition());
}

void PlayState::exit() {
    mInfoOverlay->hide();
    mMouseOverlay->hide();

    mSceneMgr->clearScene();
    mSceneMgr->destroyAllCameras();
    mRoot->getAutoCreatedWindow()->removeAllViewports();
}

void PlayState::pause() {
    mInfoOverlay->hide();
    mMouseOverlay->hide();
}

void PlayState::resume() {
    mInfoOverlay->show();
    mMouseOverlay->show();

    mInfoInstruction->setCaption( "Press space for pause" );
}

void PlayState::update( unsigned long lTimeElapsed ) {
}

void PlayState::keyPressed( const OIS::KeyEvent &e ) {
}

void PlayState::keyReleased( const OIS::KeyEvent &e ) {
    if( e.key == OIS::KC_SPACE ) {
        this->pushState( PauseState::getSingletonPtr() );
    }
    else if( e.key == OIS::KC_ESCAPE ) {
        this->requestShutdown();
    }
}

void PlayState::mouseMoved( const OIS::MouseEvent &e ) {
    const OIS::MouseState &mouseState = e.state;
    mMousePointer->setTop( mouseState.Y.abs );
    mMousePointer->setLeft( mouseState.X.abs );
}

void PlayState::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
}

void PlayState::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) {
}

PlayState* PlayState::getSingletonPtr() {
    if( !mPlayState ) {
        mPlayState = new PlayState();
    }

    return mPlayState;
}

