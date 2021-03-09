/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Scene1.h"
#include "SimpleAudioEngine.h"
#include "Scene2.h"

#define TIMER_TAG 1
#define SCORE_TAG 2

USING_NS_CC;
using namespace std;

Scene* Scene1::createScene()
{
    Scene* pScene = Scene::create();
    
    Layer* pLayer = Scene1::create();
    pScene->addChild(pLayer);
    
    return pScene;
    
    //return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Scene1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255 ,255,255)))
    {
        return false;
    }

    initData();
    setSprite();
    setUILabel();
    
    //키보드 리스너 등록
    EventListenerKeyboard* pK_listner = EventListenerKeyboard::create();
    pK_listner->onKeyPressed = CC_CALLBACK_2(Scene1::onKeyPressed,this);
    pK_listner->onKeyReleased = CC_CALLBACK_2(Scene1::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(pK_listner, this);
    
    
    //타이머
    this->schedule(schedule_selector(Scene1::callEveryFrame));

    this->scheduleUpdate();
    
    return true;
}

void Scene1::initData()
{
    time_ = 0.f;
    minute_ = 0;
    score_ = 0;
    minRange_ = 50;
    
    isMoveUp_ = false;
    isMoveDown_ = false;
    isMoveLeft_ = false;
    isMoveRight_ = false;
}

void Scene1::setSprite()
{
    //player
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    pPlayer_ = Sprite::create("white.png");
    pPlayer_->setColor(Color3B::RED);
    pPlayer_->setScale(0.2f);
    
    int halfLength =pPlayer_->getContentSize().width * pPlayer_->getScaleX()/2;
    pPlayer_->setPosition(Vec2(origin.x + halfLength
                               , origin.y + visibleSize.height/2));
    
    
    this->addChild(pPlayer_);
    
    //trigger
    pTrigger_ = Sprite::create("white.png", Rect(0,0,50,150));
    pTrigger_->setColor(Color3B::BLUE);
    pTrigger_->setPosition(Vec2(origin.x + visibleSize.width
                                , origin.y + visibleSize.height/2));
    
    this->addChild(pTrigger_);
    
    //coin
    makeCoin();
}

void Scene1::makeCoin()
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

void Scene1::setUILabel()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    //타이머ui - tag :1
    Label* TimerLabel = Label::createWithTTF(/*StringUtils::format("(Time) %d : %d ",time_)*/"", "fonts/arial.ttf", 30);
    TimerLabel->setColor(Color3B::BLACK);
    TimerLabel->setAnchorPoint(Vec2(0.5f,1));
    TimerLabel->setPosition(Vec2(winSize.width/2 , winSize.height -10));
    TimerLabel->setTag(TIMER_TAG);
 
    this->addChild(TimerLabel);
    
    //점수ui - tag :2
    Label* ScoreLabel = Label::createWithTTF(StringUtils::format("(score) %d", score_), "fonts/arial.ttf", 30);
    ScoreLabel->setColor(Color3B::BLACK);
    ScoreLabel->setAnchorPoint(Vec2(1,1));
    ScoreLabel->setPosition(Vec2(winSize.width - 10 , winSize.height -10));
    ScoreLabel->setTag(SCORE_TAG);
    
    this->addChild(ScoreLabel);
}

void Scene1::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{   
    //int speed = 3;
    
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        {
            isMoveUp_=true;
            startMoving();
            break;
        }
        case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        {
            isMoveDown_=true;
            startMoving();
            break;
        }
        case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        {
            isMoveLeft_=true;
            startMoving();
            break;
        }
       case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        {
            isMoveRight_=true;
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

void Scene1::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
//    isMoveUp_= false;
//    isMoveDown_= false;
//    isMoveLeft_= false;
//    isMoveRight_= false;
    
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

void Scene1::startMoving()
{
    this->schedule(schedule_selector(Scene1::playerMove));
}

void Scene1::stopMoving()
{
    this->unschedule(schedule_selector(Scene1::playerMove));
}

void Scene1::playerMove(float deltaTime)
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

void Scene1::callEveryFrame(float deltaTime)
{
    time_ += deltaTime;
    
    int minute =0;
    
    if(60 <= time_)
    {
        minute += 1;
        time_=0;
    }
    
    int sec = time_;
    
    //타이머 ui
      Label* timerLabel = static_cast<Label*>(this->getChildByTag(TIMER_TAG));
      timerLabel->setString(StringUtils::format("%02d : %02d", minute, sec));
    
          
    123456123
    
    
}

void Scene1::changeScene(Ref* sender)
{
    Director::getInstance()->replaceScene((Scene*)sender);
}

void Scene1::collisionCheck()
{
    Rect playerRect = pPlayer_->getBoundingBox();
    Rect triggerRect = pTrigger_->getBoundingBox();
    
    if(triggerRect.intersectsRect(playerRect))
    {
        changeScene(Scene2::createScene());
    }
    
    std::list<cocos2d::Sprite*>::iterator iter_begin = coin_.begin();
    
    for(; iter_begin != coin_.end() ; ++iter_begin)   //for(const cocos2d::Sprite* pSprite : coin_)
    {
        Rect coinRect = (*iter_begin)->getBoundingBox();
        
        if(coinRect.intersectsRect(playerRect))
        {
            score_ += 1;
            coin_.erase(iter_begin);
            this->removeChild((*iter_begin));
            break;
        }
    }
}

void Scene1::update(float deltaTime)
{
    CCLOG("%f", deltaTime);
    
//    //타이머 ui
//    Label* timerLabel = static_cast<Label*>(this->getChildByTag(TIMER_TAG));
//    //timerLabel->setString(StringUtils::format("(Time) %2.1f" , time_));
//
//    if(0 < minute_)
//        timerLabel->setString(StringUtils::format("(Time) %02d : %02d", minute_, time_));
//    else
//        timerLabel->setString(StringUtils::format("(Time) %02d : &02d", time_ ));
    
    //점수 ui
    Label* scoreLabel  = static_cast<Label*>(this->getChildByTag(SCORE_TAG));
    scoreLabel->setString(StringUtils::format("(score) %d", score_));
    
    //충돌
    collisionCheck();
    
}
