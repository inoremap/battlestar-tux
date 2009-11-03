#
# Find the native OIS includes and library
#

# This module defines
# OIS_INCLUDE_DIR, where to find OIS.h
# OIS_LIBRARY, where to find the OIS library.
# OIS_FOUND, If false, do not try to use OIS.
#

FIND_PATH( OIS_INCLUDE_DIR OIS.h
  /usr/include/
  /usr/include/OIS/
  /usr/local/include/
  /usr/local/include/OIS/
)

FIND_LIBRARY( OIS_LIBRARY OIS
  PATHS /usr/lib /usr/local/lib /usr/local/lib/OIS
)

IF( OIS_LIBRARY AND OIS_INCLUDE_DIR )
    SET( OIS_FOUND "YES" )
    SET( OIS_INCLUDE_DIR
      ${OIS_INCLUDE_DIR} )
ENDIF( OIS_LIBRARY AND OIS_INCLUDE_DIR )

IF( NOT OIS_FOUND )
  IF( OIS_FIND_REQUIRED )
    MESSAGE( FATAL "Cound not find OIS" )
  ENDIF( OIS_FIND_REQUIRED )
ENDIF( NOT OIS_FOUND )
