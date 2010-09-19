/* Battlestar TUX
 * Copyright (C) 2010 Eliot Eshelman <battlestartux@6by9.net>
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


#ifndef BoltWeaponCell_H
#define BoltWeaponCell_H

#include <btBulletDynamicsCommon.h>
#include <Ogre.h>

#include "WeaponCell.h"


/** Bolt weapons fire discrete ammunitions.
 *
 * Each bolt will have its own Ogre and Bullet object.  The collision shape is shared.
 */
class BoltWeaponCell : public WeaponCell {
public:
    /** Create new BoltWeaponCell
     *
     * @param name Unique name of cell.
     * The cell's Ogre::SceneNode's name is name+"Node".
     * @param mass Mass of this cell (kg).
     * @param hitPoints Maximum possible hitpoints this cell can sustain.
     * @param damagePoints Amount of damage the weapon deals.
     * @param energyRequired Amount of energy needed for each fire.
     * @param restTime Amount of time the weapon must rest after each firing.
     */
    BoltWeaponCell(const std::string& name, const float mass, const float hitPoints,
                const float damagePoints, const float energyRequired,
                const unsigned long restTime);
    ~BoltWeaponCell();

    /// Build sphere mesh representing weapons fire.
    void createWeaponSphere(const float r = 1, const int nRings = 16, const int nSegments = 16);

protected:
    BoltWeaponCell();
    BoltWeaponCell(const BoltWeaponCell&);
    BoltWeaponCell& operator=(const BoltWeaponCell&);

    /// The actual activation of the weapon - consume energy and do damage.
    void activateWeapon();

    /// Weapon's ammo collision shape.
    static btCollisionShape *mWeaponShape;
};


#endif

