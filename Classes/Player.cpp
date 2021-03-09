//
//  Player.cpp
//  NewGame-mobile
//
//  Created by CD-hj0949 on 2021/03/08.
//

#include "Player.h"

cocos2d::Node* Player::create()
{
    Sprite* player = Sprite::create("images/white.png");
    
    return player;
}

bool Player::init()
{
    
    return true;
}
