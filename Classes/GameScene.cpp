#include "GameScene.h"

#include "SimpleAudioEngine.h"
#include "KeyMgr.h"
#include "DataMgr.h"

#include "Stage1Layer.h"
#include "Stage2Layer.h"
#include "UILayer.h"
#include "Player.h"
#include "Coin.h"

#include "StageDefine.h"

USING_NS_CC;

GameScene::GameScene()
    : curStage_(nullptr)
{
}

GameScene::~GameScene()
{
    KeyMgr::destroyInstance();
    DataMgr::destroyInstance();
}

GameScene* GameScene::create()
{
    GameScene* pRet = new(std::nothrow) GameScene;
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

bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    addStage(stage::name::Stage1, Stage1Layer::create());
    addStage(stage::name::Stage2, Stage2Layer::create());
    
    changeStage(stage::name::Stage1);
    
    KeyMgr* pKeyMgr = KeyMgr::getInstance();
    this->addChild(pKeyMgr);
    
    Layer* pUI = UILayer::create();
    pUI->setLocalZOrder(99);
    this->addChild(pUI);
    
    return true;
}

void GameScene::changeStage(std::string stageName)
{
    Layer* stage = mapStage_[stageName];
    if(nullptr == stage)
        assert(0);
    
    curStage_ = stage;
    
    this->removeChildByName("Stage");
    this->addChild(stage);
}

void GameScene::addStage(std::string key, Layer* pLayer)
{
    pLayer->retain();
    
    auto iter = mapStage_.find(key);
    if(iter != mapStage_.end())
    {
        assert(0);
        return;
    }
    
    mapStage_[key] = pLayer;
}
