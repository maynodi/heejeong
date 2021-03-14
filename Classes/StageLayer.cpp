//
//  StageLayer.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/12.
//

#include "StageLayer.h"

#include "KeyMgr.h"
#include "DataMgr.h"

#include "StageDefine.h"
#include "./json/rapidjson.h"
#include "./json/document.h"
#include "./json/writer.h"
#include "./json/stringbuffer.h"

#include "TitleScene.h"


USING_NS_CC;

bool StageLayer::init(const std::string stageName, const Color4B& color)
{
    if(false == LayerColor::initWithColor(color))
        return false;
    
    this->setName("Stage");
    
    pPlayer_ = Player::create(stageName);
    this->addChild(pPlayer_);
        
	//
	loadData(stageName);

    return true;
}

void StageLayer::onEnter()
{
    Layer::onEnter();
    
    scheduleUpdate();
}

void StageLayer::makeCoin()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    int maxX = visibleSize.width - stage::define::COIN_MIN_RANGE;
    int maxY = visibleSize.height - stage::define::COIN_MIN_RANGE;
    int rangeX = maxX - stage::define::COIN_MIN_RANGE;
    int rangeY = maxY - stage::define::COIN_MIN_RANGE;
    
    for(int i=0; i<5; ++i)
    {
        Coin* pCoin = Coin::create();
        pCoin->getSprite()->setPosition(Vec2((rand() % rangeX) + stage::define::COIN_MIN_RANGE, (rand() % rangeY + stage::define::COIN_MIN_RANGE)));

        this->addChild(pCoin);
    }    
}

void StageLayer::keyCheck()
{
    if(KeyMgr::getInstance()->getIsMove(KEY::KEY_Q))
    {
        makeCoin();
    }
    else if(KeyMgr::getInstance()->getIsMove(KEY::KEY_ESCAPE))
    {
        Director::getInstance()->replaceScene(TitleScene::create());
    }
}

void StageLayer::loadData(const std::string stageName)
{
	std::string fileName = {};
	if (stage::name::Stage1 == stageName)
	{
		fileName = stage::fileName::data_Stage1;
	}
	else if (stage::name::Stage2 == stageName)
	{
		fileName = stage::fileName::data_Stage2;
	}

	std::string filePath = FileUtils::getInstance()->getWritablePath() + fileName;

	ssize_t bufSize = 0;
	const char* fileData = (const char*)(FileUtils::getInstance()->getFileData(filePath.c_str(), "rt", &bufSize));
	if (nullptr == fileData)
	{
		//파일이 없을 때
		makeCoin();
		return;
	}


	std::string clearData(fileData);
	size_t end = clearData.rfind("}");
	clearData = clearData.substr(0, end + 1);

	rapidjson::Document doc;
	doc.Parse<0>(clearData.c_str());
	if (doc.HasParseError())
	{
		return;
	}

	rapidjson::Value& arr = doc["coinX"];
	for (rapidjson::SizeType i = 0; i < arr.Size(); ++i)
	{
		Coin* pCoin = Coin::create();

		float posX = arr[i].GetFloat();
		float posY = doc["coinY"][i].GetFloat();

		pCoin->getSprite()->setPosition(Vec2(posX, posY));
		this->addChild(pCoin);
	}

}
