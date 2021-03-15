//
//  TitleLobbyLayer.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#pragma once

#include "cocos2d.h"

#include "StageLayer.h"


class Stage2Layer : public StageLayer
{    
public:
    static Stage2Layer* create(menu::PLAY ePlay);
    
public:
    bool init(menu::PLAY ePlay);
    virtual void update(float dt) override;
    
private:
    virtual void keyCheck() override;
    
public:
    Stage2Layer();
    ~Stage2Layer();
};


