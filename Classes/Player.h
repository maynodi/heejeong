//
//  TitleLobbyLayer.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#pragma once

#include "cocos2d.h"

class Player : public cocos2d::Node
{    
private:
    cocos2d::Sprite* pSprite_;
    cocos2d::Vec2 originPos_;
    
public:
    static Player* create();
    
public:
    virtual bool init() override;
    
public:
    cocos2d::Sprite* getSprite() { return pSprite_; }
    
public:
    virtual void update(float deltaTime) override;
    virtual void onEnter() override;
    
private:
    void move(float deltaTime);
    void collisionCheck();
    
public:
    Player();
    ~Player();
};


