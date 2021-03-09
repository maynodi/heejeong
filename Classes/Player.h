//
//  Player.hpp
//  NewGame-mobile
//
//  Created by CD-hj0949 on 2021/03/08.
//

#pragma once

#include <stdio.h>

class Player : public cocos2d::Node
{
public:
    static cocos2d::Node* create();
    
    virtual bool init();
};
