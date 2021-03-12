#pragma once

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
private:
    cocos2d::Layer* curStage_;
    std::map<std::string, cocos2d::Layer*> mapStage_;
    
public:
    static GameScene* create();
    
public:
    virtual bool init() override;
    
public:
    cocos2d::Layer* getCurStage() { return curStage_; }
    
public:
    void changeStage(std::string stageName);
    void addStage(std::string key, cocos2d::Layer* pLayer);
    
public:
    GameScene();
    ~GameScene();
};
