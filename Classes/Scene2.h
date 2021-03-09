//
//  Scene2.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/09.
//

#pragma once

#include <stdio.h>

class Scene2 : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    
    // implement the "static create()" method manually
     CREATE_FUNC(Scene2);
};


