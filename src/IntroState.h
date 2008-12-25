#ifndef IntroState_H
#define IntroState_H

#ifndef PlayState_H
#include "PlayState.h"
#endif
#ifndef GameState_H
#include "GameState.h"
#endif

class IntroState : public GameState {
public:
    ~IntroState( void );

    void enter( void );
    void exit( void );

    void pause( void );
    void resume( void );
    void update( unsigned long lTimeElapsed );

    void keyPressed( const OIS::KeyEvent &e );
    void keyReleased( const OIS::KeyEvent &e );

    void mouseMoved( const OIS::MouseEvent &e );
    void mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
    void mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

    static IntroState* getSingletonPtr( void );
private:
    IntroState( void ) { }
    IntroState( const IntroState& ) { }
    IntroState & operator = ( const IntroState& );

    Ogre::Root           *mRoot;
    Ogre::Camera         *mCamera;
    Ogre::SceneManager   *mSceneMgr;
    Ogre::Viewport       *mViewport;
    Ogre::OverlayManager *mOverlayMgr;
    Ogre::Overlay        *mIntroOverlay;

    static IntroState    *mIntroState;
};
#endif

