//
//  KeyMgr.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#include "DataMgr.h"

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
    return true;
}
