# Copyright (C) 2006 Eliot Eshelman <eliot@6by9.net>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AUTOMAKE_OPTIONS = subdir-objects

INCLUDES = -I/usr/include -I/usr/include/SDL -I/usr/include/freetype2 -I/usr/include/FTGL
AM_LDFLAGS = -L/usr/lib
LDADD = -lSDL -lSDL_image -lGL -lGLU -lfreetype -lftgl

bin_PROGRAMS = battlestarTUX
noinst_PROGRAMS = testTUX
battlestarTUX_SOURCES = Config.cpp \
			Config.h \
			Displayable.cpp \
			Displayable.h \
			DisplayableList.cpp \
			DisplayableList.h \
			EnemyFighterList.cpp \
			EnemyFighterList.h \
			FighterAmmo.cpp \
			FighterAmmo.h \
			FighterAmmoList.cpp \
			FighterAmmoList.h \
			Fighter/EnemyFighter.cpp \
			Fighter/EnemyFighter.h \
			Fighter/Fighter.cpp \
			Fighter/Fighter.h \
			Fighter/HeroFighter.cpp \
			Fighter/HeroFighter.h \
			Fighter/Shield.cpp \
			Fighter/Shield.h \
			Fighter/ShieldImpact.cpp \
			Fighter/ShieldImpact.h \
			Fighter/ShieldImpactList.cpp \
			Fighter/ShieldImpactList.h \
			Fighter/Weapon.cpp \
			Fighter/Weapon.h \
			Fighter/WeaponSystem.cpp \
			Fighter/WeaponSystem.h \
			Fighter/Weapons/LightLaser.cpp \
			Fighter/Weapons/LightLaser.h \
			Fighter/Weapons/MediumLaser.cpp \
			Fighter/Weapons/MediumLaser.h \
			Fighter/Weapons/HeavyLaser.cpp \
			Fighter/Weapons/HeavyLaser.h \
			Fighter/Weapons/LightPlasma.cpp \
			Fighter/Weapons/LightPlasma.h \
			Fighter/Weapons/MediumPlasma.cpp \
			Fighter/Weapons/MediumPlasma.h \
			Fighter/Weapons/HeavyPlasma.cpp \
			Fighter/Weapons/HeavyPlasma.h \
			Game.cpp \
			Game.h \
			Ground.cpp \
			Ground.h \
			GroundSegment.cpp \
			GroundSegment.h \
			HUD.cpp \
			HUD.h \
			Pulse.cpp \
			Pulse.h \
			Screen.cpp \
			Screen.h \
			Structures/List.cpp \
			Structures/List.h \
			Structures/ListItem.cpp \
			Structures/ListItem.h \
			Structures/StringArray.cpp \
			Structures/StringArray.h \
			UI/Button.cpp \
			UI/Button.h \
			UI/ButtonClickEvent.h \
			UI/Container.h \
			UI/Event.h \
			UI/EventGenerator.h \
			UI/EventListener.h \
			UI/GUI.cpp \
			UI/GUI.h \
			UI/Label.cpp \
			UI/Label.h \
			UI/Widget.cpp \
			UI/Widget.h \
			UI/VerticalContainer.cpp \
			UI/VerticalContainer.h \
			TextureManager.cpp \
			TextureManager.h \
			main.cpp

testTUX_SOURCES =	Config.cpp \
			Config.h \
			Displayable.cpp \
			Displayable.h \
			DisplayableList.cpp \
			DisplayableList.h \
			EnemyFighterList.cpp \
			EnemyFighterList.h \
			FighterAmmo.cpp \
			FighterAmmo.h \
			FighterAmmoList.cpp \
			FighterAmmoList.h \
			Fighter/EnemyFighter.cpp \
			Fighter/EnemyFighter.h \
			Fighter/Fighter.cpp \
			Fighter/Fighter.h \
			Fighter/HeroFighter.cpp \
			Fighter/HeroFighter.h \
			Fighter/Shield.cpp \
			Fighter/Shield.h \
			Fighter/ShieldImpact.cpp \
			Fighter/ShieldImpact.h \
			Fighter/ShieldImpactList.cpp \
			Fighter/ShieldImpactList.h \
			Fighter/Weapon.cpp \
			Fighter/Weapon.h \
			Fighter/WeaponSystem.cpp \
			Fighter/WeaponSystem.h \
			Fighter/Weapons/LightLaser.cpp \
			Fighter/Weapons/LightLaser.h \
			Fighter/Weapons/MediumLaser.cpp \
			Fighter/Weapons/MediumLaser.h \
			Fighter/Weapons/HeavyLaser.cpp \
			Fighter/Weapons/HeavyLaser.h \
			Fighter/Weapons/LightPlasma.cpp \
			Fighter/Weapons/LightPlasma.h \
			Fighter/Weapons/MediumPlasma.cpp \
			Fighter/Weapons/MediumPlasma.h \
			Fighter/Weapons/HeavyPlasma.cpp \
			Fighter/Weapons/HeavyPlasma.h \
			Game.cpp \
			Game.h \
			Ground.cpp \
			Ground.h \
			GroundSegment.cpp \
			GroundSegment.h \
			HUD.cpp \
			HUD.h \
			Pulse.cpp \
			Pulse.h \
			Screen.cpp \
			Screen.h \
			Structures/List.cpp \
			Structures/List.h \
			Structures/ListItem.cpp \
			Structures/ListItem.h \
			Structures/StringArray.cpp \
			Structures/StringArray.h \
			UI/Button.cpp \
			UI/Button.h \
			UI/ButtonClickEvent.h \
			UI/Container.h \
			UI/Event.h \
			UI/EventGenerator.h \
			UI/EventListener.h \
			UI/GUI.cpp \
			UI/GUI.h \
			UI/Label.cpp \
			UI/Label.h \
			UI/VerticalContainer.cpp \
			UI/VerticalContainer.h \
			UI/Widget.cpp \
			UI/Widget.h \
			TextureManager.cpp \
			TextureManager.h \
			test.cpp

SUBDIRS = data/
