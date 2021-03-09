//
//  UILayer.h
//  NewGame-mobile
//
//  Created by CD-hj0949 on 2021/03/08.
//

#pragma once

#include <stdio.h>

class Scene2;
class Manager
{
private:
    static Manager* pInstance_;
 
private:
    cocos2d::Layer* pScene_;
    
public:
    static Manager* getInstance();
    static void destroyInstance();
    
    bool Init();
    void setScene2(cocos2d::Layer* pLayer);
    cocos2d::Layer* getScene2() { return pScene_; }
    
private:
    Manager();
    ~Manager();
};


