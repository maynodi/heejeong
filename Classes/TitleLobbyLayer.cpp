//
//  TitleLobbyLayer.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#include "TitleLobbyLayer.h"
#include "GameScene.h"

#include "StageDefine.h"

#define FONTPATH "fonts/arial.ttf"

USING_NS_CC;

TitleLobbyLayer::TitleLobbyLayer()
    : menuFontSize_(30)
{
    
}

TitleLobbyLayer::~TitleLobbyLayer()
{
    
}

TitleLobbyLayer* TitleLobbyLayer::create()
{
    TitleLobbyLayer* pRet = new(std::nothrow) TitleLobbyLayer;
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

bool TitleLobbyLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* backGround = Sprite::create("sky.jpeg");
    backGround->setAnchorPoint(Point::ZERO);
    backGround->setPosition(Point::ZERO);
    backGround->setContentSize(Size(visibleSize.width, visibleSize.height));
    this->addChild(backGround);
    
    Label* gameTitleLabel = Label::createWithTTF("gamegamegamegame", FONTPATH, 60);
    gameTitleLabel->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height - 100));
    this->addChild(gameTitleLabel);
    
    Label* newPlayLabel = Label::createWithTTF("New Play", FONTPATH, menuFontSize_);
    Label* loadPlayLabel = Label::createWithTTF("Load Play", FONTPATH, menuFontSize_);
    Label* loadLabel = Label::createWithTTF("---------", FONTPATH, menuFontSize_);
    Label* toolLabel = Label::createWithTTF("Game Tool", FONTPATH, menuFontSize_);
    
    MenuItemLabel* newPlayMenuItem = MenuItemLabel::create(newPlayLabel, CC_CALLBACK_1(TitleLobbyLayer::newPlayMenuClick,this));
    MenuItemLabel* loadPlayMenuItem = MenuItemLabel::create(loadPlayLabel, CC_CALLBACK_1(TitleLobbyLayer::loadPlayMenuClick,this));
    MenuItemLabel* loadMenuItem = MenuItemLabel::create(loadLabel, CC_CALLBACK_1(TitleLobbyLayer::loadMenuClick,this));
    MenuItemLabel* toolMenuItem = MenuItemLabel::create(toolLabel, CC_CALLBACK_1(TitleLobbyLayer::toolMenuClick,this));
    
    Menu* menu = Menu::create(newPlayMenuItem, loadPlayMenuItem, loadMenuItem, toolMenuItem, NULL);
    menu->alignItemsVertically();
    this->addChild(menu);
    return true;
}

void TitleLobbyLayer::newPlayMenuClick(Ref* pSender)
{
    Scene* pScene = GameScene::create(menu::PLAY::NEW);    
    Director::getInstance()->replaceScene(pScene);
}

void TitleLobbyLayer::loadPlayMenuClick(Ref* pSender)
{
    Scene* pScene = GameScene::create(menu::PLAY::LOAD);
    Director::getInstance()->replaceScene(pScene);
}

void TitleLobbyLayer::loadMenuClick(Ref* pSender)
{
}

void TitleLobbyLayer::toolMenuClick(Ref* pSender)
{
}
