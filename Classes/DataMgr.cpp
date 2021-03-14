//
//  KeyMgr.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#include "DataMgr.h"

#include "StageDefine.h"
#include "./json/rapidjson.h"
#include "./json/document.h"
#include "./json/writer.h"
#include "./json/stringbuffer.h"

USING_NS_CC;

DataMgr* DataMgr::pInstance_ = nullptr;

DataMgr::DataMgr()
    : score_(0)
{
}

DataMgr::~DataMgr()
{
    pInstance_ = nullptr;
}

DataMgr* DataMgr::getInstance()
{
    if(nullptr == pInstance_)
    {
        pInstance_ = new (std::nothrow) DataMgr;
        pInstance_->init();
    }
    
    return pInstance_;
}

void DataMgr::destroyInstance()
{
    if(nullptr != pInstance_)
    {
        pInstance_->release();
        pInstance_ = nullptr;
    }
}

bool DataMgr::init()
{
	loadData();

    return true;
}

void DataMgr::loadData()
{
	std::string filePath = FileUtils::getInstance()->getWritablePath() + stage::fileName::data_Stage2;

	ssize_t bufSize = 0;
	const char* fileData = (const char*)(FileUtils::getInstance()->getFileData(filePath.c_str(), "rt", &bufSize));
	if (nullptr == fileData)
	{
		//파일이 없을 때
		score_ = 0;
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

	rapidjson::Value& val1 = doc["score"];
	score_ = val1.GetInt();
}