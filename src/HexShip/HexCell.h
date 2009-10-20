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


#ifndef HexCell_H
#define HexCell_H

#include <btBulletDynamicsCommon.h>
#include <Ogre.h>
#include <string.h>
#include <tinyxml.h>

#include "XmlEntity.h"

class HexShip;


/** HexCells are the basic building blocks of a HexShip craft.
 *
 * Each HexCell can provide one or more capabilities, and is visually displayed
 * via an Ogre::SceneNode.  The cell is also linked to a Bullet collision object
 * and added to the Bullet dynamic physics simulation.
 */
class HexCell : public XmlEntity {
public:
    /** Create new HexCell
     *
     * @param name Unique name of cell.
     * The cell's Ogre::SceneNode's name is name+"Node".
     * @param mass Mass of this cell (kg).
     * @param hitPoints Maximum possible hitpoints this cell can sustain.
     */
    HexCell(const std::string& name, const float mass, const float hitPoints);

    /// Default destructor.
    ~HexCell();

    /// Update cell for a new frame.
    virtual void update(unsigned long lTimeElapsed) { }

    /** Apply damage to this cell.
     *
     * @param hitpoints The amount of damage applied to this cell.
     */
    virtual void damage(const float hitpoints);

    /** This cell has been destroyed.  Queue any explosions and destructive
     * events that follow the destruction of the cell.
     */
    virtual void destroy();

    /** Attach this HexCell to a HexShip.  Indicates that this cell should
     * cease managing its own movement and collisions.
     *
     * @param ship The HexShip this cell has been attached to.
     * @param offset Indicates the offset (from the core cell) of this cell.
     */
    void attachCell(HexShip* ship, const Ogre::Vector3 offset);

    /** Separate this HexCell from its HexShip.  Requires the HexCell to create
     * its own btRigidBody to manage collisions and movement.
     */
    void separateCell();

    /// Build XML structure with cell data/attributes.
    void toXml(TiXmlElement* node) const;

    /// Get the Ogre::SceneNode representing this cell.
    Ogre::SceneNode* getOgreNode() { return mOgreNode; }

    /// Get (and create, if necessary) the HexCell Bullet collision object.
    static btCollisionShape* getCollisionShapePtr();

    /// Get cell's name.
    const std::string& getName() const { return mName; }

    /// Get cell's mass.
    float getMass() const { return mMass; }

    /// Get cell's maximum hitpoints.
    float getMaxHp() const { return mMaxHp; }

    /// Get cell's current hitpoints.
    float getHp() const { return mHp; }

    /// Get this cell's offset within the HexShip.
    const Ogre::Vector3& getOffset() const { return mOffset; }

protected:
    HexCell();
    HexCell(const HexCell&);
    HexCell& operator=(const HexCell&);

    /// Ogre object visually representing this cell.
    Ogre::Entity *mOgreEntity;

    /// Ogre node controlling this cell.
    Ogre::SceneNode *mOgreNode;

    /** Bullet object physically simulating this cell.
     *
     * @attention When this HexCell is part of a larger HexShip, the ship will
     * manage all collisions and motion states, so this cell will not have a
     * rigidbody.  Only when the cell is on its own will it need this rigidbody.
     */
    btRigidBody *mHexCellRigidBody;

    /// HexCell collision shape - shared by all HexCell instances.
    static btCollisionShape *mHexCellShape;

    /// Unique name of this cell.
    std::string mName;

    /// Mass of this cell (kg).
    float mMass;

    /// Maximum possible hitpoints this cell can sustain.
    float mMaxHp;
    /// Current number of hitpoints remaining.
    float mHp;

    /// The HexShip this cell is attached to (if any).
    HexShip* mShip;

    /// Offset of this cell within the HexShip (if this cell is part of a ship).
    Ogre::Vector3 mOffset;
};


#endif

