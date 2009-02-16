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
    mCamera->setPosition(Vector3(10, 10, 10));
    // TODO: poor clipping distances impinge performance
    mCamera->setNearClipDistance(Real(5));
    mCamera->setFarClipDistance(Real(100));
    mCamera->lookAt(0,0,0);

    // Configure lighting
    mSceneMgr->setAmbientLight(ColourValue(150.0/255, 150.0/255, 150.0/255));
    mViewport->setBackgroundColour(ColourValue(55.0/255, 140.0/255, 230.0/255));
    mLight = mSceneMgr->createLight("SunLight");
    mLight->setType(Light::LT_DIRECTIONAL);
    mLight->setDiffuseColour(ColourValue(255.0/255, 239.0/255, 162.0/255));
    mLight->setSpecularColour(ColourValue(255.0/255, 239.0/255, 162.0/255));
    mLight->setDirection(Vector3( 0, -1, -1 ));

    // Configure overlays
    mInfoOverlay      = mOverlayMgr->getByName( "Overlay/Info" );
    mMouseOverlay     = mOverlayMgr->getByName( "Overlay/MousePointer" );
    mInfoInstruction  = mOverlayMgr->getOverlayElement( "Info/Instruction" );
    mMousePointer     = mOverlayMgr->getOverlayElement( "MousePointer/Pointer" );
    mInfoInstruction->setCaption( "Press space for pause" );
    mInfoOverlay->show();
    mMouseOverlay->show();


    //// Initialize Bullet physics/collisions
    btVector3 worldAabbMin(-10000, -10000, -10000);
    btVector3 worldAabbMax(10000, 10000, 10000);
    int maxProxies = 1024;
    broadphase = new btAxisSweep3(worldAabbMin, worldAabbMax, maxProxies);

    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

    solver = new btSequentialImpulseConstraintSolver;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -10, 0));

    mBtDebugDrawer = new BtOgre::DebugDrawer(mSceneMgr->getRootSceneNode(), dynamicsWorld);
    dynamicsWorld->setDebugDrawer(mBtDebugDrawer);

    groundShape = new btStaticPlaneShape(btVector3(0,1,0), 1);
    btDefaultMotionState *groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
    btRigidBody::btRigidBodyConstructionInfo
            groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);
    //// End Bullet physics/collisions


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


    // Create player's ship
    Entity *player = mSceneMgr->createEntity( "Player", "HexCell.mesh" );
    playerNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( "PlayerNode", Vector3(0, 10, 0) );
    playerNode->attachObject(player);
    hexCellShape = new btCylinderShapeZ(btVector3(1.3,1.3,0.3));
    btScalar mass = 5;
    btVector3 inertia;
    hexCellShape->calculateLocalInertia(mass, inertia);
    BtOgre::RigidBodyState *state = new BtOgre::RigidBodyState(playerNode);
    hexCellRigidBody = new btRigidBody(mass, state, hexCellShape, inertia);
    dynamicsWorld->addRigidBody(hexCellRigidBody);
}

void PlayState::exit() {
    mInfoOverlay->hide();
    mMouseOverlay->hide();

    mSceneMgr->clearScene();
    mSceneMgr->destroyAllCameras();
    mRoot->getAutoCreatedWindow()->removeAllViewports();

    //// Cleanup Bullet physics simulation
    dynamicsWorld->removeRigidBody(hexCellRigidBody);
    delete hexCellRigidBody->getMotionState();
    delete hexCellRigidBody;

    dynamicsWorld->removeRigidBody(groundRigidBody);
    delete groundRigidBody->getMotionState();
    delete groundRigidBody;

    delete hexCellShape;

    delete groundShape;

    delete dynamicsWorld;
    delete solver;
    delete collisionConfiguration;
    delete dispatcher;
    delete broadphase;
    //// End Bullet physics simulation cleanup
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
    dynamicsWorld->stepSimulation(1/60.f,10);
    mBtDebugDrawer->step();

    Ogre::ColourValue newColor = mInfoInstruction->getColour();
    if(newColor.a > 0)
        newColor.a -= 0.001;
    else
        newColor.a = 0;
    mInfoInstruction->setColour(newColor);
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

