#!/usr/bin/env python
#
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

    def __init__(self, application,
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

        self.renderWindow = application.renderWindow
        self.entitySystemManager = application.entitySystemManager
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


class Application(object):

    app_title = "Battlestar T.U.X."

    def go(self):
        self.initializeLogging()
        self.createRoot()
        self.defineResources()
        self.setupRenderSystem()
        self.createRenderWindow()
        self.initializeResourceGroups()
        self.createEntitySystem()
        self.setupScene()
        self.createFrameListener()
        self.setupCEGUI()
        self.startRenderLoop()
        self.cleanUp()

    def initializeLogging(self):
        """Set up logging of in-game info/warnings/errors.
        All log messages are written to file and to the console, but the file
        and the console may have different log levels (e.g. DEBUG vs INFO).
        
        OGRE and CEGUI automatically create their own logs.
        """
        logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s %(levelname)-8s %(message)s',
                    filename='BattlestarTUX.log',
                    filemode='w')
        console = logging.StreamHandler()
        console.setLevel(logging.DEBUG)
        # set a format which is simpler for console use
        formatter = logging.Formatter('[battlestar-tux]: %(levelname)-8s %(message)s')
        console.setFormatter(formatter)
        logging.getLogger('').addHandler(console)
        logging.info(Application.app_title + " initialization...")

    def createRoot(self):
        """Create OGRE Root object."""
        self.root = ogre.Root()

    def defineResources(self):
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

    def setupRenderSystem(self):
        """Load the renderer (e.g. OpenGL) or present a menu of options."""
        # Show the config dialog if we don't yet have an ogre.cfg file
        if not self.root.restoreConfig() and not self.root.showConfigDialog():
            logging.critical("User canceled OGRE config dialog!")
            raise Exception("User canceled OGRE config dialog!")

    def createRenderWindow(self):
        """Create the main OGRE window."""
        self.root.initialise(True, self.app_title)

    def initializeResourceGroups(self):
        """Initialize all the resources."""
        ogre.TextureManager.getSingleton().setDefaultNumMipmaps(5)
        ogre.ResourceGroupManager.getSingleton().initialiseAllResourceGroups()

    def createEntitySystem(self):
        self.entityManager = EntityManager.EntityManager()
        """EntityManager provides access to all Entity data."""

        self.entitySystemManager = SystemManager.SystemManager()
        """SystemManager oversees all the systems as they operate on Component data."""

    def setupScene(self):
        """Create the initial scene (first items to appear)."""
        self.renderWindow = self.root.getAutoCreatedWindow()
        self.sceneManager = self.root.createSceneManager(ogre.ST_GENERIC,
                                                         "Default SceneManager")
        self.camera = self.sceneManager.createCamera("Camera")
        self.viewPort = self.root.getAutoCreatedWindow().addViewport(self.camera)

        self.camera.setPosition(ogre.Vector3(0, 0, -100))
        self.camera.lookAt(ogre.Vector3(0, 0, 0))

        self.sceneManager.setAmbientLight(ogre.ColourValue(0.7, 0.7, 0.7))
        self.sceneManager.setFog(ogre.FOG_EXP, ogre.ColourValue(1, 1, 1), 0.0002)
        self.light = self.sceneManager.createLight('lightMain')
        self.light.setPosition(ogre.Vector3(20, 80, 50))

        self.rn = self.sceneManager.getRootSceneNode()

        self.entityOgre = self.sceneManager.createEntity('Cell', 'HexCell.mesh')
        self.nodeOgre = self.rn.createChildSceneNode('nodeOgre')
        self.nodeOgre.setPosition(ogre.Vector3(0, 0, 0))
        self.nodeOgre.attachObject(self.entityOgre)

    def createFrameListener(self):
        """Initialize event listener for window and user-input events."""
        self.eventListener = EventListener(self)
        self.root.addFrameListener(self.eventListener)

    def setupCEGUI(self):
        """Initialize CEGUI - application menus."""
        self.renderer = CEGUI.OgreRenderer.bootstrapSystem()
        self.system = CEGUI.System.getSingleton()
        CEGUI.SchemeManager.getSingleton().create("TaharezLookSkin.scheme")
        self.system.setDefaultMouseCursor("TaharezLook", "MouseArrow")
        self.system.setDefaultFont("BlueHighway-12")

        # Uncomment the following to read in a CEGUI sheet (from CELayoutEditor)
        # 
        # self.mainSheet = CEGUI.WindowManager.getSingleton().loadWindowLayout("myapplication.layout")
        # self.system.setGUISheet(self.mainSheet)

    def startRenderLoop(self):
        """Begin rendering - will continue until interrupted."""
        self.root.startRendering()

    def cleanUp(self):
        """Halt and delete resources."""
        logging.info("Shutting down and cleaning up resources.")
        logging.debug("Deleting CEGUI")
        del self.system
        del self.renderer
        logging.debug("Deleting OIS/OGRE Listener")
        del self.eventListener
        logging.debug("Deleting OGRE")
        del self.root


if __name__ == '__main__':
    try:
        # Run the game.
        ta = Application()
        ta.go()
    except Exception:
        logging.exception("An unexpected error occurred. Application exiting...")

    # Shut down logging - do this last so we can log any errors during shutdown.
    logging.shutdown()
