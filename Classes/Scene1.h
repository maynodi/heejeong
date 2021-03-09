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

#pragma once

#include "cocos2d.h"

class Player;

class Scene1 : public cocos2d::LayerColor
{
private:
    cocos2d::Sprite* pPlayer_;
    cocos2d::Sprite* pTrigger_;
    std::list<cocos2d::Sprite*> coin_;
    
    int minRange_ = 50; //코인 생성범위 조절
    
    bool isMoveUp_;
    bool isMoveDown_;
    bool isMoveLeft_;
    bool isMoveRight_;
    
    cocos2d::Vec2 originPos_;
    
public:
    static float g_time;
    static int g_score;
    
public:
    void setPlayerOriginPos() { pPlayer_->setPosition(originPos_); }
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    
    void initData();
    void setSprite();
    void makeCoin();
    void setUILabel();
    
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
    void startMoving(); // 이동 스케쥴링 시작
    void stopMoving(); // 이동 스케쥴링 멈춤
    
    void playerMove(float deltaTime);
    
    void callEveryFrame(float deltaTime);
    
    void changeScene(Ref* sender);
    
    void collisionCheck();
    
    virtual void update(float deltaTime) override;
    
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Scene1);
    
public:
    Scene1();
    ~Scene1();
};


