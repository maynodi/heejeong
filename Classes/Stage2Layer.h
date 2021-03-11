//
//  TitleLobbyLayer.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#pragma once

#include "cocos2d.h"

class Player;
class Coin;

class Stage2Layer : public cocos2d::LayerColor
{
private:
    Player* pPlayer_;
    std::list<Coin*> coinList_;
    
public:
    static Stage2Layer* create();
    
public:
    virtual bool init() override;
    virtual void update(float dt) override;
    
public:
    Player* getPlayer() { return pPlayer_; }
    std::list<Coin*>& getCoinList() { return coinList_; }
    
public:
    void makeCoin();
    
public:
    Stage2Layer();
    ~Stage2Layer();
};


