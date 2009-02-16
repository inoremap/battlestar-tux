/*
 * =====================================================================================
 *
 *       Filename:  BtOgreShapes.h
 *
 *    Description:  Contains the Ogre Mesh to Bullet Shape converters.
 *
 *        Version:  1.0
 *        Created:  27/12/2008 01:45:56 PM
 *
 *         Author:  Nikhilesh (nikki)
 *
 * =====================================================================================
 */

#ifndef _BtOgreShapes_H_
#define _BtOgreShapes_H_

#include "btBulletDynamicsCommon.h"
#include "OgreSimpleRenderable.h"
#include "OgreCamera.h"
#include "OgreHardwareBufferManager.h"
#include "OgreManualObject.h"
#include "OgreMaterialManager.h"
#include "OgreTechnique.h"
#include "OgrePass.h"

#include "OgreLogManager.h"

namespace BtOgre
{

typedef std::vector<Ogre::Vector3> Vector3Array;

//Converts from and to Bullet and Ogre stuff. Pretty self-explanatory.
class Convert
{
public:
	Convert() {};
	~Convert() {};

	static btQuaternion toBullet(const Ogre::Quaternion &q)
	{
		return btQuaternion(q.x, q.y, q.z, q.w);
	}
	static btVector3 toBullet(const Ogre::Vector3 &v)
	{
		return btVector3(v.x, v.y, v.z);
	}

	static Ogre::Quaternion toOgre(const btQuaternion &q)
	{
		return Ogre::Quaternion(q.w(), q.x(), q.y(), q.z());
	}
	static Ogre::Vector3 toOgre(const btVector3 &v)
	{
		return Ogre::Vector3(v.x(), v.y(), v.z());
	}
};

//From here on its debug-drawing stuff. ------------------------------------------------------------------


class DebugDrawer : public btIDebugDraw
{
protected:
	Ogre::SceneNode *mNode;
	btDynamicsWorld *mWorld;
	Ogre::ManualObject *mLineDrawer;
	Ogre::MaterialPtr mLineMaterial;
	bool mDebugOn;

public:

	DebugDrawer(Ogre::SceneNode *node, btDynamicsWorld *world)
		: mNode(node),
		  mWorld(world),
		  mDebugOn(true)
	{
		mLineDrawer = new Ogre::ManualObject("BtOgre/btDebugDrawer");
		mNode->attachObject(mLineDrawer);
	}

	~DebugDrawer()
	{
		delete mLineDrawer;
	}

	void step()
	{
		if (mDebugOn)
		{
		    mLineDrawer->clear();
			mWorld->debugDrawWorld();
			mNode->needUpdate();
		}
		else
		{
			mLineDrawer->clear();
			mNode->needUpdate();
		}
	}

	void drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
	{
	    mLineDrawer->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
	    mLineDrawer->position(Convert::toOgre(from));
	    mLineDrawer->colour(color.getX(), color.getY(), color.getZ(), 1.0);
		mLineDrawer->position(Convert::toOgre(to));
		mLineDrawer->colour(color.getX(), color.getY(), color.getZ(), 1.0);
		mLineDrawer->end();
	}

	void drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color)
	{
	    mLineDrawer->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
		mLineDrawer->position(Convert::toOgre(PointOnB));
		mLineDrawer->colour(color.getX(), color.getY(), color.getZ(), 1.0);
		mLineDrawer->position(Convert::toOgre(PointOnB) + (Convert::toOgre(normalOnB) * distance * 20));
		mLineDrawer->colour(color.getX(), color.getY(), color.getZ(), 1.0);
		mLineDrawer->end();
	}

	void reportErrorWarning(const char* warningString)
	{
		Ogre::LogManager::getSingleton().logMessage(warningString);
	}

	void draw3dText(const btVector3& location,const char* textString)
	{
	}

	//0 for off, anything else for on.
	void setDebugMode(int isOn)
	{
		mDebugOn = (isOn == 0) ? false : true;

		if (!mDebugOn)
			mLineDrawer->clear();
	}

	//0 for off, anything else for on.
	int	getDebugMode() const
	{
		return mDebugOn;
	}

};

}

#endif





