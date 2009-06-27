/* Battlestar TUX
 * Copyright (C) 2008-2009 Eliot Eshelman <battlestartux@6by9.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <Ogre.h>

#include "HexShip.h"


HexShip::HexShip(const Ogre::String& name, const Ogre::Vector3& pos) {
    coreCell = new HexCell(name + "CoreCell", pos);
}

HexShip::~HexShip() {
    delete coreCell;
}


void HexShip::update( unsigned long lTimeElapsed ) {
}


void HexShip::applyCentralImpulse(const Ogre::Vector3& impulse) {
    assert(coreCell);
    coreCell->applyCentralImpulse(impulse);
}

