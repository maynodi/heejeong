#pragma once

#include "cocos2d.h"
#include "StageDefine.h"

class StageLayer;

class GameScene : public cocos2d::Scene
{
private:
    StageLayer* curStage_;
    std::map<std::string, StageLayer*> mapStage_;
    menu::PLAY playState_;
    
public:
    static GameScene* create(menu::PLAY ePlay);
    
public:
    bool init(menu::PLAY ePlay);
    
public:
    StageLayer* getCurStage() { return curStage_; }
    menu::PLAY getPlayState() { return playState_; }
    
public:
    void changeStage(std::string stageName);
    void addStage(std::string key, StageLayer* pLayer);
    void save();
    void load();

    
public:
    GameScene();
    ~GameScene();
};
