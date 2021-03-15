#include "GameScene.h"

#include "SimpleAudioEngine.h"
#include "KeyMgr.h"
#include "DataMgr.h"

#include <stdio.h>
#include "./json/rapidjson.h"
#include "./json/document.h"
#include "./json/writer.h"
#include "./json/stringbuffer.h"

#include "Stage1Layer.h"
#include "Stage2Layer.h"
#include "StageLayer.h"
#include "UILayer.h"
#include "Player.h"
#include "Coin.h"



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

GameScene* GameScene::create(menu::PLAY ePlay)
{
    GameScene* pRet = new(std::nothrow) GameScene;
    if (pRet && pRet->init(ePlay))
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

bool GameScene::init(menu::PLAY ePlay)
{
    if ( false == Scene::init() )
    {
        return false;
    }
    
    playState_ = ePlay;
    addStage(stage::name::Stage1, Stage1Layer::create(playState_));
    addStage(stage::name::Stage2, Stage2Layer::create(playState_));
    
    if(menu::PLAY::NEW == ePlay)
    {
        changeStage(stage::name::Stage1);
    }
    else if(menu::PLAY::LOAD == ePlay)
    {
        load();
    }
    
    
    KeyMgr* pKeyMgr = KeyMgr::getInstance();
    this->addChild(pKeyMgr);
    
    Layer* pUI = UILayer::create();
    pUI->setLocalZOrder(99);
    this->addChild(pUI);    
	
    return true;
}

void GameScene::changeStage(std::string stageName)
{
    StageLayer* stage = mapStage_[stageName];
    if(nullptr == stage)
        assert(0);
    
    curStage_ = stage;
    
    this->removeChildByName("Stage");
    this->addChild(stage);
}

void GameScene::addStage(std::string key, StageLayer* pLayer)
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
	for (auto& stage : mapStage_)
	{
        const char* json = "{\"playerX\":0,\"playerY\":0,\"coinX\":[],\"coinY\":[],\"score\":0,\"finalStage\":0}";
        rapidjson::Document doc;
        doc.Parse(json);
        
		Player* pPlayer = ((StageLayer*)mapStage_[stage.first])->getPlayer();
		float fX = (pPlayer->getSprite())->getPosition().x;
		float fY = (pPlayer->getSprite())->getPosition().y;

		//player
		rapidjson::Value& val1 = doc["playerX"];
		val1.SetFloat(fX);

		rapidjson::Value& val2 = doc["playerY"];
		val2.SetFloat(fY);

		//coin
		Vector<Node*> childrenVector = mapStage_[stage.first]->getChildren();

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
				val4.PushBack(coinY, allocator);

				++cnt;
			}
		}
        
        //score
        rapidjson::Value& val5 = doc["score"];
        val5.SetInt(DataMgr::getInstance()->getScore());
        
        //final stage
        std::string finalStageName = ((StageLayer*)curStage_)->getStageName();
        
        rapidjson::Value& val6 = doc["finalStage"];
        val6.SetString(finalStageName.c_str(), finalStageName.length());
        
		//
		rapidjson::StringBuffer buf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
		doc.Accept(writer);

        FILE* pfile = nullptr;

		std::string filePath = FileUtils::getInstance()->getWritablePath();
		if (stage::name::Stage1 == stage.first)
		{
			filePath += stage::fileName::data_Stage1;
		}
		if (stage::name::Stage2 == stage.first)
		{
			filePath += stage::fileName::data_Stage2;
		}

        pfile = fopen(filePath.c_str(), "wt");
        
		fwrite(buf.GetString(), buf.GetSize(), 1, pfile);
		fclose(pfile);
	}
}

void GameScene::load()
{
    std::string filePath = FileUtils::getInstance()->getWritablePath() + stage::fileName::data_Stage1;
    //파일이름은 뭐가 와도 상관 없음, 파일 모두에 마지막 스테이지정보 저장했음
    
    std::string fileData = FileUtils::getInstance()->getStringFromFile(filePath.c_str());
    
    std::string clearData(fileData);
    size_t end = clearData.rfind("}");
    clearData = clearData.substr(0, end + 1);
    
    rapidjson::Document doc;
    doc.Parse<0>(clearData.c_str());
    if (doc.HasParseError())
    {
        return;
    }

    rapidjson::Value& val1 = doc["finalStage"];
    std:: string fianlStageName = val1.GetString();
    
    changeStage(fianlStageName);
}
