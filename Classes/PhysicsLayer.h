//
//  PhysicsLayer.h
//  ChocolateFactory
//
//  Created by Yuya on 2014/03/25.
//
//

#ifndef __ChocolateFactory__PhysicsLayer__
#define __ChocolateFactory__PhysicsLayer__

#include <iostream>

#include "cocos2d.h"
#include "Box2D.h"
#include "Config.h"
#include "PhysicsSprite.h"

USING_NS_CC;

class PhysicsLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(PhysicsLayer);
	
	b2World* world;
	void initPhysics();
	virtual void update(float delta);
	
	void createGround();
	void createSprite();
	
	enum kTag {
        kTag_Sprite,
        kTag_Ground,
    };
	
};

#endif /* defined(__ChocolateFactory__PhysicsLayer__) */
