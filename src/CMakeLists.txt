# Battlestar TUX
#
# Source cmake configuration file - assemble project.
#
# Copyright (C) 2006-2010 Eliot Eshelman <battlestartux@6by9.net>
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
    client
    #server      -- not until server code in place
	lib/btOgre
	lib/bullet
    lib/procedural
    lib/tinyxml
)


INCLUDE_DIRECTORIES(
	# Libraries included with Battlestar TUX
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/btOgre
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/procedural
	# Libraries that make up Bullet Physics
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/bullet/src
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/bullet/src/BulletDynamics
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/bullet/src/BulletDynamics/ConstraintSolver
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/bullet/src/BulletCollision
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/bullet/src/LinearMath
    # TinyXML library
	${BATTLESTAR_TUX_SOURCE_DIR}/src/lib/tinyxml

	# Libraries not included with Battlestar TUX
	${OGRE_INCLUDE_DIR}
	${CEGUI_INCLUDE_DIR}
	${OIS_INCLUDE_DIR}
)

LINK_DIRECTORIES(
	# Libraries included with Battlestar TUX
	${BATTLESTAR_TUX_BINARY_DIR}/src/lib/btOgre
	${BATTLESTAR_TUX_BINARY_DIR}/src/lib/bullet
	${BATTLESTAR_TUX_BINARY_DIR}/src/lib/procedural
	${BATTLESTAR_TUX_BINARY_DIR}/src/lib/tinyxml
)

