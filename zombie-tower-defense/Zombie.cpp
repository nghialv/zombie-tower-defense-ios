//
//  Zombie.cpp
//  zombie-tower-defense
//
//  Created by Le Ngoc Cuong on 5/19/13.
//
//

#include "Zombie.h"

int count = 1;

Zombie::Zombie(){
    this->z_health_max = 300;
    this->z_health = z_health_max;
    this->z_speed = 2;
    this->z_slower = false;
    
    //Thêm từ điển Sprite vào Cache
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombiex.plist");
    
    //Thiết lập ban đầu cho SpriteBatchNode
    this->z_sprite_sheet = CCSpriteBatchNode::create("zombiex.png");
    this->z_sprite_sheet->retain();
    this->z_sprite_sheet->setPosition(ccp(128,0));
    this->z_sprite_sheet->setVisible(false);
    
    //Thiết lập ban đầu cho Sprite
    this->setSpriteBatch(1);
}

Zombie::~Zombie(){
    CC_SAFE_RELEASE_NULL(this->z_sprite_sheet);
}

bool Zombie::z_alive(){
    if(this->z_health > 0) return true;
    else return false;
}

void Zombie::z_get_dam(Cannon *cannon){
    int i = 0;
    CCDelayTime *delayTime = CCDelayTime::create(0.5f);
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this->z_sprite_sheet,callfuncN_selector(Zombie::spriteMoveFinished));
    
    if(this->z_alive()){
        this->z_health = this->z_health - cannon->get_cannon_damage();
        i = 1;
    }
    if(!this->z_alive() && i == 1){
        this->z_die();
        this->z_sprite_sheet->runAction(CCSequence::create( delayTime,actionMoveDone,NULL ));
    }
}

void Zombie::z_get_slower(){
    if(this->z_slower == true)
        this->z_speed = 1;
}

void Zombie::z_AddToMap(CCLayer *layer, int zOrder){
    
    layer->addChild(this->z_sprite_sheet,zOrder);
}

void Zombie::spriteMoveFinished(CCNode* sender)
{
    CCSpriteBatchNode *sheet = (CCSpriteBatchNode *) sender;
    sheet->setVisible(false);
}

void Zombie::z_move(){
    float speed = this->z_speed;
    
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(this->z_sprite_sheet,callfuncN_selector(Zombie::spriteMoveFinished));
    
    float x = this->z_sprite_sheet->getPositionX();
    float y = this->z_sprite_sheet->getPositionY();
    
    if(this->z_alive()){
        if((x == 128.0) && (y < 240.0)){
            y = y + speed;
            this->z_sprite_sheet->setPosition(x,y);
            this->z_sprite_sheet->setVisible(true);
        }
        else if((x < 384.0) && (y >= 240.0)){
            x = x + speed;
            this->z_sprite_sheet->setPosition(x,y);
            this->z_sprite_sheet->setVisible(true);
        }
        else if((x >= 384.0) && (y > 100.0)){
            y = y - speed;
            this->z_sprite_sheet->setPosition(x,y);
            this->z_sprite_sheet->setVisible(true);
        }
        else if((x > 258.0) && (y <= 100.0)){
            x = x - speed;
            this->z_sprite_sheet->setPosition(x,y);
            this->z_sprite_sheet->setVisible(true);
        }
        else if((x <= 258.0) && (y < 128.0)){
            y = y + speed;
            this->z_sprite_sheet->setPosition(x,y);
            this->z_sprite_sheet->setVisible(true);
        }
        else if((x == 258.0) && (y == 128.0))
            this->z_sprite_sheet->runAction(actionMoveDone);
        
        
        
        
        if((x == 128.0) && (y == 240.0)){
            //printf(" zOrder = %d",this->z_sprite_sheet->getZOrder());
            this->z_speed = 0.5;
            setSpriteBatch(5);
        }
        else if((x == 384.0) && (y ==240.0)){
            this->z_sprite_sheet->setZOrder(60 - this->z_sprite_sheet->getZOrder());
            setSpriteBatch(9);
        }
        else if((x == 384.0) && (y == 100.0)){
            setSpriteBatch(13);
        }
        else if((x == 258.0) && (y == 100.0)){
            this->z_sprite_sheet->setZOrder(60 - this->z_sprite_sheet->getZOrder());
            setSpriteBatch(1);
        }
    }
}

void Zombie::setSpriteBatch(int pic_num){
    CCArray *bearArray = new CCArray();
    for(int i = pic_num; i < pic_num+4; i++)
    {
        char name[32] = {0};
        sprintf(name, "zombiex%d.png",i);
        bearArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
    }
    CCAnimation *walkAnim = CCAnimation::createWithSpriteFrames(bearArray, 0.1f);
    walkAnim->setDelayPerUnit(1.0f/6.0f);
    this->z_sprite = CCSprite::createWithSpriteFrameName("zombiex1.png");
    CCAction *walkAction = CCRepeatForever::create(CCAnimate::create(walkAnim));
    this->z_sprite->runAction(walkAction);
    this->z_sprite_sheet->removeAllChildrenWithCleanup(true);
    this->z_sprite_sheet->addChild(this->z_sprite);
}

void Zombie::z_die(){
    CCArray *bearArray = new CCArray();
    for(int i = 1; i < 5; i++)
    {
        char name[32] = {0};
        sprintf(name, "explosion%d.png",i);
        bearArray->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name));
    }
    CCAnimation *walkAnim = CCAnimation::createWithSpriteFrames(bearArray, 0.1f);
    walkAnim->setDelayPerUnit(0.125f);
    this->z_sprite = CCSprite::createWithSpriteFrameName("explosion1.png");
    CCAction *walkAction = CCRepeatForever::create(CCAnimate::create(walkAnim));
    this->z_sprite->runAction(walkAction);
    this->z_sprite_sheet->removeAllChildrenWithCleanup(true);
    this->z_sprite_sheet->addChild(this->z_sprite);
}