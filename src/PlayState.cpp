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

#include "EnergyCell.h"
#include "HexCell.h"
#include "HexShip.h"
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

    // Configure overlays
    mInfoOverlay      = mOverlayMgr->getByName( "Overlay/Info" );
    mMouseOverlay     = mOverlayMgr->getByName( "Overlay/MousePointer" );
    mInfoInstruction  = mOverlayMgr->getOverlayElement( "Info/Instruction" );
    mMousePointer     = mOverlayMgr->getOverlayElement( "MousePointer/Pointer" );
    mInfoInstruction->setCaption( "Press space for pause" );
    mInfoOverlay->show();
    mMouseOverlay->show();

    // Draw Origin with X, Y, Z Axes
    ManualObject* axes = mSceneMgr->createManualObject("Axes");
    SceneNode* axesNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("AxesNode");
    axes->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
    axes->position(0,0,0);    axes->colour(1,0,0);
    axes->position(10,0,0);   axes->colour(1,0,0);
    axes->position(0,0,0);    axes->colour(0,1,0);
    axes->position(0,10,0);   axes->colour(0,1,0);
    axes->position(0,0,0);    axes->colour(0,0,1);
    axes->position(0,0,10);   axes->colour(0,0,1);
    axes->end();
    axesNode->attachObject(axes);


    // Initialize Bullet physics simulation
    mPhysicsManager = PhysicsManager::getSingletonPtr();

    // Add player's ship
    mPlayer = new HexShip("PlayerShip", Vector3(0,2,0));
    HexCell* coreCell = new HexCell("PlayerShip:CoreCell", 1, 1000);
    mPlayer->addCoreHexCell(coreCell, 0, 0);
    EnergyCell* energyCell = new EnergyCell("PlayerShip:EnergyCell", 1, 500, 100, 500);
    mPlayer->addHexCell(energyCell, 0, 1);

    // Add AI ship
    HexShip* ai = new HexShip("AI", Vector3(15, 2, 0));
    coreCell = new HexCell("AI:CoreCell", 1, 2000);
    ai->addCoreHexCell(coreCell, 0, 0);
    for(int i=-1; i<=1; i++) {
        for(int n=0; n<=2; n++) {
            String aiName = "AI";
            aiName += "-Row-" + StringConverter::toString(n)
                    + "-Column-" + StringConverter::toString(i);
            HexCell* cell = new HexCell(aiName + ":Cell", 1, 1000);
            ai->addHexCell(cell, i, n);
        }
    }

    // Configure camera
    mCamera->setAspectRatio(
            Real(mViewport->getActualWidth()) /
            Real(mViewport->getActualHeight())
            );
    // TODO: poor clipping distances impinge performance
    mCamera->setNearClipDistance(Real(5));
    mCamera->setFarClipDistance(Real(100));
    // Attach to player's ship and track.
    mPlayer->getOgreNode()->attachObject(mCamera);
    mCamera->setAutoTracking(true, mPlayer->getOgreNode());
    // Set camera distance from player.
    mCamera->setPosition(Vector3(0.1, 50, 0));


    // Configure lighting
    mSceneMgr->setAmbientLight(ColourValue(150.0/255, 150.0/255, 150.0/255));
    mViewport->setBackgroundColour(ColourValue(55.0/255, 140.0/255, 230.0/255));
    mLight = mSceneMgr->createLight("SunLight");
    mLight->setType(Light::LT_DIRECTIONAL);
    mLight->setDiffuseColour(ColourValue(255.0/255, 239.0/255, 162.0/255));
    mLight->setSpecularColour(ColourValue(255.0/255, 239.0/255, 162.0/255));
    mLight->setDirection(Vector3( 0, -1, -1 ));
}

void PlayState::exit() {
    mInfoOverlay->hide();
    mMouseOverlay->hide();

    mSceneMgr->clearScene();
    mSceneMgr->destroyAllCameras();
    mRoot->getAutoCreatedWindow()->removeAllViewports();

    delete mPlayer;
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
    mPhysicsManager->update(lTimeElapsed);
    mPlayer->update(lTimeElapsed);

    Ogre::ColourValue newColor = mInfoInstruction->getColour();
    if(newColor.a > 0)
        newColor.a -= 0.001;
    else
        newColor.a = 0;
    mInfoInstruction->setColour(newColor);
}

void PlayState::keyPressed( const OIS::KeyEvent &e ) {
    switch(e.key) {
    case OIS::KC_U:
        mPlayer->applyCentralImpulse(Vector3(0,0,-10));
        break;
    case OIS::KC_A:
        mPlayer->applyCentralImpulse(Vector3(0,0,10));
        break;
    case OIS::KC_COMMA:
        mPlayer->applyCentralImpulse(Vector3(-10,0,0));
        break;
    case OIS::KC_O:
        mPlayer->applyCentralImpulse(Vector3(10,0,0));
        break;
    default:
        break;
    }
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

