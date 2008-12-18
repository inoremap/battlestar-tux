#include "Input.h"
#include "OgreStringConverter.h"
#include "Simulation.h"
#include "CEGUISystem.h"

InputHandler::InputHandler(CEGUI::System* pSystem, Simulation *sim, unsigned long hWnd) :
	m_pSystem(pSystem)
{
	
	OIS::ParamList pl;
	pl.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
	
	m_hWnd = hWnd;
	m_ois = OIS::InputManager::createInputSystem( pl );
	mMouse = static_cast<OIS::Mouse*>(m_ois->createInputObject( OIS::OISMouse, true ));
	mKeyboard = static_cast<OIS::Keyboard*>(m_ois->createInputObject( OIS::OISKeyboard, true));
	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	m_simulation = sim;
}

InputHandler::~InputHandler() {
	if (mMouse)
		delete mMouse;
	if (mKeyboard)
		delete mKeyboard;
	OIS::InputManager::destroyInputSystem(m_ois);
}

void InputHandler::capture() {
	mMouse->capture();
	mKeyboard->capture();
}

void  InputHandler::setWindowExtents(int width, int height){
	//Set Mouse Region.. if window resizes, we should alter this to reflect as well
	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}


// MouseListener
bool InputHandler::mouseMoved(const OIS::MouseEvent &evt) {
	m_pSystem->injectMouseWheelChange(evt.state.Z.rel);
	return m_pSystem->injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
}

bool InputHandler::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID btn) {
	CEGUI::MouseButton button = CEGUI::NoButton;

	if (btn == OIS::MB_Left)
		button = CEGUI::LeftButton;
	
	if (btn == OIS::MB_Middle)
		button = CEGUI::MiddleButton;
	
	if (btn == OIS::MB_Right)
		button = CEGUI::RightButton;

	return m_pSystem->injectMouseButtonDown(button);
}

bool InputHandler::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID btn) {
	CEGUI::MouseButton button = CEGUI::NoButton;

	if (btn == OIS::MB_Left)
		button = CEGUI::LeftButton;
	
	if (btn == OIS::MB_Middle)
		button = CEGUI::MiddleButton;
	
	if (btn == OIS::MB_Right)
		button = CEGUI::RightButton;
	
	return m_pSystem->injectMouseButtonUp(button);
}

		
// KeyListener
bool InputHandler::keyPressed(const OIS::KeyEvent &evt) {
	unsigned int ch = evt.text;

	m_pSystem->injectKeyDown(evt.key);
	return m_pSystem->injectChar(ch);
}

bool InputHandler::keyReleased(const OIS::KeyEvent &evt) {
	if (evt.key == OIS::KC_ESCAPE)
		m_simulation->requestStateChange(SHUTDOWN);

	return m_pSystem->injectKeyUp(evt.key);
}

		

// JoyStickListener
bool InputHandler::buttonPressed(const OIS::JoyStickEvent &evt, int index) {
	return true;
}

bool InputHandler::buttonReleased(const OIS::JoyStickEvent &evt, int index) {
	return true;
}

bool InputHandler::axisMoved(const OIS::JoyStickEvent &evt, int index) {
	return true;
}

bool InputHandler::povMoved(const OIS::JoyStickEvent &evt, int index) {
	return true;
}

