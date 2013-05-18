//
//  Level1Scene.cpp
//  zombie-tower-defense
//
//  Created by iNghia on 5/18/13.
//
//

#include "Level1Scene.h"
#include "Common.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

CCScene* Level1::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Level1 *layer = Level1::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Level1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    // register touch event
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    float ratio = DEVICE_WIDTH/LEVEL1_MAP_WIDTH;
    if(ratio < DEVICE_HEIGHT/LEVEL1_MAP_HEIGHT)
    	ratio = DEVICE_HEIGHT/LEVEL1_MAP_HEIGHT;
    tileMap = CCTMXTiledMap::create("level1.tmx");
    tileMap->setScale(ratio);
    background = tileMap->layerNamed("background");
    addChild(tileMap, -1);
    
    // add cannon
    CCMenuItemImage *pAddCannon = CCMenuItemImage::create("CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(Level1::addCannonCallback));
    pAddCannon->setPosition(ccp(DEVICE_WIDTH-20, DEVICE_HEIGHT-20));
    CCMenu *pMenu = CCMenu::create(pAddCannon, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    return true;
}

void Level1::addCannonCallback(CCObject* pSender)
{
    printf("ADD CANNON");
}

bool Level1::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    printf("Touches Began¥n");
    return true;
}

void Level1::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    printf("Touches Moved¥n");
}

void Level1::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    printf("Touches Ended¥n");
}

void Level1::ccTouchCancelled(CCTouch* touch, CCEvent* event)
{
    printf("Touches Cancelled¥n");
}

