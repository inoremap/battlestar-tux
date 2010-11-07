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

#include <btGeneric6DofConstraint.h>
#include <Ogre.h>
#include <BtOgreExtras.h>

#define _USE_MATH_DEFINES
#include <cmath>

#include "BoltWeaponCell.h"
#include "HexShip.h"
#include "PhysicsManager.h"
#include "UniqueNames.h"
#include "WeaponCell.h"


// Static members
btCollisionShape* BoltWeaponCell::mWeaponShape;


BoltWeaponCell::BoltWeaponCell(const std::string& name, const float mass, const float hitPoints,
                            const float damagePoints, const float energyRequired,
                            const unsigned long restTime) :
    WeaponCell(name, mass, hitPoints, damagePoints, energyRequired, restTime, BOLT_WEAPON)
{
}


BoltWeaponCell::~BoltWeaponCell() {
}


void BoltWeaponCell::activateWeapon() {
    // Create ammo's visual entity.
    std::string ammoName = UniqueNames::Next("BeamAmmo");
    Ogre::SceneManager *sceneMgr = Ogre::Root::getSingletonPtr()->getSceneManager("ST_GENERIC");
    Ogre::Entity *ammoEntity = sceneMgr->createEntity(ammoName, Ogre::SceneManager::PT_SPHERE);
    Ogre::SceneNode *ammoNode = sceneMgr->getRootSceneNode()->createChildSceneNode(ammoName + "Node");
    ammoNode->attachObject(ammoEntity);
    // The built-in Ogre SPHERE has a size of 100 units.
    ammoNode->setScale(0.004, 0.004, 0.004);

    // Set position of ammo - outside of the HexShip
    Ogre::SceneNode* shipNode = mShip->getOgreNode();
    ammoNode->setOrientation(shipNode->getOrientation());
    ammoNode->setPosition(shipNode->getPosition());
    ammoNode->translate(mOffset, Ogre::Node::TS_LOCAL);
    Ogre::Vector3 cellPos = ammoNode->getPosition();
    // At this point, the ammo is in the center of the BoltWeaponCell.
    // Applying this final offset will put it outside the cell.
    Ogre::Ray firingRay = Ogre::Ray(cellPos, mTargetPoint.normalisedCopy());
    ammoNode->setPosition(firingRay.getPoint(2));

    // Add the ammo to the collision world.
    btDiscreteDynamicsWorld *btDynamicsWorld = PhysicsManager::getSingletonPtr()->getDynamicsWorld();
    BtOgre::RigidBodyState *state = new BtOgre::RigidBodyState(ammoNode);
    btRigidBody *ammoRigidBody = new btRigidBody(1, state, getCollisionShapePtr());
    btDynamicsWorld->addRigidBody(ammoRigidBody);
    ammoRigidBody->setLinearFactor(btVector3(1,0,1));
    // Fire towards target.
    Ogre::Vector3 impulse = (mTargetPoint - cellPos).normalisedCopy();
    impulse *= 8;
    ammoRigidBody->applyCentralImpulse(BtOgre::Convert::toBullet(impulse));
}


btCollisionShape* BoltWeaponCell::getCollisionShapePtr() {
    if(! mWeaponShape) {
        mWeaponShape = new btSphereShape(0.3);
        btScalar mass = 1;
        btVector3 inertia  = btVector3(0,0,0);
        mWeaponShape->calculateLocalInertia(mass, inertia);
    }

    return mWeaponShape;
}

