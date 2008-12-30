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

