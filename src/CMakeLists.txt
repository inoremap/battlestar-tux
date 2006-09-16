# Battlestar TUX
#
# Source cmake configuration file - assemble project.
#
# Copyright (C) 2006 Eliot Eshelman <battlestartux@6by9.net>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
#
## YOU DO NOT NEED TO MODIFY THIS FILE ##

SUBDIRS(lib/ftgl)

# OpenGL includes OpenGL and GLU
FIND_PACKAGE(OpenGL REQUIRED)

# SDL Simple Media Library
FIND_PACKAGE(SDL REQUIRED)
FIND_PACKAGE(SDL_image REQUIRED)

# FreeType Fonts
SET(FREETYPE_DIR ${CMAKE_MODULE_PATH})
FIND_PACKAGE(FREETYPE REQUIRED)

INCLUDE_DIRECTORIES(
	# Libraries included with Battlestar TUX
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/ftgl

	# Libraries not included with Battlestar TUX
	${FREETYPE_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
	${SDL_INCLUDE_DIR}
	${SDLIMAGE_INCLUDE_DIR}
)

LINK_DIRECTORIES(
	# Libraries included with Battlestar TUX
	${BATTLESTAR_TUX_BINARY_DIR}/src/lib/ftgl
)

SET(	BATTLESTAR_TUX_LIBRARIES

	# Libraries included with Battlestar TUX
	FTGL

	# Libraries not included with Battlestar TUX
	${FREETYPE_LIBRARY}
	${OPENGL_LIBRARY}
	${SDL_LIBRARY}
	${SDLIMAGE_LIBRARY}
)

SET(	BATTLESTAR_TUX_SOURCES

	Battle.cpp
	Config.cpp
	Displayable.cpp
	DisplayableList.cpp
	EnemyFighterList.cpp
	Explosion.cpp
	ExplosionList.cpp
	Fighter/EnemyFighter.cpp
	Fighter/Fighter.cpp
	Fighter/HeroFighter.cpp
	Fighter/Shield.cpp
	Fighter/ShieldImpact.cpp
	Fighter/ShieldImpactList.cpp
	Fighter/Weapon.cpp
	Fighter/WeaponSystem.cpp
	Fighter/Weapons/Laser.cpp
	Fighter/Weapons/Plasma.cpp
	Fighter/Weapons/Turret.cpp
	FighterAmmo.cpp
	FighterAmmoList.cpp
	Game.cpp
	Ground.cpp
	HUD.cpp
	Pulse.cpp
	Screen.cpp
	Structures/List.cpp
	Structures/ListItem.cpp
	Structures/StringArray.cpp
	TextureManager.cpp
	UI/CreditsMenu.cpp
	UI/GUI.cpp
	UI/LoadCampaignMenu.cpp
	UI/MainMenu.cpp
	UI/NewCampaignMenu.cpp
	UI/OpeningMenu.cpp
	UI/Primitives/Button.cpp
	UI/Primitives/HorizontalContainer.cpp
	UI/Primitives/HorizontalPane.cpp
	UI/Primitives/Label.cpp
	UI/Primitives/PlanetButton.cpp
	UI/Primitives/VerticalContainer.cpp
	UI/Primitives/VerticalPane.cpp
	UI/Primitives/Widget.cpp
	UI/SettingsMenu.cpp
	UI/SystemMenu.cpp
)

ADD_EXECUTABLE(	battlestarTUX
		${BATTLESTAR_TUX_SOURCES}
		main.cpp
)

ADD_EXECUTABLE(	testTUX
		${BATTLESTAR_TUX_SOURCES}
		test.cpp
)

TARGET_LINK_LIBRARIES(battlestarTUX ${BATTLESTAR_TUX_LIBRARIES})
TARGET_LINK_LIBRARIES(testTUX ${BATTLESTAR_TUX_LIBRARIES})

# Copy binary data (graphics, sounds, fonts, etc) to executable directory.
# If this is an in-source build, the copy isn't necessary.
IF( NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}" )
	EXECUTE_PROCESS(
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
		RESULT_VARIABLE NULL
		OUTPUT_VARIABLE NULL
	)
	MESSAGE( STATUS "Copying data files." )
ENDIF( NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}" )
