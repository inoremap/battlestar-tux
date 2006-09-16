# Battlestar TUX
#
# FTGL cmake configuration file - assemble project.
#
# Copyright (C) 2006 Eliot Eshelman <eliot@6by9.net>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

SET(	FTGL_SOURCES
	FTBitmapGlyph.cpp
	FTCharmap.cpp
	FTContour.cpp
	FTExtrdGlyph.cpp
	FTFace.cpp
	FTFont.cpp
	FTGLBitmapFont.cpp
	FTGLExtrdFont.cpp
	FTGLOutlineFont.cpp
	FTGLPixmapFont.cpp
	FTGLPolygonFont.cpp
	FTGLTextureFont.cpp
	FTGlyph.cpp
	FTGlyphContainer.cpp
	FTLibrary.cpp
	FTOutlineGlyph.cpp
	FTPixmapGlyph.cpp
	FTPoint.cpp
	FTPolyGlyph.cpp
	FTSize.cpp
	FTTextureGlyph.cpp
	FTVectoriser.cpp
)

ADD_LIBRARY(FTGL ${FTGL_SOURCES})

TARGET_LINK_LIBRARIES(	FTGL

			# Libraries not included with Battlestar TUX
			${FREETYPE_LIBRARY}
			${OPENGL_LIBRARY}
)

