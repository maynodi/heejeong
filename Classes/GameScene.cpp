#include "GameScene.h"

#include "SimpleAudioEngine.h"
#include "KeyMgr.h"
#include "DataMgr.h"

#include "Stage1Layer.h"
#include "Stage2Layer.h"
#include "StageLayer.h"
#include "UILayer.h"
#include "Player.h"
#include "Coin.h"

#include "StageDefine.h"
//#include "../cocos2d/external/json/rapidjson.h"

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

void GameScene::save()
{
    UserDefault* pUserDefault = UserDefault::getInstance();

    int stageNumInt = 0;

    const char* X = {};
    const char* Y = {};
    for(auto map : mapStage_)
    {
        Vec2 playePos = static_cast<StageLayer*>(map.second)->getPlayer()->getPlayerPos();

        char stageNum = stageNumInt + '0';
        X = "playerX";
        Y = "playerY";
        char* playerX = std::strcat(&stageNum, X);
        char* playerY = std::strcat(&stageNum, Y);

        pUserDefault->setFloatForKey(playerX, playePos.x);
        pUserDefault->setFloatForKey(playerY, playePos.y);


        Vector<Node*> children = static_cast<StageLayer*>(map.second)->getChildren();

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

        ++stageNumInt;
    }

    pUserDefault->setIntegerForKey("score", DataMgr::getInstance()->getScore());

    pUserDefault->flush();
    
    
    
    
    
    

    std::string path = FileUtils::getInstance()->getWritablePath() + "test.txt";
    FILE* fp = fopen(path.c_str(), "wt");

    if(nullptr != fp)
    {
        int data = 200;
        fwrite((void*)&data, sizeof(int), 1, fp);
        fclose(fp);
    }
}
