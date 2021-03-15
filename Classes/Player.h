//
//  TitleLobbyLayer.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#pragma once

#include "cocos2d.h"
#include "MyObjectNode.h"

#include "StageDefine.h"

class Player : public cocos2d::Node, public MyObjectNode
{    
private:
    cocos2d::Sprite* pSprite_;
    cocos2d::Vec2 originPos_;
    
public:
    static Player* create(menu::PLAY ePlay, const std::string stageName);
    
public:
    bool init(menu::PLAY ePlay, const std::string stageName);
    
public:
    cocos2d::Sprite* getSprite() { return pSprite_; }
    cocos2d::Vec2 getPlayerPos() { return pSprite_->getPosition(); }
    
public:
    virtual void update(float deltaTime) override;
    virtual void onEnter() override;
    
private:
    void move(float deltaTime);
    void collisionCheck();
    
public:
    virtual void save() override ;
	void loadData(const std::string stageName);

    
public:
    Player();
    ~Player();
};


