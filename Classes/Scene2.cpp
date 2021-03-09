//
//  Scene2.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/09.
//

#include "Scene2.h"
#include "Scene1.h"
#include "Manager.h"

#define TIMER_TAG 1
#define SCORE_TAG 2

USING_NS_CC;
using namespace std;

Scene2::Scene2()
{
    minute_ = Scene1::g_time/60;
}

Scene2::~Scene2()
{
    Manager::destroyInstance();
}

Scene* Scene2::createScene()
{
    Scene* pScene = Scene::create();
    
    Layer* pLayer = Manager::getInstance()->getScene2();
    if(!pLayer)
    {
        pLayer = Scene2::create();
    }
    pScene->addChild(pLayer);
    
    return pScene;
}

bool Scene2::init()
{
    if ( !LayerColor::initWithColor(Color4B(255,255 ,255,255)))
    {
        return false;
    }
    
    initData();
    setSprite();
    setUILabel();
    
    //키보드 리스너 등록
    EventListenerKeyboard* pK_listner = EventListenerKeyboard::create();
    pK_listner->onKeyPressed = CC_CALLBACK_2(Scene2::onKeyPressed,this);
    pK_listner->onKeyReleased = CC_CALLBACK_2(Scene2::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(pK_listner, this);
    
    //타이머
    this->schedule(schedule_selector(Scene1::callEveryFrame));

    this->scheduleUpdate();
    
    return true;
}

void Scene2::initData()
{
    isMoveUp_ = false;
    isMoveDown_ = false;
    isMoveLeft_ = false;
    isMoveRight_ = false;
}

void Scene2::setSprite()
{
    //player
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    pPlayer_ = Sprite::create("white.png");
    pPlayer_->setColor(Color3B::RED);
    pPlayer_->setScale(0.2f);
   
    int halfLength =pPlayer_->getContentSize().width * pPlayer_->getScaleX()/2;
    originPos_ = Vec2(origin.x + halfLength + 50, origin.y + visibleSize.height/2);
    pPlayer_ -> setPosition(originPos_);
   
   
   this->addChild(pPlayer_);
   
   //trigger1
   pRightTrigger_ = Sprite::create("white.png", Rect(0,0,50,150));
   pRightTrigger_->setColor(Color3B::BLUE);
   pRightTrigger_->setPosition(Vec2(origin.x + visibleSize.width
                               , origin.y + visibleSize.height/2));
   
   this->addChild(pRightTrigger_);
    
    //trigger2
   pLeftTrigger_ = Sprite::create("white.png", Rect(0,0,50,150));
   pLeftTrigger_->setColor(Color3B::BLUE);
   pLeftTrigger_->setPosition(Vec2(origin.x
                               , origin.y + visibleSize.height/2));
   
   this->addChild(pLeftTrigger_);
    
   //coin
   makeCoin();
}

void Scene2::makeCoin()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    int maxX = visibleSize.width - minRange_;
    int maxY = visibleSize.height - minRange_;
    int rangeX = maxX - minRange_;
    int rangeY = maxY - minRange_;
    
    for(int i = 0; i < 5; ++i)
    {
        Sprite* pCoin = Sprite::create("white.png");
        pCoin->setColor(Color3B::YELLOW);
        pCoin->setScale(0.1f);
        pCoin->setPosition(Vec2((rand() % rangeX) + minRange_ , (rand() % rangeY) + minRange_));
        pCoin->setName("coin" + std::to_string(i));
        this->addChild(pCoin);
        
        coin_.emplace_back(pCoin);
    }
}

void Scene2::setUILabel()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    //타이머ui - tag :1
    Label* TimerLabel = Label::createWithTTF("", "fonts/arial.ttf", 30);
    TimerLabel->setColor(Color3B::BLACK);
    TimerLabel->setAnchorPoint(Vec2(0.5f,1));
    TimerLabel->setPosition(Vec2(winSize.width/2 , winSize.height -10));
    TimerLabel->setTag(TIMER_TAG);
 
    this->addChild(TimerLabel);
    
    //점수ui - tag :2
    Label* ScoreLabel = Label::createWithTTF(StringUtils::format("%d", Scene1::g_score), "fonts/arial.ttf", 30);
    ScoreLabel->setColor(Color3B::BLACK);
    ScoreLabel->setAnchorPoint(Vec2(1,1));
    ScoreLabel->setPosition(Vec2(winSize.width - 10 , winSize.height -10));
    ScoreLabel->setTag(SCORE_TAG);
    
    this->addChild(ScoreLabel);
}

