//
//  TitleLobbyLayer.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#include "Stage1Layer.h"

#include "DataMgr.h"
#include "KeyMgr.h"

#include "Player.h"
#include "Coin.h"

#define MIN_RANGE 100

USING_NS_CC;

Stage1Layer::Stage1Layer()
{
    
}

Stage1Layer::~Stage1Layer()
{
    
}

Stage1Layer* Stage1Layer::create()
{
    Stage1Layer* pRet = new(std::nothrow) Stage1Layer;
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

bool Stage1Layer::init()
{
    if ( !LayerColor::initWithColor(Color4B::WHITE) )
    {
        return false;
    }
    
    pPlayer_ = Player::create();
    this->addChild(pPlayer_);
    
    //scheduleUpdate();
    makeCoin();
    return true;
}

void Stage1Layer::update(float dt)
{
    if(KeyMgr::getInstance()->getIsMove(KEY::KEY_Q))
    {
        makeCoin();
    }
}

void Stage1Layer::makeCoin()
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
