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
import math
import ogre.io.OIS as OIS
import ogre.gui.CEGUI as CEGUI
import ogre.physics.bullet as bullet
import ogre.renderer.OGRE as ogre
import random

import Assemblages.HexShip as HexShip
import EntitySystem
import utils.OgreBulletUtils as OgreBulletUtils

class EventListener(ogre.FrameListener, ogre.WindowEventListener,
                    OIS.MouseListener, OIS.KeyListener, OIS.JoyStickListener):
    """
    This class handles all our ogre and OIS events (mouse/keyboard/joystick)
    depending on how you initialize this class. All events are handled
    using callbacks (buffered input).
    """

    def __init__(self, render_window, bullet,
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
        self.bullet_world = bullet

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

    def frameEnded(self, evt):
        """Called at the end of a frame."""
        self.bullet_world.getDebugDrawer().frameEnded(evt)
        return True

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

        # Update Bullet Physics simulation
        self.bullet_world.stepSimulation(evt.timeSinceLastFrame, 50)
        self.bullet_world.getDebugDrawer().frameRenderingQueued(evt)
        self.bullet_world.debugDrawWorld()

        # Update all Entity Systems
        EntitySystem.game_step(evt.timeSinceLastFrame)

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

ogre_root = None
"""OGRE Root object - must be created before OGRE does anything."""

ogre_scene_manager = None
"""OGRE scene manager handles OGRE entities and objects."""

ogre_root_node = None
"""All in-game OGRE objects are descendents of this root."""

ogre_render_window = None
"""Ogre Render Window - everything is drawn here"""

ogre_event_listener = None
"""Listens for Ogre events as well as user input."""

bullet_world = None
"""Manages Bullet Physics engine."""

bullet_collision_configuration = None
bullet_dispatcher = None
bullet_broadphase = None
bullet_solver = None

bullet_debug_drawer = None
"""Allows Bullet Physics to draw collision debugging details."""

cegui_renderer = None
"""Draws GUI for CEGUI."""

cegui_system = None
"""Core CEGUI object."""


def go():
    # Inialize everything and enter main menu.
    createRoot()
    defineResources()
    setupRenderSystem()
    createRenderWindow()
    initializeResourceGroups()
    setupScene()
    initializePhysics()
    createFrameListener()
    setupCEGUI()
    startRenderLoop()

    # Window has closed.
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

def setupScene():
    """Create the initial OGRE scene (first items to appear)."""
    global ogre_scene_manager
    global ogre_render_window
    global ogre_root_node

    ogre_render_window = ogre_root.getAutoCreatedWindow()
    ogre_scene_manager = ogre_root.createSceneManager(ogre.ST_GENERIC,
                                                     "Default SceneManager")
    camera = ogre_scene_manager.createCamera("Camera")
    ogre_root.getAutoCreatedWindow().addViewport(camera)

    camera.setPosition(ogre.Vector3(25, 25, 100))
    camera.lookAt(ogre.Vector3(0, 0, 0))
    camera.nearClipDistance = 10

    ogre_scene_manager.setAmbientLight(ogre.ColourValue(0.7, 0.7, 0.7))
    ogre_scene_manager.setFog(ogre.FOG_EXP, ogre.ColourValue(1, 1, 1), 0.0002)
    light = ogre_scene_manager.createLight('lightMain')
    light.setPosition(ogre.Vector3(10, 10, 10))

    ogre_root_node = ogre_scene_manager.getRootSceneNode()

def initializePhysics():
    """Start the Bullet Physics engine."""
    global bullet_world
    global bullet_debug_drawer
    global bullet_collision_configuration
    global bullet_dispatcher
    global bullet_broadphase
    global bullet_solver

    bullet_collision_configuration = bullet.get_btDefaultCollisionConfiguration()
    bullet_dispatcher = bullet.get_btCollisionDispatcher1(bullet_collision_configuration)
    #bullet_broadphase = bullet.btDbvtBroadphase()
    bullet_broadphase = bullet.btAxisSweep3(
                                    bullet.btVector3(-10000, -10000, -10000),
                                    bullet.btVector3(10000, 10000, 10000),
                                    1024)
    bullet_solver = bullet.btSequentialImpulseConstraintSolver()

    bullet_world = bullet.btDiscreteDynamicsWorld(
                                    bullet_dispatcher,
                                    bullet_broadphase,
                                    bullet_solver,
                                    bullet_collision_configuration)
    bullet_world.setGravity(bullet.btVector3(0, -10, 0))
    bullet_world.getDispatchInfo().m_enableSPU = True

    bullet_debug_drawer = OgreBulletUtils.DebugDrawer(ogre_scene_manager)
    bullet_world.setDebugDrawer(bullet_debug_drawer)
    bullet_world.getDebugDrawer().setDebugMode(
                                       bullet.btIDebugDraw.DBG_DrawWireframe |
                                       bullet.btIDebugDraw.DBG_DrawAabb
                                       #bullet.btIDebugDraw.DBG_DrawContactPoints
                                       #bullet.btIDebugDraw.DBG_NoDebug
                                               )

def createFrameListener():
    """Initialize event listener for window and user-input events."""
    global ogre_event_listener
    ogre_event_listener = EventListener(ogre_render_window, bullet_world)
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

    # Create an infinite non-moving collision plane.
    # TODO: limit physics world to plane size  
    plane = OgreBulletUtils.CollisionObject(bullet_world)
    plane.mShape = bullet.btStaticPlaneShape(bullet.btVector3(0, 1, 0), 0)
    plane.setMass(0.0)
    plane.setInertia(bullet.btVector3(0, 0, 0))
    plane.setTransform(bullet.btVector3(0, 0, 0))
    plane.setMotion(None)
    #XXX: self.collisionObjects.append(plane)
    assert(plane.mRigidBody.getFlags() == plane.mRigidBody.getFlags() &
           bullet.btCollisionObject.CollisionFlags.CF_STATIC_OBJECT)

    # Create ships - arrange in a circle.
    for i in range(0, 360, 360 / 6):
        HexShip.create((
                       math.sin(math.radians(i)) * 8,
                       20,
                       math.cos(math.radians(i)) * 8,
                       ))

    # Begin running game
    ogre_root.startRendering()

def cleanUp():
    """Halt and delete resources."""
    global cegui_system
    global cegui_renderer
    global bullet_debug_drawer
    global bullet_world
    global bullet_solver
    global bullet_broadphase
    global bullet_dispatcher
    global bullet_collision_configuration
    global ogre_event_listener
    global ogre_root

    logging.info("Shutting down and cleaning up resources.")

    logging.debug("Deleting CEGUI")
    del cegui_system
    del cegui_renderer

    logging.debug("Deleting Bullet Physics")
    # TODO: Clean up collision objects
    del bullet_debug_drawer
    del bullet_world
    del bullet_solver
    del bullet_broadphase
    del bullet_dispatcher
    del bullet_collision_configuration

    logging.debug("Deleting OIS/OGRE Listener")
    del ogre_event_listener

    logging.debug("Deleting OGRE")
    del ogre_root

