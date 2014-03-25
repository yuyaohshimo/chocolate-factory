//
//  PhysicsLayer.cpp
//  ChocolateFactory
//
//  Created by Yuya on 2014/03/25.
//
//

#include "PhysicsLayer.h"

using namespace cocos2d;
using namespace std;

CCScene* PhysicsLayer::scene()
{
	CCScene* scene = CCScene::create();
	PhysicsLayer* layer = PhysicsLayer::create();
	scene->addChild(layer);
	
	return scene;
}

bool PhysicsLayer::init()
{
	if (!CCLayer::init()) {
		return false;
	}
	
	initPhysics();
	
	createGround();
	createSprite();
	
	// call update
	scheduleUpdate();
	
	return true;
}

void PhysicsLayer::initPhysics()
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	
	world = new b2World(gravity);
}

void PhysicsLayer::update(float delta)
{
	int velocityIterations = 8;
	int positionIterations = 1;
	
	// Update world
	world->Step(delta, velocityIterations, positionIterations);
}

void PhysicsLayer::createGround()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    /*
     物理エンジン空間上に地面を設定する
     */
    
    // 地面ノードの作成
    CCNode* pGround = CCNode::create();
    pGround->setTag(kTag_Ground);
    this->addChild(pGround);
    
    // 地面の定義
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    groundBodyDef.userData = pGround;
    
    // 地面作成
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    
    // 地面の形と大きさの定義
    float groundHeight = size.height * 0.2;
    b2EdgeShape groundBox;
    groundBox.Set(b2Vec2(0, groundHeight / PTM_RATIO),
                  b2Vec2(size.width / PTM_RATIO, groundHeight / PTM_RATIO));
    groundBody->CreateFixture(&groundBox, 0);
}

void PhysicsLayer::createSprite()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    /* 画像の表示 */
    PhysicsSprite* pSprite = new PhysicsSprite();
    pSprite->autorelease();
    pSprite->initWithFile("CloseNormal.png");
    pSprite->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    pSprite->setTag(kTag_Sprite);
    this->addChild(pSprite);
    
    /*
     物理エンジン上の物理構造設定
     */
    
    /* 物理エンジン上の物質の定義 */
    b2BodyDef spriteBodyDef;
    /*
	 物体の力に対する属性
	 b2_dynamicBody: 速度があり力に反応する
	 b2_staticBody: 速度が無く力に反応しない
	 b2_kinematicBody: 速度があり力に反応しない
     */
    spriteBodyDef.type = b2_dynamicBody;
    /* 物理エンジンの空間上の座標 */
    spriteBodyDef.position.Set(pSprite->getPositionX() / PTM_RATIO,
                               pSprite->getPositionY() / PTM_RATIO);
    spriteBodyDef.userData = pSprite;
    /* 物理エンジン上の物質作成 */
    b2Body* spriteBody = world->CreateBody(&spriteBodyDef);
    
    /* 物理エンジン上の物質の形と大きさ */
    b2CircleShape spriteShape;
    spriteShape.m_radius = pSprite->getContentSize().width * 0.3 / PTM_RATIO;
    
    /* 物質の性質定義（形、密度、摩擦） */
    b2FixtureDef spriteFixturedef;
    spriteFixturedef.shape = &spriteShape;
    spriteFixturedef.density = 1;
    spriteFixturedef.friction = 0.9;
    
    /* 物質の性質定義適用 */
    spriteBody->CreateFixture(&spriteFixturedef);
    
    /* 画像と物理エンジン上の物質の関連付け */
    pSprite->setPhysicsBody(spriteBody);
}