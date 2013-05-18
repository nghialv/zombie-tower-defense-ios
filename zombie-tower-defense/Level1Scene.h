//
//  Level1Scene.h
//  zombie-tower-defense
//
//  Created by iNghia on 5/18/13.
//
//

#ifndef __zombie_tower_defense__Level1Scene__
#define __zombie_tower_defense__Level1Scene__

#include "cocos2d.h"

using namespace cocos2d;

class Level1 : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(Level1);
    
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual void ccTouchCancelled(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
private:
    CCTMXTiledMap *tileMap;
    CCTMXLayer *background;
    
    // add cannon callback
    void addCannonCallback(CCObject* pSender);
};

#endif /* defined(__zombie_tower_defense__Level1Scene__) */
