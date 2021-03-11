#include "GameScene.h"

#include "SimpleAudioEngine.h"
#include "KeyMgr.h"
#include "DataMgr.h"

#include "Stage1Layer.h"
#include "Stage2Layer.h"
#include "UILayer.h"
#include "Player.h"
#include "Coin.h"

USING_NS_CC;

GameScene::GameScene()
    : stage_(nullptr)
{
}

GameScene::~GameScene()
{
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
    
    stage_ = Stage1Layer::create();
    this->addChild(stage_);
    
    KeyMgr* pKeyMgr = KeyMgr::getInstance();
    this->addChild(pKeyMgr);
    
    Layer* pUI = UILayer::create();
    pUI->setLocalZOrder(99);
    this->addChild(pUI);
    
    this->scheduleUpdate();
    
    return true;
}

void GameScene::update(float deltaTime)
{
    collisionCheck();
    
    if(KeyMgr::getInstance()->getIsMove(KEY::KEY_P))
    {
        this->removeChild(stage_);

        stage_ = Stage2Layer::create();
        this->addChild(stage_);
    }
}

void GameScene::collisionCheck()
{
    Player* pPlayer = static_cast<Stage1Layer*>(stage_)->getPlayer();
    
    if(nullptr == pPlayer)
        return;
    
    std::list<Coin*>* coinList = &static_cast<Stage1Layer*>(stage_)->getCoinList();
    
    if(coinList->empty())
       return;
    
    Rect playerRect = pPlayer->getSprite()->getBoundingBox();
    
    std::list<Coin*>::iterator iter_begin = coinList->begin();
    for(; iter_begin != coinList->end() ; ++iter_begin)
    {
        Rect coinRect = (*iter_begin)->getSprite()->getBoundingBox();
        
        if(coinRect.intersectsRect(playerRect))
        {
            DataMgr::getInstance()->setScore();
            
            coinList->erase(iter_begin);
            stage_->removeChild((*iter_begin));
            break;
        }
    }
}
