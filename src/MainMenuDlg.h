#pragma once

#include "CEGUIWindow.h"

namespace CEGUI
{
	class System;
	class Window;
}

class Simulation;

class MainMenuDlg
{
public:
	MainMenuDlg(CEGUI::System* pSystem, CEGUI::Window* pSheet, Simulation* pSimulation);
	~MainMenuDlg();

	// CEGUI event handlers. You can name these whatever you like, so long as they have the proper 
	// signature: bool <method name>(const CEGUI::EventArgs &args)
	bool Quit_OnClick(const CEGUI::EventArgs &args);
	bool Options_OnClick(const CEGUI::EventArgs &args);
	bool Launch_OnClick(const CEGUI::EventArgs &args);

private:
	CEGUI::System* m_pSystem;	// pointer to the CEGUI System instance
	CEGUI::Window* m_pWindow;	// pointer to the layout sheet window
	Simulation* m_pSimulation;	// pointer to the Simulation controller 
};
