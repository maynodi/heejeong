//
//  KeyMgr.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#pragma once

#include "cocos2d.h"

#define KEY cocos2d::EventKeyboard::KeyCode

class KeyMgr : public cocos2d::Node
{
public:
    static KeyMgr* pInstance_;
    
private:
    cocos2d::EventListenerKeyboard* pListner_;
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap_;
    
    
public:
    static KeyMgr* getInstance();
    static void destroyInstance();
    
public:
    bool init();
    
public:
    bool getIsMove(cocos2d::EventKeyboard::KeyCode keyCode);
    
public:
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
private:
    KeyMgr();
    ~KeyMgr();
};


