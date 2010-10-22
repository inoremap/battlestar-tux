# Battlestar TUX
#
# Procedural library cmake configuration file - assemble project.
#
# Copyright (C) 2010 Eliot Eshelman <battlestartux@6by9.net>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

SET(PRODECURAL_SOURCES
	Simplex.cpp
    Textures.cpp
)

ADD_LIBRARY(PROCEDURAL ${PROCEDURAL_SOURCES})

TARGET_LINK_LIBRARIES(PROCEDURAL)

