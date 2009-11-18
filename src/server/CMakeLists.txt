# Battlestar TUX
#
# Source cmake configuration file - assemble project.
# Builds server back-end software.
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


INCLUDE_DIRECTORIES(
	# Directories in Battlestar TUX project
	${BATTLESTAR_TUX_SOURCE_DIR}/src/server
)

SET(	BATTLESTAR_TUX_SERVER_LIBRARIES

	# Libraries included with Battlestar TUX
    # TinyXML library
    TINYXML

	# Libraries not included with Battlestar TUX
	${OIS_LIBRARY}
)

SET(	BATTLESTAR_TUX_SERVER_SOURCES

    XmlEntity.cpp
)

ADD_EXECUTABLE(	battlestarTUX-server
		${BATTLESTAR_TUX_SERVER_SOURCES}
		main.cpp
)
TARGET_LINK_LIBRARIES(battlestarTUX-server ${BATTLESTAR_TUX_SERVER_LIBRARIES})

