//
//  TitleLobbyLayer.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#include "Stage2Layer.h"

#include "KeyMgr.h"

#include "GameScene.h"

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
    if(false == StageLayer::init(Color4B::GRAY))
        return false;
    
    return true;
}

void Stage2Layer::update(float dt)
{
    keyCheck();
}

void Stage2Layer::keyCheck()
{
    StageLayer::keyCheck();
    
    if(KeyMgr::getInstance()->getIsMove(KEY::KEY_O))
     {
         GameScene* scene = (GameScene*)Director::getInstance()->getRunningScene();
         
         scene->changeStage(stage::name::Stage1);
     }
}
