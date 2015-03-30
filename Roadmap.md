#summary Project Development Roadmap
#labels Phase-Requirements,Phase-Design

It seems to be easy to get off track when brainstorming improvements.  Keep in mind that while the game may have RPG, strategy, and 4X elements, it is primarily a 2.5D scrolling shooter.  Many of the really cool features listed here can't be done until the physics and basic gameplay are solid.

The goal is a fairly immersive game with exciting action and decent 4X (eXplore, eXpand, eXploit and eXterminate) elements.  The scrolling shooter aspect dominates the initial gameplay, but as play progresses the player will have to participate in 4X activities to remain competitive.  This is where the addiction can come in: an unlimited universe to explore and conquer.  Of course, the enemy have already conquered most of it, so the player has a deal of work to do.


## Conventions ##
In order to minimize confusion between units of measurement, all classes should make use of the same "order of magnitude" when dealing with measurements (e.g. one class shouldn't use grams while the others use kilograms).

It's important that the units used correlate with real world values, because modifying existing formulas just leads to bugs and confusion.  For example, the orbital radius of a planet should be a number that would be possible in a real solar system.  The algorithm that calculates the orbital velocity of that planet can then use established astronomical formulas, without any strange, customized alterations.

**Do not** use frame numbers as units of time!  This ends up causing all sorts of trouble when frames are skipped, or when we decide to change the game's default frame rate.

  * Distance: meters
  * Mass: kilograms
  * Temperature: kelvin
  * Energy: joules
  * Rotation: degrees
  * Rotational Velocity: degrees/sec
  * Time: seconds


## Release Roadmap ##

0.0.X: **Current Status**
  * Mostly unplayable game.  Basic elements (2.5D scrolling shooter, universe overview, simple menus) taking shape.  Integration with external libraries (OGRE, BulletPhysics, OpenAL, etc).  These releases will not be tagged in subversion.

0.1.0:
  * First playable release.  Although much of the richer gameplay experience will be missing, players can at least shoot a few enemies and possibly even run a small campaign.
    * Robust CMake Build System
      * Resource and library dependencies need to be flexible - not hardcoded
      * No ridiculously non-portable code
    * GUI in place (CEGUI)
      * Opening Menu
      * Credits Screen
  * HUD
    * Pause Menu
    * Basic, Stable Game Engine
      * Robust collision detection
      * Stable physics that fit gameplay and "feel" fun
      * Basic fighter and weapon entities
    * Simple Control Interface

0.2.0:
  * Expansion of shooter.  Game elements such as fighters, weapons, ammo and explosions are no longer defined at compile time.  Other game elements moved out of code, as well.
    * Save Game State:
      * Save/Load game objects using lightweight serialization.  This will allow objects to be sent over the network in later releases.
    * Modular Units
      * Eventually, everything needs to be procedural.  Units, weapons and ammo need to be designed with this in mind.  We need clearly defined orthogonality between game objects - this facilitates computer generated content being dropped into the game.  Even if each "class" or "genre" of unit has to be hand written, the player needs to have freedom to customize/expand the units.
      * Planets, systems and enemy(s) also need to be expandable.
    * Events / Event Listeners
      * Sounds, explosions and other game necessities will need to be created at the proper times.

0.3.0:
  * Online, Persistent Universe
    * Not all games should be MMO, but it doesn't hurt to introduce a social aspect to a game, if possible/practical.  Persistent objects/scenarios introduce a lot of additional capabilities and gameplay options (such as players sharing accomplishments/territories).
    * A simple starting point should be possible: combat does not need to be multiplayer from the start if other parts of the gameplay are shared between players (the independent actions of two players at different locations will have larger-scale implications).
    * All elements will be loaded from a central database; progress of players will be public.

0.4.0:
  * Expansion of universe.  A well crafted, dynamic, entirely procedurally generated universe is not an easy task.  Now build one...
    * Resources need to be gathered by the player (4X element)
    * Player must vie for control of systems and galaxies
      * Although the procedural creation of a galaxy seems straightforward, keeping track of the status of the galaxy after its creation does not seem as trivial.


## Errata ##

  * Custom GPU shaders may be added during any phase of the roadmap, thanks to OGRE's flexibility.  Stunning visuals have always been a goal of the project - it's just debatable what level of visuals will be possible given the current manpower.  Pre-built OGRE materials may get us most of the way there.

  * Production quality textures, sound effects and soundtracks will be accepted as soon as they are available.  The "development" textures and sounds may actually detract a lot from the game.  Potential players might be so turned off by the lousy screenshots that they never even try the game.

&lt;wiki:gadget url="http://www.ohloh.net/p/43668/widgets/project\_basic\_stats.xml" height="220"  border="1" title="Battlestar T.U.X. Statistics" /&gt;