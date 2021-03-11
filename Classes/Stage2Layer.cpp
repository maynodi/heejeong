//
//  TitleLobbyLayer.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#include "Stage2Layer.h"

#include "DataMgr.h"
#include "KeyMgr.h"

#include "Player.h"
#include "Coin.h"

#define MIN_RANGE 100

USING_NS_CC;

Stage2Layer::Stage2Layer()
{
    
}

Stage2Layer::~Stage2Layer()
{
    
}

Stage2Layer* Stage2Layer::create()
{
    Stage2Layer* pRet = new(std::nothrow) Stage2Layer;
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool Stage2Layer::init()
{
    if ( !LayerColor::initWithColor(Color4B::GRAY) )
    {
        return false;
    }
    
    pPlayer_ = Player::create();
    this->addChild(pPlayer_);
    
    scheduleUpdate();
    
    return true;
}

void Stage2Layer::update(float dt)
{
    if(KeyMgr::getInstance()->getIsMove(KEY::KEY_Q))
    {
        makeCoin();
    }
}

void Stage2Layer::makeCoin()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    int maxX = visibleSize.width - MIN_RANGE;
    int maxY = visibleSize.height - MIN_RANGE;
    int rangeX = maxX - MIN_RANGE;
    int rangeY = maxY - MIN_RANGE;
    
    for(int i=0; i<5; ++i)
    {
        Coin* pCoin = Coin::create();
        pCoin->getSprite()->setPosition(Vec2((rand() % rangeX) + MIN_RANGE, (rand() % rangeY + MIN_RANGE)));
        
        this->addChild(pCoin);
        coinList_.emplace_back(pCoin);
    }
}
