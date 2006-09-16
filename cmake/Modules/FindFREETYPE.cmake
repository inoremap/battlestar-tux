#
# Find the native FREETYPE includes and library
#
# This file was written for the Scribus project:
# http://scribus.net/
#
# Modified by Eliot Eshelman to support QUIET and REQUIRED.
#

# This module defines
# FREETYPE_INCLUDE_DIR, where to find ft2build.h, ftheader.h, ...
# FREETYPE_LIBRARY, where to find the FREETYPE library.
# FREETYPE_FOUND, If false, do not try to use FREETYPE.
#

FIND_PATH( FREETYPE_INCLUDE_DIR_FT2BUILD ft2build.h
  /usr/include/
  /usr/local/include/
)

FIND_PATH( FREETYPE_INCLUDE_DIR_FTHEADER freetype/config/ftheader.h
  /usr/include/freetype2
  /usr/local/include/freetype2
)

FIND_LIBRARY( FREETYPE_LIBRARY freetype
  PATHS /usr/lib /usr/local/lib
)

IF( FREETYPE_LIBRARY AND FREETYPE_INCLUDE_DIR_FTHEADER AND FREETYPE_INCLUDE_DIR_FT2BUILD )
    SET( FREETYPE_FOUND "YES" )
    SET( FREETYPE_INCLUDE_DIR
      ${FREETYPE_INCLUDE_DIR_FT2BUILD}
      ${FREETYPE_INCLUDE_DIR_FTHEADER} )
ENDIF( FREETYPE_LIBRARY AND FREETYPE_INCLUDE_DIR_FTHEADER AND FREETYPE_INCLUDE_DIR_FT2BUILD )

IF( NOT FREETYPE_FOUND )
  IF( FREETYPE_FIND_REQUIRED )
    MESSAGE( FATAL "Cound not find Freetype2" )
  ENDIF( FREETYPE_FIND_REQUIRED )
ENDIF( NOT FREETYPE_FOUND )
