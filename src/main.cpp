#include "Input.h"
#include "Simulation.h"

#include "Ogre.h"

// needed to be able to create the CEGUI renderer interface
#include "OgreCEGUIRenderer.h"

// CEGUI includes
#include "CEGUISystem.h"
#include "CEGUIInputEvent.h"
#include "CEGUIWindow.h"
#include "CEGUIWindowManager.h"
#include "CEGUISchemeManager.h"
#include "CEGUIFontManager.h"
#include "elements/CEGUIFrameWindow.h"

// GUI sheet handlers
#include "MainMenuDlg.h"

#if defined(WIN32)
#include "windows.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
int main (int argc, char *argv[]) {
#endif

	Ogre::Root *ogre;
	Ogre::RenderWindow *window;
	Ogre::SceneManager *sceneMgr;
	Ogre::Camera *camera;

	// fire up an Ogre rendering window. Clearing the first two (of three) params will let us 
	// specify plugins and resources in code instead of via text file
	ogre = new Ogre::Root("", "");


	// This is a VERY minimal rendersystem loading example; we are hardcoding the OpenGL 
	// renderer, instead of loading GL and D3D9. We will add renderer selection support in a 
	// future article.
	ogre->loadPlugin("RenderSystem_GL");
	Ogre::RenderSystemList *renderSystems = NULL;
	Ogre::RenderSystemList::iterator r_it;

	// we do this step just to get an iterator that we can use with setRenderSystem. In a future article
	// we actually will iterate the list to display which renderers are available. 
	renderSystems = ogre->getAvailableRenderers();
	r_it = renderSystems->begin();
	ogre->setRenderSystem(*r_it);
	ogre->initialise(false);

	// load common plugins
	ogre->loadPlugin("Plugin_CgProgramManager");		
	ogre->loadPlugin("Plugin_OctreeSceneManager");

	// load the basic resource location(s)
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
		"resource", "FileSystem", "General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
		"resource/gui.zip", "Zip", "GUI");
#if defined(WIN32)
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
		"c:\\windows\\fonts", "FileSystem", "GUI");
#endif

	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("General");
	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("GUI");

	// setup main window; hardcode some defaults for the sake of presentation
	Ogre::NameValuePairList opts;
	opts["resolution"] = "1024x768";
	opts["fullscreen"] = "false";
	opts["vsync"] = "false";

	// create a rendering window with the title "CDK"
	window = ogre->createRenderWindow("CDK", 1024, 768, false, &opts);

	// since this is basically a CEGUI app, we can use the ST_GENERIC scene manager for now; in a later article 
	// we'll see how to change this
	sceneMgr = ogre->createSceneManager(Ogre::ST_GENERIC);
	camera = sceneMgr->createCamera("camera");
	camera->setNearClipDistance(5);
    Ogre::Viewport* vp = window->addViewport(camera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

	// most examples get the viewport size to calculate this; for now, we'll just 
	// set it to 4:3 the easy way
	camera->setAspectRatio((Ogre::Real)1.333333);

	// with a scene manager and window, we can create a the GUI renderer
	CEGUI::OgreCEGUIRenderer* pGUIRenderer = new CEGUI::OgreCEGUIRenderer(
		window,							// the render window created earlier; CEGUI renders to this
		Ogre::RENDER_QUEUE_OVERLAY,		// CEGUI should render in this render queue
		false,							// put everything in the above render queue first, not last
		3000,							// this is actually unnecessary now in CEGUI -- max quads for the UI
		sceneMgr						// use this scene manager to manage the UI
	);

	// create the root CEGUI class
	CEGUI::System* pSystem = new CEGUI::System(pGUIRenderer);

	// tell us a lot about what is going on (see CEGUI.log in the working directory)
	CEGUI::Logger::getSingleton().setLoggingLevel(CEGUI::Informative);

	// use this CEGUI scheme definition (see CEGUI docs for more)
	CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLookSkin.scheme", (CEGUI::utf8*)"GUI");

	// show the CEGUI mouse cursor (defined in the look-n-feel)
	pSystem->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");

	// use this font for text in the UI
	CEGUI::FontManager::getSingleton().createFont("Tahoma-8.font", (CEGUI::utf8*)"GUI");
	pSystem->setDefaultFont((CEGUI::utf8*)"Tahoma-8");

	// load a layout from the XML layout file (you'll find this in resources/gui.zip), and 
	// put it in the GUI resource group
	CEGUI::Window* pLayout = CEGUI::WindowManager::getSingleton().loadWindowLayout("katana.layout", "", "GUI");

	// you need to tell CEGUI which layout to display. You can call this at any time to change the layout to
	// another loaded layout (i.e. moving from screen to screen or to load your HUD layout). Note that this takes
	// a CEGUI::Window instance -- you can use anything (any widget) that serves as a root window.
	pSystem->setGUISheet(pLayout);

	// this next bit is for the sake of the input handler
	unsigned long hWnd;
	// WINDOW is generic to all platforms now as of Eihort
	window->getCustomAttribute("WINDOW", &hWnd);

	// set up the input handlers
	Simulation *sim = new Simulation();

	// since the input handler deals with pushing input to CEGUI, we need to give it a pointer
	// to the CEGUI System instance to use
	InputHandler *handler = new InputHandler(pSystem, sim, hWnd);

	// put us into our "main menu" state
	sim->requestStateChange(GUI);

	// make an instance of our GUI sheet handler class
	MainMenuDlg* pDlg = new MainMenuDlg(pSystem, pLayout, sim);

	while (sim->getCurrentState() != SHUTDOWN) {
		
		handler->capture();

		// run the message pump (uncomment for Dagon)
		//Ogre::PlatformManager::getSingleton().messagePump(window);

		// run the message pump (uncomment for Eihort)
		Ogre::WindowEventUtilities::messagePump();

		ogre->renderOneFrame();
	}

	// clean up after ourselves
	delete pDlg;
	delete pSystem;
	delete pGUIRenderer;
	delete handler;
	delete sim;
	delete ogre;

	return 0;
}
