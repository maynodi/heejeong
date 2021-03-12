//
//  KeyMgr.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#pragma once

#include "cocos2d.h"

class DataMgr : public cocos2d::Node
{
public:
    static DataMgr* pInstance_;
    
private:
    int score_;
    
public:
    static DataMgr* getInstance();
    static void destroyInstance();
    
public:
    bool init();
    
public:
    void addScore() { score_ += 1; }
    
public:
    int getScore() { return score_; }
    
private:
    DataMgr();
    ~DataMgr();
};


