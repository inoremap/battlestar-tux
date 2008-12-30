#ifndef GameManager_H
#define GameManager_H

#include <Ogre.h>//#include <OgreRoot.h>
#include <OgreConfigFile.h>
//#include <OgreRenderWindow.h>
//#include <OgrePlatformManager.h>//yys
#include <OgreWindowEventUtilities.h>

#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>
//#include <OISMouse.h>
//#include <OISKeyboard.h>


#ifndef InputManager_H
#include "InputManager.h"
#endif

class GameState;

class GameManager : public OIS::KeyListener, OIS::MouseListener ,  public Ogre::WindowEventListener {
public:
    ~GameManager();

    void startGame( GameState *gameState );

    void changeState( GameState *gameState );
    void pushState( GameState *gameState );
    void popState();
    void requestShutdown();

    static GameManager* getSingletonPtr();

private:
    GameManager();
    GameManager( const GameManager& ) { }
    GameManager & operator = ( const GameManager& );

    bool loadConfiguration();
    void setupResources();

    bool keyPressed( const OIS::KeyEvent &e );
    bool keyReleased( const OIS::KeyEvent &e );

    bool mouseMoved( const OIS::MouseEvent &e );
    bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
    bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

    Ogre::Root         *mOgre;
    Ogre::RenderWindow *mRenderWindow;
    InputManager       *mInputMgr;

    GameState          *mIntroState;
    GameState          *mPlayState;
    GameState          *mPauseState;

    bool bShutdown;
    std::vector<GameState*> mStates;
    static GameManager *mGameManager;
};
#endif
