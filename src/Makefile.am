# Copyright (C) 2006 Eliot Eshelman <eliot@6by9.net>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


INCLUDES = -I/usr/include -I/usr/include/SDL
AM_LDFLAGS = -L/usr/lib
LDADD = -lSDL -lSDL_image -lGL -lGLU

bin_PROGRAMS = battlestarTUX
battlestarTUX_SOURCES = Displayable.cpp Displayable.h EnemyFighter.cpp EnemyFighter.h EnemyFighterList.cpp EnemyFighterList.h Fighter.cpp Fighter.h FighterAmmo.cpp FighterAmmo.h FighterAmmoList.cpp FighterAmmoList.h Game.cpp Game.h GfxUtils.cpp GfxUtils.h Ground.cpp Ground.h GroundSegment.cpp GroundSegment.h HUD.cpp HUD.h ListItem.cpp ListItem.h Screen.cpp Screen.h main.cpp
SUBDIRS = data/
