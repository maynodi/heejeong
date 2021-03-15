//
//  StageLayer.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/12.
//

#pragma once

#include "cocos2d.h"

#include "StageDefine.h"

#include "Coin.h"
#include "Player.h"

class StageLayer : public cocos2d::LayerColor
{
private:
    Player* pPlayer_;
    std::vector<MyObjectNode*> myObjects_;
    
    std::string curStageName_;
    
public:
    bool init(menu::PLAY ePlay, const std::string stageName, const cocos2d::Color4B& color);
    virtual void onEnter() override;
    
public:
    Player* getPlayer() { return pPlayer_; }
    std::string getStageName() { return curStageName_; }
public:
    void makeCoin();
    virtual void keyCheck();
    
public:
    void save();
	void loadData(const std::string stageName);

protected:
    StageLayer(std::string stageName);
    ~StageLayer();
};
