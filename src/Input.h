#pragma once

#include "OISEvents.h"
#include "OISInputManager.h"
#include "OISMouse.h"
#include "OISKeyboard.h"
#include "OISJoyStick.h"

class Simulation;

namespace CEGUI
{
	class System;
}

class InputHandler : 
		public OIS::MouseListener, 
		public OIS::KeyListener, 
		public OIS::JoyStickListener
{
private:
	OIS::InputManager *m_ois;
	OIS::Mouse *mMouse;
	OIS::Keyboard *mKeyboard;
	unsigned long m_hWnd;
	Simulation *m_simulation;	
	CEGUI::System* m_pSystem;

public:
	InputHandler(CEGUI::System* pSystem, Simulation *sim, unsigned long hWnd); 
	~InputHandler();

	void setWindowExtents(int width, int height) ;
	void capture();
	
	// MouseListener
	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID);
	
	// KeyListener
	bool keyPressed(const OIS::KeyEvent &evt);
	bool keyReleased(const OIS::KeyEvent &evt);
	
	// JoyStickListener
	bool buttonPressed(const OIS::JoyStickEvent &evt, int index);
	bool buttonReleased(const OIS::JoyStickEvent &evt, int index);
	bool axisMoved(const OIS::JoyStickEvent &evt, int index);
	bool povMoved(const OIS::JoyStickEvent &evt, int index);
};

