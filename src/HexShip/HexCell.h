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

class HexCell {
public:
    HexCell();
    HexCell(const Ogre::String& name, const Ogre::Vector3& pos);
    ~HexCell();

    void update(unsigned long lTimeElapsed);

    void applyCentralImpulse(const Ogre::Vector3& impulse);

    Ogre::SceneNode* getOgreNode() { return mHexCellNode; }

    static btCollisionShape* getCollisionShapePtr();

private:
    HexCell(const HexCell&);
    HexCell & operator = (const HexCell&);

    Ogre::Entity *mHexCell;
    Ogre::SceneNode *mHexCellNode;
    btRigidBody *mHexCellRigidBody;

    // All HexCells can share the collision shapes.
    static btCollisionShape *mHexCellShape;
};

#endif

