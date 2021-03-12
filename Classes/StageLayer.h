//
//  StageLayer.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/12.
//

#pragma once

#include "cocos2d.h"

#include "StageDefine.h"

#include "Coin.h"
#include "Player.h"

class StageLayer : public cocos2d::LayerColor
{
private:
    Player* pPlayer_;
    
public:
    bool init(const cocos2d::Color4B& color);
    virtual void onEnter() override;
    
public:
    void makeCoin();
    
    
};
