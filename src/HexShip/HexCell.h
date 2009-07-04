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
#include <tinyxml.h>

/** HexCells are the basic building blocks of a HexShip craft.
 *
 * Each HexCell can provide one or more capabilities, and is visually displayed
 * via an Ogre::SceneNode.  The cell is also linked to a Bullet collision object
 * and added to the Bullet dynamic physics simulation.
 */
class HexCell {
public:
    /** Create new HexCell
     *
     * @param name Unique name of cell.
     * The cell's Ogre::SceneNode's name is name+"Node".
     * @param pos Initial position of cell.
     */
    HexCell(const Ogre::String& name, const Ogre::Vector3& pos);

    /// Default destructor.
    ~HexCell();

    /// Update cell for a new frame.
    void update(unsigned long lTimeElapsed);

    /// HACK: forces should come from propulsion cells or object collisions.
    void applyCentralImpulse(const Ogre::Vector3& impulse);

    /** Build XML structure with cell data/attributes.
     *
     * @param node XML element to add data to.  If node is NULL, a new node
     * will be automatically created.
     *
     * @attention This function creates a new TiXmlElement object, but will
     * rely on the caller to delete the object.
     */
    void toXml(TiXmlElement* node) const;

    /// Get the Ogre::SceneNode representing this cell.
    Ogre::SceneNode* getOgreNode() { return mHexCellNode; }

    /// Get (and create, if necessary) the HexCell Bullet collision object.
    static btCollisionShape* getCollisionShapePtr();

private:
    HexCell();
    HexCell(const HexCell&);
    HexCell& operator=(const HexCell&);

    /// Ogre object controlling this cell.
    Ogre::Entity *mHexCell;

    /// Ogre node visually representing this cell.
    Ogre::SceneNode *mHexCellNode;

    /// Bullet object physically simulating this cell.
    btRigidBody *mHexCellRigidBody;

    /// HexCell collision shape - shared by all HexCell instances.
    static btCollisionShape *mHexCellShape;
};


inline std::ostream & operator<<(std::ostream& out, HexCell* cell) {
    TiXmlElement* node = NULL;
    cell->toXml(node);

    out << node;
    delete node;

    return out;
}


#endif

