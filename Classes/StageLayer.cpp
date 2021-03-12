//
//  StageLayer.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/12.
//

#include "StageLayer.h"

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
