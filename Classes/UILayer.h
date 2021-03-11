//
//  TitleLobbyLayer.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#pragma once

#include "cocos2d.h"

class UILayer : public cocos2d::Layer
{
private:
    cocos2d::Label* pScoreLabel;
    
public:
    static UILayer* create();
    
public:
    virtual bool init() override;
    
public:
    virtual void update(float deltaTime) override;
    
public:
    UILayer();
    ~UILayer();
};


