//
//  PhysicsSprite.h
//  ChocolateFactory
//
//  Created by A12642 on 2014/03/25.
//
//

#ifndef __ChocolateFactory__PhysicsSprite__
#define __ChocolateFactory__PhysicsSprite__

#include <iostream>
#include "cocos2d.h"
#include "Box2D.h"

USING_NS_CC;

class PhysicsSprite : public CCSprite
{
protected:
    b2Body* m_pBody;
    
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body* body);
    
    virtual bool isDirty(void);
    virtual CCAffineTransform nodeToParentTransform(void);
};

#endif /* defined(__ChocolateFactory__PhysicsSprite__) */
