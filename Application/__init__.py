# Copyright (c) 2011 Eliot Eshelman
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.
###############################################################################

import logging
import ogre.renderer.OGRE as ogre
import ogre.io.OIS as OIS
import ogre.gui.CEGUI as CEGUI

import EntitySystem.SystemManager as SystemManager
import EntitySystem.EntityManager as EntityManager

class EventListener(ogre.FrameListener, ogre.WindowEventListener,
                    OIS.MouseListener, OIS.KeyListener, OIS.JoyStickListener):
    """
    This class handles all our ogre and OIS events (mouse/keyboard/joystick)
    depending on how you initialize this class. All events are handled
    using callbacks (buffered input).
    """

    def __init__(self, render_window, entity_system_manager,
                 buffer_mouse=True,
                 buffer_keys=True,
                 buffer_joystick=False):
        # Initialize the various listener classes we are a subclass from
        ogre.FrameListener.__init__(self)
        ogre.WindowEventListener.__init__(self)
        OIS.MouseListener.__init__(self)
        OIS.KeyListener.__init__(self)
        OIS.JoyStickListener.__init__(self)

        self.quitApplication = False
        """Set to True when the application should exit."""

        self.renderWindow = render_window
        self.entitySystemManager = entity_system_manager
        # Listen for window close events.
        ogre.WindowEventUtilities.addWindowEventListener(self.renderWindow, self)
        # Create the inputManager using the supplied renderWindow.
        windowHnd = self.renderWindow.getCustomAttributeInt("WINDOW")
        self.inputManager = OIS.createPythonInputSystem([("WINDOW", str(windowHnd))])

        self.mouse = None
        self.keyboard = None
        self.joystick = None

        # Attempt to get the mouse/keyboard/joystick input objects:
        try:
            if buffer_mouse:
                self.mouse = self.inputManager.createInputObjectMouse(
                                    OIS.OISMouse, True)
                self.mouse.setEventCallback(self)

            if buffer_keys:
                self.keyboard = self.inputManager.createInputObjectKeyboard(
                                    OIS.OISKeyboard, True)
                self.keyboard.setEventCallback(self)

            if buffer_joystick:
                self.joystick = self.inputManager.createInputObjectJoyStick(
                                    OIS.OISJoyStick, True)
                self.joystick.setEventCallback(self)

        except Exception, e:
            logging.exception("Unable to create keyboard/mouse/joystick object.", e)
            raise e

    def __del__ (self):
        if self.keyboard is not None:
            self.inputManager.destroyInputObjectKeyboard(self.keyboard)
        if self.mouse is not None:
            self.inputManager.destroyInputObjectMouse(self.mouse)
        if self.joystick is not None:
            self.inputManager.destroyInputObjectJoyStick(self.joystick)
        OIS.InputManager.destroyInputSystem(self.inputManager)
        self.inputManager = None

        ogre.WindowEventUtilities.removeWindowEventListener(self.renderWindow, self)
        self.windowClosed(self.renderWindow)

    def frameRenderingQueued(self, evt):
        """ 
        Called before a frame is displayed - handles events.
        Capture any buffered events and call any required callback functions.

        Returning False exits the application (render loop stops).
        """
        if self.keyboard:
            self.keyboard.capture()
        if self.mouse:
            self.mouse.capture()
        if self.joystick:
            self.joystick.capture()
            # # joystick test
            # axes_int = self.joystick.getJoyStickState().mAxes
            # axes = []
            # for i in axes_int:
            #    axes.append(i.abs)
            # print axes

        # Update all Entity Systems
        self.entitySystemManager.game_step(evt.timeSinceLastFrame)

        return not self.quitApplication


    ### Window Event Listener callbacks ###
    def windowResized(self, renderWindow):
        """Called when a window is resized."""
        pass

    def windowClosed(self, renderWindow):
        """Called when a window is closed."""
        # Only exit the application if the window which created OIS is closed.
        if(renderWindow == self.renderWindow):
            self.quitApplication = True


    ### Mouse Listener callbacks ###
    def mouseMoved(self, evt):
        """Pass the location of the mouse pointer over to CEGUI."""
        CEGUI.System.getSingleton().injectMouseMove(evt.get_state().X.rel,
                                                    evt.get_state().Y.rel)
        return True

    def mousePressed(self, evt, id_):
        """Convert any mouse button press events and forward them to CEGUI."""
        CEGUI.System.getSingleton().injectMouseButtonDown(self.convertButton(id_))
        return True

    def mouseReleased(self, evt, id_):
        """Convert any mouse button release events and forward them to CEGUI."""
        CEGUI.System.getSingleton().injectMouseButtonUp(self.convertButton(id_))
        return True

    def convertButton(self, ois_id):
        """Convert OIS mouse button events to CEGUI button events."""
        if ois_id == OIS.MB_Left:
            return CEGUI.LeftButton
        elif ois_id == OIS.MB_Right:
            return CEGUI.RightButton
        elif ois_id == OIS.MB_Middle:
            return CEGUI.MiddleButton
        else:
            return CEGUI.LeftButton


    ### Key Listener callbacks ###
    def keyPressed(self, evt):
        """Process any keyboard key presses."""
        if evt.key == OIS.KC_ESCAPE:
            self.quitApplication = True
        else:
            print("Key pressed: ", evt.key)
        return True

    def keyReleased(self, evt):
        """Process any keyboard key releases."""
        print("Key released: ", evt.key)
        return True


    ### Joystick Listener callbacks ###
    def buttonPressed(self, evt, id_):
        """Process any joystick button presses."""
        return True

    def buttonReleased(self, evt, id_):
        """Process any joystick button releases."""
        return True

    def axisMoved(self, evt, id_):
        """Process any joystick movements."""
        return True


