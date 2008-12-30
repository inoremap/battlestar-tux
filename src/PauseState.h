#ifndef PauseState_H
#define PauseState_H

#ifndef PlayState_H
#include "PlayState.h"
#endif
#ifndef GameState_H
#include "GameState.h"
#endif

class PauseState : public GameState {
public:
    ~PauseState() { }

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

    static PauseState* getSingletonPtr();
private:
    PauseState() { }
    PauseState( const PauseState& ) { }
    PauseState & operator = ( const PauseState& );

    Ogre::Root           *mRoot;
    Ogre::Camera         *mCamera;
    Ogre::SceneManager   *mSceneMgr;
    Ogre::Viewport       *mViewport;
    Ogre::OverlayManager *mOverlayMgr;
    Ogre::Overlay        *mInfoOverlay;
    Ogre::Overlay        *mPauseOverlay;
    Ogre::Overlay        *mMouseOverlay;
    Ogre::OverlayElement *mMousePointer;
    Ogre::OverlayElement *mInfoInstruction;

    static PauseState    *mPauseState;
};
#endif

