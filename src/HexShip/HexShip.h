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


#ifndef HexShip_H
#define HexShip_H

#include <assert.h>
#include <Ogre.h>
#include <string.h>
#include <tinyxml.h>
#include <vector>

#include "HexCell.h"
#include "XmlEntity.h"

/** Spacecraft/Aircraft constructed from multiple HexCells.
 *
 * Capabilities of the ship are determined by the collective capabilities of
 * the HexCells.  Each HexCell may provide one or more capabilities, with
 * advanced HexCells providing a larger multitude of capabilities.
 */
class HexShip : public XmlEntity {
public:
    /** Create new HexShip with a single (core) HexCell.
     *
     * @param name Unique name of ship.
     * @param pos Initial position of ship.
     */
    HexShip(const std::string& name, const Ogre::Vector3& pos);

    /// Default destructor.
    ~HexShip();

    /// Update ship (and all child objects) for a new frame.
    void update(unsigned long lTimeElapsed);

    /// HACK: forces should come from propulsion cells or object collisions.
    void applyCentralImpulse(const Ogre::Vector3& impulse);

    /// Build XML structure with ship data/attributes.
    void toXml(TiXmlElement* node) const;

    /** Get Ogre::SceneNode at center of HexShip.
     *
     * @attention Since the HexShip itself is not an Ogre object, we will use
     * the Ogre node of the core HexCell when one is needed.
     */
    Ogre::SceneNode* getOgreNode() {
        assert(mCoreCell);
        return mCoreCell->getOgreNode();
    }

    /// Get total ship mass.
    float getMass() { return mMass; }

private:
    HexShip();
    HexShip(const HexShip&);
    HexShip& operator=(const HexShip&);

    /** Reference to ship's central HexCell.
     *
     * A ship will be destroyed along with its core cell.
     */
    HexCell* mCoreCell;

    /** Collection of all cells in a ship.
     *
     * @remark Although a separate reference is kept to the core cell, this cell
     * is also included in mShipCells.  The core cell often performs some of the
     * same tasks as other cells, so it will be implicitly included in ship
     * energy, propulsion updates, etc.
     */
    std::vector<HexCell*> mShipCells;

    /// Unique name of this ship.
    std::string mName;

    /// Total mass of ship, including all cells (kg).
    float mMass;
};


#endif