app_title = "Battlestar T.U.X."

entity_manager = None
system_manager = None

ogre_root = None
ogre_render_window = None
ogre_event_listener = None

cegui_renderer = None
cegui_system = None


def go():
    createRoot()
    defineResources()
    setupRenderSystem()
    createRenderWindow()
    initializeResourceGroups()
    createEntitySystem()
    setupScene()
    createFrameListener()
    setupCEGUI()
    startRenderLoop()
    cleanUp()

def createRoot():
    """Create OGRE Root object."""
    global ogre_root
    ogre_root = ogre.Root()

def defineResources():
    """Parse OGRE resources.cfg file."""
    # Read the resources.cfg file and add all resource locations in it
    cf = ogre.ConfigFile()
    cf.load("resources.cfg")
    seci = cf.getSectionIterator()
    while seci.hasMoreElements():
        secName = seci.peekNextKey()
        settings = seci.getNext()

        for item in settings:
            typeName = item.key
            archName = item.value
            ogre.ResourceGroupManager.getSingleton().addResourceLocation(
                                             archName, typeName, secName)

def setupRenderSystem():
    """Load the renderer (e.g. OpenGL) or present a menu of options."""
    # Show the config dialog if we don't yet have an ogre.cfg file
    if not ogre_root.restoreConfig() and not ogre_root.showConfigDialog():
        logging.critical("User canceled OGRE config dialog!")
        raise Exception("User canceled OGRE config dialog!")

def createRenderWindow():
    """Create the main OGRE window."""
    ogre_root.initialise(True, app_title)

def initializeResourceGroups():
    """Initialize all the resources."""
    ogre.TextureManager.getSingleton().setDefaultNumMipmaps(5)
    ogre.ResourceGroupManager.getSingleton().initialiseAllResourceGroups()

def createEntitySystem():
    """Initialize the Entity/Component/System managers."""
    global entity_manager
    global system_manager

    entity_manager = EntityManager.EntityManager()
    """EntityManager provides access to all Entity data."""

    system_manager = SystemManager.SystemManager()
    """SystemManager oversees all the systems as they operate on Component data."""

def setupScene():
    """Create the initial scene (first items to appear)."""
    global ogre_render_window
    ogre_render_window = ogre_root.getAutoCreatedWindow()
    scene_manager = ogre_root.createSceneManager(ogre.ST_GENERIC,
                                                     "Default SceneManager")
    camera = scene_manager.createCamera("Camera")
    ogre_root.getAutoCreatedWindow().addViewport(camera)

    camera.setPosition(ogre.Vector3(0, 0, -100))
    camera.lookAt(ogre.Vector3(0, 0, 0))

    scene_manager.setAmbientLight(ogre.ColourValue(0.7, 0.7, 0.7))
    scene_manager.setFog(ogre.FOG_EXP, ogre.ColourValue(1, 1, 1), 0.0002)
    light = scene_manager.createLight('lightMain')
    light.setPosition(ogre.Vector3(20, 80, 50))

    root_node = scene_manager.getRootSceneNode()

    ogre_entity = scene_manager.createEntity('Cell', 'HexCell.mesh')
    ogre_node = root_node.createChildSceneNode('nodeOgre')
    ogre_node.setPosition(ogre.Vector3(0, 0, 0))
    ogre_node.attachObject(ogre_entity)

def createFrameListener():
    """Initialize event listener for window and user-input events."""
    global ogre_event_listener
    ogre_event_listener = EventListener(ogre_render_window, system_manager)
    ogre_root.addFrameListener(ogre_event_listener)

def setupCEGUI():
    """Initialize CEGUI - application menus."""
    global cegui_renderer
    global cegui_system
    cegui_renderer = CEGUI.OgreRenderer.bootstrapSystem()
    cegui_system = CEGUI.System.getSingleton()
    CEGUI.SchemeManager.getSingleton().create("TaharezLookSkin.scheme")
    cegui_system.setDefaultMouseCursor("TaharezLook", "MouseArrow")
    cegui_system.setDefaultFont("BlueHighway-12")

    # Uncomment the following to read in a CEGUI sheet (from CELayoutEditor)
    # 
    # mainSheet = CEGUI.WindowManager.getSingleton().loadWindowLayout("myapplication.layout")
    # cegui_system.setGUISheet(mainSheet)

def startRenderLoop():
    """Begin rendering - will continue until interrupted."""
    ogre_root.startRendering()

def cleanUp():
    """Halt and delete resources."""
    global cegui_system
    global cegui_renderer
    global ogre_event_listener
    global ogre_root

    logging.info("Shutting down and cleaning up resources.")
    logging.debug("Deleting CEGUI")
    del cegui_system
    del cegui_renderer
    logging.debug("Deleting OIS/OGRE Listener")
    del ogre_event_listener
    logging.debug("Deleting OGRE")
    del ogre_root

