# Battlestar TUX
#
# Top-level cmake configuration file.
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

cmake_minimum_required(VERSION 2.6)

PROJECT(BATTLESTAR_TUX)

# Include custom cmake modules.
SET(CMAKE_MODULE_PATH "${BATTLESTAR_TUX_SOURCE_DIR}/cmake/Modules")

SUBDIRS(src)
