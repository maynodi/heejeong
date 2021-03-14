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

#include "./json/rapidjson.h"
#include "./json/document.h"
#include "./json/writer.h"
#include "./json/stringbuffer.h"
#include "./json/prettywriter.h"

USING_NS_CC;

GameScene::GameScene()
    : curStage_(nullptr)
{
}

GameScene::~GameScene()
{
	save();
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
	Player* pPlayer = ((StageLayer*)mapStage_[stage::name::Stage1])->getPlayer();
	float fX = (pPlayer->getSprite())->getPosition().x;
	float fY = (pPlayer->getSprite())->getPosition().y;

	const char* json = "{\"playerX\":0,\"playerY\":0,\"coinX\":[0],\"coinY\":[0]}";
	rapidjson::Document doc;
	doc.Parse(json);

	rapidjson::Value& val1 = doc["playerX"];
	val1.SetFloat(fX);

	rapidjson::Value& val2 = doc["playerY"];
	val2.SetFloat(fY);

	Vector<Node*> childrenVector = mapStage_[stage::name::Stage1]->getChildren();
	int size = childrenVector.size();

	rapidjson::Value& val3 = doc["coinX"];
	rapidjson::Value& val4 = doc["coinY"];
	
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

	int cnt = 0;
	for (auto child : childrenVector)
	{
		if ("Coin" == child->getName())
		{
			float coinX = (((Coin*)child)->getSprite())->getPosition().x;
			float coinY = (((Coin*)child)->getSprite())->getPosition().y;

			val3.PushBack(coinX, allocator);
			val4.PushBack(coinY,allocator);

			++cnt;			
		}
	}
	int itest = 0;
	
	
	rapidjson::StringBuffer buf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
	doc.Accept(writer);
	
	FILE* pfile = nullptr;

	std::string fileName = FileUtils::getInstance()->getWritablePath();
	fileName += "data.json";

	fopen_s(&pfile, fileName.c_str(), "wt");
	fwrite(buf.GetString(), buf.GetSize(), 1, pfile);
	fclose(pfile);
}
