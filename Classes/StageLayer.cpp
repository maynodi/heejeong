//
//  StageLayer.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/12.
//

#include "StageLayer.h"

#include "KeyMgr.h"
#include "DataMgr.h"

#include "TitleScene.h"


USING_NS_CC;

bool StageLayer::init(const Color4B& color)
{
    if(false == LayerColor::initWithColor(color))
        return false;
    
    this->setName("Stage");
    
    pPlayer_ = Player::create();
    this->addChild(pPlayer_);
        
    makeCoin();
    
    return true;
}

void StageLayer::onEnter()
{
    Layer::onEnter();
    
    scheduleUpdate();
}

void StageLayer::makeCoin()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    int maxX = visibleSize.width - stage::define::COIN_MIN_RANGE;
    int maxY = visibleSize.height - stage::define::COIN_MIN_RANGE;
    int rangeX = maxX - stage::define::COIN_MIN_RANGE;
    int rangeY = maxY - stage::define::COIN_MIN_RANGE;
    
    for(int i=0; i<5; ++i)
    {
        Coin* pCoin = Coin::create();
        pCoin->getSprite()->setPosition(Vec2((rand() % rangeX) + stage::define::COIN_MIN_RANGE, (rand() % rangeY + stage::define::COIN_MIN_RANGE)));

        this->addChild(pCoin);
    }
    
}

void StageLayer::keyCheck()
{
    if(KeyMgr::getInstance()->getIsMove(KEY::KEY_Q))
    {
        makeCoin();
    }
    else if(KeyMgr::getInstance()->getIsMove(KEY::KEY_ESCAPE))
    {
        Director::getInstance()->replaceScene(TitleScene::create());
    }
    else if(KeyMgr::getInstance()->getIsMove(KEY::KEY_1))
    {
        save();
    }
}

void StageLayer::save()
{
    char stageNum = {};
    if(stage::name::Stage1 == this->getName())
    {
        stageNum = 0 + '0';
    }
    else if(stage::name::Stage2 == this->getName())
    {
       stageNum = 1 + '0';
    }
    
    UserDefault* pUserDefault = UserDefault::getInstance();
    
    Vec2 playePos = pPlayer_->getPlayerPos();
    
    const char* X = {};
    const char* Y = {};
    
    X = "playerX";
    Y = "playerY";
    char* playerX = std::strcat(&stageNum, X);
    char* playerY = std::strcat(&stageNum, Y);
    
    pUserDefault->setFloatForKey(playerX, playePos.x);
    pUserDefault->setFloatForKey(playerY, playePos.y);
    
    
    Vector<Node*> children = this->getChildren();
    
    int cntInt = 0;
    for(auto child : children)
    {
        if("Coin" == child->getName())
        {
            
            char cnt = cntInt + '0';
            X = "coinX";
            Y = "coinY";
            char* coinX = std::strcat(&cnt, X);
            char* coinY = std::strcat(&cnt, Y);
            
            Vec2 coinPos = ((Coin*)child)->getCoinPos();
            pUserDefault->setFloatForKey(coinX, coinPos.x);
            pUserDefault->setFloatForKey(coinY, coinPos.y);
            
            ++cntInt;
        }
    }
    
    pUserDefault->setIntegerForKey("score", DataMgr::getInstance()->getScore());
    pUserDefault->flush();
}
