//
//  UILayer.cpp
//  NewGame-mobile
//
//  Created by CD-hj0949 on 2021/03/08.
//

#include "Manager.h"
#include "Scene2.h"

Manager* Manager::pInstance_ = nullptr;

Manager* Manager::getInstance()
{
    if(!pInstance_)
    {
        pInstance_ = new Manager;
        pInstance_ -> Init();
    }
    
    return pInstance_;
}

void Manager::destroyInstance()
{
    if(pInstance_)
    {
        delete pInstance_;
        pInstance_ = nullptr;
    }
}

bool Manager::Init()
{
    return true;
}

void Manager::setScene2(cocos2d::Layer* pLayer)
{
    if(!pScene_)
    {
        pScene_ = pLayer;
        
    }
}

Manager::Manager()
    :pScene_(nullptr)
{
}

Manager::~Manager()
{
    delete pScene_;
}
