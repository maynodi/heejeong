//
//  TitleLobbyLayer.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#include "UILayer.h"

#include "DataMgr.h"

USING_NS_CC;

UILayer::UILayer()
    : pScoreLabel(nullptr)
{
    
}

UILayer::~UILayer()
{
    
}

UILayer* UILayer::create()
{
    UILayer* pRet = new(std::nothrow) UILayer;
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

bool UILayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    pScoreLabel = Label::createWithTTF(StringUtils::format("%d", 0), "fonts/arial.ttf", 30);
    pScoreLabel->setColor(Color3B::BLACK);
    pScoreLabel->setAnchorPoint(Vec2(1,1));
    pScoreLabel->setPosition(Vec2(winSize.width - 10 , winSize.height -10));
    this->addChild(pScoreLabel);
    
    this->scheduleUpdate();
    
    return true;
}

void UILayer::update(float deltaTime)
{
    //점수 ui
    pScoreLabel->setString(StringUtils::format("%d",DataMgr::getInstance()->getScore()));
}
