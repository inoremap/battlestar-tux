/* Battlestar TUX
 * Copyright (C) 2009 Eliot Eshelman <battlestartux@6by9.net>
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


#ifndef EnergyCell_H
#define EnergyCell_H

#include <string.h>

#include "HexCell.h"


/** EnergyCells provide the HexShip with power.  Typically, an EnergyCell can
 *  both generate and store energy for later use.
 */
class EnergyCell : public HexCell {
public:
    /** Create new EnergyCell
     *
     * @param name Unique name of cell.
     * The cell's Ogre::SceneNode's name is name+"Node".
     * @param mass Mass of this cell (kg).
     * @param hitPoints Maximum possible hitpoints this cell can sustain.
     * @param generationRate Amount of energy generated each second.
     * @param energyStorage Amount of energy which may be stored in the cell.
     * @remark generationRate may not be larger than energyStorage.  An EnergyCell will only be able to provide as much energy each second as can be stored.
     */
    EnergyCell(const std::string& name, const float mass, const float hitPoints,
                const float generationRate, const float energyStorage);

    /// Update cell for a new frame.
    void update(unsigned long lTimeElapsed);

    /* Obtain energy from the EnergyCell.
     *
     * @param energy The amount of energy needed.
     * @return The amount of energy this cell was able to provide.
     */
    float getEnergy(const float energy);

    /* Put energy into this EnergyCell for storage.
     *
     * @param energy The amount of energy to store.
     * @return The amount of energy this cell was able to store.
     */
    float storeEnergy(const float energy);

private:
    EnergyCell();
    EnergyCell(const EnergyCell&);
    EnergyCell& operator=(const EnergyCell&);

    /// Specifies how much energy is generated each second.
    float mGenerationRate;

    /// Specifies how much energy is currently stored.
    float mEnergyStorage;

    /// Specifies how much energy may be stored.
    float mMaxEnergyStorage;
};


#endif

