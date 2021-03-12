//
//  TitleLobbyLayer.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#include "Stage1Layer.h"

#include "DataMgr.h"
#include "KeyMgr.h"

#include "GameScene.h"
#include "Player.h"
#include "Stage2Layer.h"

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
    if(false == StageLayer::init(Color4B::WHITE))
        return false;
    
    return true;
}

void Stage1Layer::update(float dt)
{
    if(KeyMgr::getInstance()->getIsMove(KEY::KEY_Q))
    {
        makeCoin();
    }
    else if(KeyMgr::getInstance()->getIsMove(KEY::KEY_P))
    {
        GameScene* scene = (GameScene*)Director::getInstance()->getRunningScene();
        
        scene->changeStage("Stage2");
    }
}

