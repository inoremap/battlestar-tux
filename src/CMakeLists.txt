# Battlestar TUX
#
# Source cmake configuration file - assemble project.
#
# Copyright (C) 2006-2009 Eliot Eshelman <battlestartux@6by9.net>
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


SUBDIRS(
	lib/btOgre
	lib/bullet
)


# OGRE
SET(OGRE_DIR ${CMAKE_MODULE_PATH})
FIND_PACKAGE(OGRE REQUIRED)

# OIS
SET(OIS_DIR ${CMAKE_MODULE_PATH})
FIND_PACKAGE(OIS REQUIRED)


INCLUDE_DIRECTORIES(
	# Directories in Battlestar TUX project
	${BATTLESTAR_TUX_SOURCE_DIR}/src
	${BATTLESTAR_TUX_SOURCE_DIR}/src/HexShip

	# Libraries included with Battlestar TUX
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/btOgre
	# Libraries that make up Bullet Physics
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/bullet/src
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/bullet/src/BulletDynamics
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/bullet/src/BulletCollision
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/bullet/src/LinearMath

	# Libraries not included with Battlestar TUX
	${OGRE_INCLUDE_DIR}
	${CEGUI_INCLUDE_DIR}
	${OIS_INCLUDE_DIR}
)

LINK_DIRECTORIES(
	# Libraries included with Battlestar TUX
	${BATTLESTAR_TUX_BINARY_DIR}/src/lib/btOgre
	${BATTLESTAR_TUX_BINARY_DIR}/src/lib/bullet
)

SET(	BATTLESTAR_TUX_LIBRARIES

	# Libraries included with Battlestar TUX
	BTOGRE
	# Libraries that make up Bullet Physics
	BulletDynamics
	BulletCollision
	LinearMath

	# Libraries not included with Battlestar TUX
	${OGRE_LIBRARY}
	${CEGUI_LIBRARY}
	${CEGUIRENDERER_LIBRARY}
	${OIS_LIBRARY}
)

SET(	BATTLESTAR_TUX_SOURCES

	GameManager.cpp
	GameState.cpp
	InputManager.cpp
	IntroState.cpp
	PauseState.cpp
	PhysicsManager.cpp
	PlayState.cpp
	HexShip/HexShip.cpp
)

ADD_EXECUTABLE(	battlestarTUX
		${BATTLESTAR_TUX_SOURCES}
		main.cpp
)
TARGET_LINK_LIBRARIES(battlestarTUX ${BATTLESTAR_TUX_LIBRARIES})


# Copy binary data (graphics, sounds, fonts, etc) to executable directory.
# If this is an in-source build, the copy isn't necessary.
IF( NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}" )
	EXECUTE_PROCESS(
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
		RESULT_VARIABLE NULL
		OUTPUT_VARIABLE NULL
	)
	MESSAGE( STATUS "Copying data files." )
ENDIF( NOT "${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}" )

