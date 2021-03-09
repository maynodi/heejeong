//
//  Scene2.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/09.
//

#include "Scene2.h"

USING_NS_CC;
using namespace std;

Scene* Scene2::createScene()
{
    Scene* pScene = Scene::create();
    
    Layer* pLayer = Scene2::create();
    pScene->addChild(pLayer);
    
    return pScene;
}

bool Scene2::init()
{
    if ( !LayerColor::initWithColor(Color4B(255,255 ,255,255)))
    {
        return false;
    }
    
    return true;
}
