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

    /** Add a HexCell to this HexShip.
     *
     * @param cell Cell to add to the ship.
     * @param offset Offset (from the core cell) of this new cell.
     */
    void addHexCell(HexCell* cell, const Ogre::Vector3& offset);

    /// Add a Core HexCell to this HexShip.
    void addCoreHexCell(HexCell* cell, const Ogre::Vector3& offset);

    /** Remove a HexCell from this HexShip.
     *
     * @param cell Cell to remove from the ship.
     *
     * @remark This operation does not destroy the cell, but simply detaches
     * it from the ship.  The cell will likely slowly drift away.
     */
    void removeHexCell(HexCell* cell);

    /// Update ship (and all child objects) for a new frame.
    void update(unsigned long lTimeElapsed);

    /// HACK: forces should come from propulsion cells or object collisions.
    void applyCentralImpulse(const Ogre::Vector3& impulse);

    /// Build XML structure with ship data/attributes.
    void toXml(TiXmlElement* node) const;

    /// Get Ogre::SceneNode at center of HexShip.
    Ogre::SceneNode* getOgreNode() { return mOgreNode; }

    /// Get ship's name.
    const std::string& getName() const { return mName; }

    /// Get total ship mass.
    float getMass() const { return mMass; }

private:
    HexShip();
    HexShip(const HexShip&);
    HexShip& operator=(const HexShip&);

    /** Reevaluate and rebuild the collision hull of the HexShip.
     *
     * When the shape of the ship changes (when cells are added or removed),
     * the compound collision shape of the ship must be recreated.
     */
    void rebuildCollisionHull();

    /// Ogre node controlling this ship.
    Ogre::SceneNode *mOgreNode;

    /// Bullet object physically simulating this ship.
    btRigidBody *mHexShipRigidBody;

    /// HexShip collision shape - assembled from HexCell shapes.
    btCompoundShape *mHexShipShape;

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

