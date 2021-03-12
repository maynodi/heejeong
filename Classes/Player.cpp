//
//  TitleLobbyLayer.cpp
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#include "Player.h"

#include "KeyMgr.h"

#include "GameScene.h"
#include "Coin.h"

USING_NS_CC;

Player::Player()
    : pSprite_(nullptr)
    , originPos_(Vec2(50,100))
{
    
}

Player::~Player()
{
}

Player* Player::create()
{
    Player* pRet = new(std::nothrow) Player;
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

bool Player::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    
    this->setName("Player");
    
    pSprite_ = Sprite::create("white.png");
    pSprite_->setScale(0.2f);
    pSprite_->setColor(Color3B::RED);
    pSprite_->setPosition(originPos_);
    
    this->addChild(pSprite_);
    
    return true;
}

void Player::update(float deltaTime)
{
    move(deltaTime);
    
    collisionCheck();
}

void Player::onEnter()
{
    Node::onEnter();
    
    scheduleUpdate();
}

void Player::move(float deltaTime)
{
    Point playerPos = pSprite_->getPosition();
    float speed = 500 * deltaTime;
    
    bool isUp = KeyMgr::getInstance()->getIsMove(KEY::KEY_UP_ARROW);
    bool isDown = KeyMgr::getInstance()->getIsMove(KEY::KEY_DOWN_ARROW);
    bool isLeft = KeyMgr::getInstance()->getIsMove(KEY::KEY_LEFT_ARROW);
    bool isRight = KeyMgr::getInstance()->getIsMove(KEY::KEY_RIGHT_ARROW);
    
    if(isUp)
    {
        pSprite_->setPositionY(playerPos.y + speed);
        
        if(isLeft)
        {
            pSprite_->setPositionX(playerPos.x - speed/sqrt(2));
        }
        else if(isRight)
        {
            pSprite_->setPositionX(playerPos.x + speed/sqrt(2));
        }
    }
    else if(isDown)
    {
        pSprite_->setPositionY(playerPos.y - speed);
        
        if(isLeft)
        {
            pSprite_->setPositionX(playerPos.x - speed/sqrt(2));
        }
        else if(isRight)
        {
            pSprite_->setPositionX(playerPos.x + speed/sqrt(2));
        }
    }
    else if(isLeft)
    {
        pSprite_->setPositionX(playerPos.x - speed);
        
        if(isUp)
        {
            pSprite_->setPositionY(playerPos.y + speed/sqrt(2));
            
        }
        else if(isDown)
        {
            pSprite_->setPositionY(playerPos.y - speed/sqrt(2));
        }
    }
    else if(isRight)
    {
        pSprite_->setPositionX(playerPos.x + speed);
        
        if(isUp)
        {
            pSprite_->setPositionY(playerPos.y + speed/sqrt(2));
            
        }
        else if(isDown)
        {
            pSprite_->setPositionY(playerPos.y - speed/sqrt(2));
        }
    }
}

void Player::collisionCheck()
{
    Player* pPlayer = this;
    if(nullptr == pPlayer)
        return;
    
    GameScene* pGameScene = (GameScene*)Director::getInstance()->getRunningScene();
    Layer* pCurStage = pGameScene->getCurStage();
    
    Vector<Node*> children = pCurStage->getChildren();
    Rect playerRect = pPlayer->getSprite()->getBoundingBox();
    
    for(auto child : children)
    {
        if("Coin" == child->getName())
        {
            Rect coinRect = ((Coin*)child)->getSprite()->getBoundingBox();
            
            if(coinRect.intersectsRect(playerRect))
              {
                  ((Coin*)child)->collision();
                  return;
              }
        }
    }
}
