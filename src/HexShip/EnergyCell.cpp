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


#include "EnergyCell.h"


EnergyCell::EnergyCell(const std::string& name, const float mass, const float hitPoints,
                        const float generationRate, const float energyStorage) :
    mGenerationRate(generationRate),
    mMaxEnergyStorage(energyStorage),
    mEnergyStorage(0),
    HexCell(name, mass, hitPoints)
{
}


void EnergyCell::update(unsigned long lTimeElapsed) {
    // All the energy generated this frame will be stored.
    // Any remaining energy is lost.
    mEnergyStorage += mGenerationRate * (lTimeElapsed/1000);
    if(mEnergyStorage > mMaxEnergyStorage)
        mEnergyStorage = mMaxEnergyStorage;
}


float EnergyCell::getEnergy(const float energyNeeded) {
    float available = 0;

    // The needed energy will be taken from storage.
    if(mEnergyStorage >= energyNeeded) {
        mEnergyStorage -= energyNeeded;
        available = energyNeeded;
    }
    else {
        available = mEnergyStorage;
        mEnergyStorage = 0;
    }

    return available;
}


float EnergyCell::storeEnergy(const float energyIn) {
    float stored = 0;

    // Put as much energy as possible into storage.
    if((mEnergyStorage + energyIn) <= mMaxEnergyStorage) {
        mEnergyStorage += energyIn;
        stored = energyIn;
    }
    else {
        stored = mMaxEnergyStorage - mEnergyStorage;
        mEnergyStorage = mMaxEnergyStorage;
    }

    return stored;
}


