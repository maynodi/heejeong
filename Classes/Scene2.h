//
//  Scene2.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/09.
//

#pragma once

#include <stdio.h>

class Scene1;

class Scene2 : public cocos2d::LayerColor
{
private:
    cocos2d::Sprite* pPlayer_;
    cocos2d::Sprite* pRightTrigger_;
    cocos2d::Sprite* pLeftTrigger_;
    std::list<cocos2d::Sprite*> coin_;
    
    int minRange_ = 50; //코인 생성범위 조절
    
    int minute_ = 0;
    
    bool isMoveUp_;
    bool isMoveDown_;
    bool isMoveLeft_;
    bool isMoveRight_;
    
    cocos2d::Vec2 originPos_;
    
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
    
    
    // implement the "static create()" method manually
     CREATE_FUNC(Scene2);
    
public:
    Scene2();
    ~Scene2();
};


