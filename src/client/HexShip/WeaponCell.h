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


#ifndef WeaponCell_H
#define WeaponCell_H

#include <string.h>

#include "HexCell.h"


/** Weapons are available in various flavors.  We must able to tell them apart.
 */
enum WeaponCellType {
    BEAM_WEAPON,    // Laser beams, lightning, neutron beams, etc.
    BOLT_WEAPON     // Plasma balls, nanites, mines, etc.
};


/** Weapons are destructive elements of the game.
 *
 * Each weapon inherits from WeaponCell and defines its own special behavior.
 * Some weapon types, such as BOLT, generate child objects (projectiles), while
 * others operate without creating additional objects.  Weapons do participate
 * in collisions - either through ray casting or dynamics.
 */
class WeaponCell : public HexCell {
public:
    /** Create new WeaponCell
     *
     * @param name Unique name of cell.
     * The cell's Ogre::SceneNode's name is name+"Node".
     * @param mass Mass of this cell (kg).
     * @param hitPoints Maximum possible hitpoints this cell can sustain.
     * @param damagePoints Amount of damage the weapon deals.
     * @param energyRequired Amount of energy needed for each fire.
     * @param restTime Amount of time the weapon must rest after each firing.
     * @param weaponType Specifies the weapon family/flavor.
     */
    WeaponCell(const std::string& name, const float mass, const float hitPoints,
                const float damagePoints, const float energyRequired,
                const unsigned long restTime, const WeaponCellType weaponType);

    /// Update cell for a new frame.
    virtual void update(unsigned long lTimeElapsed);

    /// Start firing the weapon.
    virtual void startFiring() { bFiring = true; }

    /// Stop firing the weapon.
    virtual void stopFiring() { bFiring = false; }

    /// Get weapon type.
    WeaponCellType getWeaponCellType() const { return mWeaponCellType; }

    /// Set the current point for the ship to target.
    void setTargetPoint(const Ogre::Vector3& point) { mTargetPoint = point; }

    /// Get the current point the ship is targeting.
    const Ogre::Vector3& getTargetPoint() const { return mTargetPoint; }

protected:
    WeaponCell();
    WeaponCell(const WeaponCell&);
    WeaponCell& operator=(const WeaponCell&);

    /// The actual activation of the weapon - consume energy and do damage.
    virtual void activateWeapon() = 0;

    /// Type of weapon.
    WeaponCellType mWeaponCellType;

    /** Amount of damage the weapon deals.
     *
     * For discrete weapons (e.g. plasma bursts), this equates to the damage
     * dealt by each bolt of plasma.
     *
     * For point weapons (e.g. laser), this equates to the damage dealt during
     * each second of contact with the target.
     */
    float mDamagePoints;

    /** Amount of energy needed for each fire.
     *
     * For discrete weapons (e.g. plasma bursts), this equates to the energy
     * to generate each bolt of plasma.
     *
     * For point weapons (e.g. laser), this equates to the energy required
     * for each second the weapon is fired.
     */
    float mEnergyRequired;

    /// Amount of time the weapon must rest after each firing.
    unsigned long mRestTime;

    /// How long the weapon has been resting since the last fire.
    unsigned long mTotalRestedTime;

    /// Is the weapon currently set to fire?
    bool bFiring;

    /** Is the weapon currently energized?
     *
     * For bolt weapons, this is unlikely to ever be true (the weapon is done
     * being energized as soon as the bold leaves).
     *
     * For point weapons, this is true until the beam has ceased.
     */
    bool bEnergized;

    /// Target location - cell will point weapons towards this point.
    Ogre::Vector3 mTargetPoint;
};


#endif

