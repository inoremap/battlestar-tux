#include "MainMenuDlg.h"
#include "Simulation.h"
#include "CEGUISystem.h"
#include "CEGUIWindow.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIPushButton.h"

MainMenuDlg::MainMenuDlg(CEGUI::System *pSystem, CEGUI::Window *pSheet, Simulation *pSimulation)
{
	m_pSystem = pSystem;
	m_pWindow = pSheet;
	m_pSimulation = pSimulation;

	// hook up the event handlers to the window elements
	CEGUI::PushButton* pQuitButton = (CEGUI::PushButton *)CEGUI::WindowManager::getSingleton().getWindow("cmdQuit");
	pQuitButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuDlg::Quit_OnClick, this));

	CEGUI::PushButton* pOptionsButton = (CEGUI::PushButton *)CEGUI::WindowManager::getSingleton().getWindow("cmdOptions");
	pOptionsButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuDlg::Options_OnClick, this));

	CEGUI::PushButton* pLaunchButton = (CEGUI::PushButton *)CEGUI::WindowManager::getSingleton().getWindow("cmdInstantAction");
	pLaunchButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&MainMenuDlg::Launch_OnClick, this));
}

MainMenuDlg::~MainMenuDlg()
{
}

bool MainMenuDlg::Quit_OnClick(const CEGUI::EventArgs &args)
{
	m_pSimulation->requestStateChange(SHUTDOWN);
	return true;
}

bool MainMenuDlg::Launch_OnClick(const CEGUI::EventArgs &args)
{
	return true;
}

bool MainMenuDlg::Options_OnClick(const CEGUI::EventArgs &args)
{
	return true;
}
