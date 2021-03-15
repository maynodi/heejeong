//
//  TitleLobbyLayer.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#pragma once

#include "cocos2d.h"
#include "MyObjectNode.h"

class Coin : public cocos2d::Node, public MyObjectNode
{
private:
    cocos2d::Sprite* pSprite_;
    
public:
    static Coin* create();
    virtual bool init() override;

public:
    cocos2d::Sprite* getSprite() { return pSprite_; }
    cocos2d::Vec2 getCoinPos() { return pSprite_->getPosition(); }
    
public:
    void collision();

public:
    virtual void save() override {};
    
public:
    Coin();
    ~Coin();
};