void Scene2::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        {
            isMoveUp_= true;
            startMoving();
            break;
        }
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        {
            isMoveDown_= true;
            startMoving();
            break;
        }
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        {
            isMoveLeft_= true;
            startMoving();
            break;
        }
       case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        {
            isMoveRight_= true;
            startMoving();
            break;
        }
        case cocos2d::EventKeyboard::KeyCode::KEY_C:
        {
            makeCoin();
           break;
        }
        default:
            break;
    }
}

void Scene2::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if(isMoveUp_)
    {
        isMoveUp_=!isMoveUp_;
    }
    else if(isMoveDown_)
    {
        isMoveDown_=!isMoveDown_;
    }
    else if(isMoveLeft_)
    {
        isMoveLeft_=!isMoveLeft_;
    }
    else if(isMoveRight_)
    {
        isMoveRight_=!isMoveRight_;
    }
    
    stopMoving();
}

void Scene2::startMoving()
{
    this->schedule(schedule_selector(Scene2::playerMove));
}

void Scene2::stopMoving()
{
    this->unschedule(schedule_selector(Scene2::playerMove));
}

void Scene2::playerMove(float deltaTime)
{
    float speed = 500 * deltaTime;
    Point playerPos = pPlayer_->getPosition();
    
    if(isMoveUp_)
    {
        pPlayer_->setPositionY(playerPos.y + speed);
        
        if(isMoveLeft_)
        {
            pPlayer_->setPositionX(playerPos.x - speed/sqrt(2));
        }
        else if(isMoveRight_)
        {
            pPlayer_->setPositionX(playerPos.x + speed/sqrt(2));
        }
    }
    else if(isMoveDown_)
    {
        pPlayer_->setPositionY(playerPos.y - speed);
        
        if(isMoveLeft_)
        {
            pPlayer_->setPositionX(playerPos.x - speed/sqrt(2));
        }
        else if(isMoveRight_)
        {
           pPlayer_->setPositionX(playerPos.x + speed/sqrt(2));
        }
    }
    else if(isMoveLeft_)
    {
        pPlayer_->setPositionX(playerPos.x - speed);
       
        if(isMoveUp_)
        {
            pPlayer_->setPositionY(playerPos.y + speed/sqrt(2));
            
        }
        else if(isMoveDown_)
        {
            pPlayer_->setPositionY(playerPos.y - speed/sqrt(2));
        }
       
    }
    else if(isMoveRight_)
    {
        pPlayer_->setPositionX(playerPos.x +speed);
        
        if(isMoveUp_)
        {
            pPlayer_->setPositionY(playerPos.y + speed/sqrt(2));
            
        }
        else if(isMoveDown_)
        {
            pPlayer_->setPositionY(playerPos.y - speed/sqrt(2));
        }
    }
}

void Scene2::callEveryFrame(float deltaTime)
{
    Scene1::g_time += deltaTime;

    int minute = Scene1::g_time / 60;
    int sec = Scene1::g_time;
    sec = sec % 60;
    
    //타이머 ui
    Label* timerLabel = static_cast<Label*>(this->getChildByTag(TIMER_TAG));
    timerLabel->setString(StringUtils::format("%02d : %02d", minute, sec));
}

void Scene2::changeScene(Ref* sender)
{
    Director::getInstance()->replaceScene((Scene*)sender);
}

void Scene2::collisionCheck()
{
    Rect playerRect = pPlayer_->getBoundingBox();
    Rect rightTriggerRect = pRightTrigger_->getBoundingBox();
    Rect LeftTriggerRect = pLeftTrigger_->getBoundingBox();
    
    if(rightTriggerRect.intersectsRect(playerRect))
    {
        //changeScene(Scene2::createScene());
    }
    else if(LeftTriggerRect.intersectsRect(playerRect))
    {
        Manager::getInstance()->setScene2(this);
        Director::getInstance()->popScene();
    }
    
    std::list<cocos2d::Sprite*>::iterator iter_begin = coin_.begin();
    
    for(; iter_begin != coin_.end() ; ++iter_begin)
    {
        Rect coinRect = (*iter_begin)->getBoundingBox();
        
        if(coinRect.intersectsRect(playerRect))
        {
            Scene1::g_score += 1;
            coin_.erase(iter_begin);
            this->removeChild((*iter_begin));
            break;
        }
    }
}

void Scene2::update(float deltaTime)
{
    //점수 ui
    Label* scoreLabel  = static_cast<Label*>(this->getChildByTag(SCORE_TAG));
    scoreLabel->setString(StringUtils::format("%d", Scene1::g_score));
    
    //충돌
    collisionCheck();
   
}
