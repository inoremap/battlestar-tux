# Battlestar TUX
#
# btOgre cmake configuration file - assemble project.
#
# Copyright (C) 2009 Eliot Eshelman <battlestartux@6by9.net>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

SET(	BTOGRE_SOURCES
	BtOgre.cpp
)

ADD_LIBRARY(BTOGRE ${BTOGRE_SOURCES})

TARGET_LINK_LIBRARIES(BTOGRE)
