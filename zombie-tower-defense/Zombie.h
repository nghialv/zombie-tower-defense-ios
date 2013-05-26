//
//  Zombie.h
//  zombie-tower-defense
//
//  Created by Le Ngoc Cuong on 5/19/13.
//
//

#ifndef __zombie_tower_defense__Zombie__
#define __zombie_tower_defense__Zombie__

#include <iostream>
#include "cocos2d.h"
#include "Cannon.h"
#include "Level1Scene.h"

using namespace cocos2d;

class Zombie:CCObject{
    
public:
    Zombie();
    ~Zombie();
    
    CCSpriteBatchNode *z_sprite_sheet;
    void z_AddToMap(CCLayer *layer,int zOrder);
    bool z_alive();
    void z_move();
    void z_get_dam(Cannon *can);
    void z_get_slower();
    
    
protected:
    CCSprite *z_sprite;
    int z_health_max;
    bool z_slower;
    float z_speed;
    float z_health;
    
    void setSpriteBatch(int pic_num);
    void z_die();
    void spriteMoveFinished(CCNode* sender);
};

#endif /* defined(__zombie_tower_defense__Zombie__) */
