//
//  TitleLobbyLayer.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#pragma once

#include "cocos2d.h"

#include "StageLayer.h"

class Stage1Layer : public StageLayer
{
public:
    static Stage1Layer* create();
    
public:
    virtual bool init() override;
    virtual void update(float dt) override;
    
private:
    virtual void keyCheck() override;
    
public:
    Stage1Layer();
    ~Stage1Layer();
};

