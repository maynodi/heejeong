//
//  TitleLobbyLayer.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#include "Coin.h"

#include "DataMgr.h"

#include "GameScene.h"

USING_NS_CC;

Coin::Coin()
    : pSprite_(nullptr)
{
    
}

Coin::~Coin()
{
}

Coin* Coin::create()
{
    Coin* pRet = new(std::nothrow) Coin;
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

bool Coin::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    
    this->setName("Coin");
    
    pSprite_ = Sprite::create("white.png");
    pSprite_->setScale(0.1f);
    pSprite_->setColor(Color3B::YELLOW);
    
    this->addChild(pSprite_);
    
    return true;
}

void Coin::collision()
{
    DataMgr::getInstance()->addScore();
    this->removeFromParent();
}
