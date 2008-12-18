#
# Find the native OGRE includes and library
#

# This module defines
# OGRE_INCLUDE_DIR, where to find Ogre.h
# CEGUI_INCLUDE_DIR, where to find CEGUI.h
# OGRE_LIBRARY, where to find the OGRE library.
# CEGUI_LIBRARY, where to find the CEGUI library.
# OGRE_FOUND, If false, do not try to use OGRE.
#

FIND_PATH( OGRE_INCLUDE_DIR Ogre.h
  /usr/include/
  /usr/include/OGRE/
  /usr/local/include/
  /usr/local/include/OGRE/
)

FIND_PATH( CEGUI_INCLUDE_DIR CEGUI.h
  /usr/include/
  /usr/include/CEGUI/
  /usr/local/include/
  /usr/local/include/CEGUI/
)

FIND_LIBRARY( OGRE_LIBRARY OgreMain
  PATHS /usr/lib /usr/local/lib /usr/local/lib/OGRE
)
FIND_LIBRARY( CEGUI_LIBRARY CEGUIBase
  PATHS /usr/lib /usr/local/lib
)
FIND_LIBRARY( CEGUIRENDERER_LIBRARY CEGUIOgreRenderer
  PATHS /usr/lib /usr/local/lib
)

IF( OGRE_LIBRARY AND CEGUI_LIBRARY AND OGRE_INCLUDE_DIR AND CEGUI_INCLUDE_DIR )
    SET( OGRE_FOUND "YES" )
    SET( OGRE_INCLUDE_DIR
      ${OGRE_INCLUDE_DIR} )
	SET( CEGUI_INCLUDE_DIR
      ${CEGUI_INCLUDE_DIR} )
ENDIF( OGRE_LIBRARY AND CEGUI_LIBRARY AND OGRE_INCLUDE_DIR AND CEGUI_INCLUDE_DIR )

IF( NOT OGRE_FOUND )
  IF( OGRE_FIND_REQUIRED )
    MESSAGE( FATAL "Cound not find OGRE and/or CEGUI" )
  ENDIF( OGRE_FIND_REQUIRED )
ENDIF( NOT OGRE_FOUND )
