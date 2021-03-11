//
//  TitleLobbyLayer.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#pragma once

#include "cocos2d.h"

class Coin : public cocos2d::Node
{
private:
    cocos2d::Sprite* pSprite_;
    
public:
    static Coin* create();
    
public:
    virtual bool init() override;    
    
public:
    cocos2d::Sprite* getSprite() { return pSprite_; }
    
public:
    Coin();
    ~Coin();
};


