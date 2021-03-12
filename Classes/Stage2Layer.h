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
    static Stage2Layer* create();
    
public:
    virtual bool init() override;
    virtual void update(float dt) override;
    
public:
    Stage2Layer();
    ~Stage2Layer();
};


