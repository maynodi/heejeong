#pragma once

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
private:
   cocos2d::Layer* stage_;
    
public:
    static GameScene* create();
    
public:
    virtual bool init() override;
    
public:
    virtual void update(float deltaTime) override;
    void collisionCheck();
    
public:
    GameScene();
    ~GameScene();
};
