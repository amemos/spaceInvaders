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

#include "GameController.h"
#include "EnemyEasy.hpp"
#include "EnemyHard.hpp"

USING_NS_CC;



Sprite* sp_enemy_easy[ENEMY_COUNT];
Sprite* sp_enemy_hard[ENEMY_COUNT];


Label* m_scoreLabel;
Label* game_overLabel;

int frameCount = 0;
int score = 0;
float EnemySpeed = ENEMY_START_SPEED;
int hitEnemyCount = 0;
bool rocketPoweredActive = false;
float timeElapsedRocketPowered = 0;



Scene* GameController::createScene()
{
    auto scene = Scene::createWithPhysics();
        
    auto layer = GameController::create();

    scene->addChild(layer);
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SpaceInvadersScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameController::init()
{
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameController::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    // background rect
    auto selfContentSize = this->getContentSize();
    auto background = DrawNode::create();
    background->drawSolidRect(Vec2::ZERO, selfContentSize, Color4F(0.4,0.4,0.4,1.0));
    this->addChild(background);
    
    m_scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 36);
    if (m_scoreLabel == nullptr)
    {
        printf("'fonts/arial.ttf' is missing.");
    }
    else
    {
        m_scoreLabel->setPosition(Vec2(getContentSize().width - 45.f, getContentSize().height - 45.f));
        this->addChild(m_scoreLabel, 10);
    }

    
    e_game_state = END_TOUCH_STATE;
    createGameContent();

    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameController::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameController::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameController::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameController::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    scheduleUpdate();
    
    return true;
}

void GameController::createGameContent()
{
    auto selfContentSize = this->getContentSize();
    
    poolManager = ObjectPoolManager::getInstance();
    
    this->addPlayer();
    
    enemy_easy_node = Node::create();
    enemy_easy_node->setPosition(Vec2::ZERO);
    enemy_hard_node = Node::create();
    enemy_hard_node->setPosition(Vec2::ZERO);
    
    this->addEnemy(E_CHARACTER_TYPE::_ENEMY_HARD, ROWS, COLUMNS);
    this->addEnemy(E_CHARACTER_TYPE::_ENEMY_EASY, ROWS, COLUMNS);
    
    this->addChild(enemy_hard_node);
    this->addChild(enemy_easy_node);
    
    StartEnemyMove(COLUMNS,ROWS);

}


void GameController::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void GameController::addPlayer() {
    
    auto selfContentSize = this->getContentSize();
    Vec2 startPosPlayer =  Vec2(selfContentSize.width / 2, 250);

    this->player = (Player*)ObjectPoolManager::getInstance()->CallGameObject(_PLAYER);
    this->player->Init(startPosPlayer);
    this->addChild(player->GetSprite());
    
}



void GameController::addEnemy(E_CHARACTER_TYPE e_enemy_type, int rows, int columns)
{
    auto selfContentSize = this->getContentSize();

    switch (e_enemy_type) {
        case E_CHARACTER_TYPE::_ENEMY_HARD:

            for (int i = 0; i < columns; i++)
            {
                for (int j = 0; j < rows; j++)
                {
                    EnemyHard* e_hard = (EnemyHard*)ObjectPoolManager::getInstance()->CallGameObject(e_enemy_type);
                    Vec2 startPosEnemy1 = Vec2(100 * (i+1), selfContentSize.height - (100 * (j+1)));
                    e_hard->Init(startPosEnemy1);
                    enemy_hard_node->addChild(e_hard->GetSprite());
                    sp_enemy_hard[i*rows +j] = e_hard->GetSprite();
                    sp_enemy_hard[i*rows +j]->setUserData((EnemyHard*)e_hard);
                    sp_enemy_hard[i*rows +j]->setName("HARD");

                }
            }
            break;

        case E_CHARACTER_TYPE::_ENEMY_EASY:

            for (int i = 0; i < columns; i++)
            {

                for (int j = 0; j < rows; j++)
                {
                    EnemyEasy* e_easy = (EnemyEasy*)ObjectPoolManager::getInstance()->CallGameObject(e_enemy_type);
                    Vec2 startPosEnemy1 =  sp_enemy_hard[i*rows +j]->getPosition() - Vec2(0, 200);
                    e_easy->Init(startPosEnemy1);
                    enemy_easy_node->addChild(e_easy->GetSprite());
                    sp_enemy_easy[i*rows +j] = e_easy->GetSprite();
                    sp_enemy_easy[i*rows +j]->setUserData((EnemyEasy*)e_easy);
                    sp_enemy_easy[i*rows +j]->setName("EASY");
                }

            }
            break;

        default:
            break;
    }
}


void GameController::update(float dt)
{

    switch (e_game_state) {
        case ON_TOUCH_RIGHT_STATE:
            MovePlayerRight();
            break;
            
        case ON_TOUCH_LEFT_STATE:
            MovePlayerLeft();
            break;
            
        case END_TOUCH_STATE:
            //idle state
            break;
            
        case GAME_OVER_STATE:
            GameOver();
            e_game_state = END_TOUCH_STATE;
            break;
            
        default:
            break;
    }
    
    if(!rocketPoweredActive){
        if(++frameCount % 50 == 0 && e_game_state != GAME_OVER_STATE)
        {
            LaunchRocket();
        }

    }else{
        if(++frameCount % 50 == 0 && e_game_state != GAME_OVER_STATE)
        {
            LaunchRocketPowered();
        }
        timeElapsedRocketPowered += dt;
        if(timeElapsedRocketPowered > 3.0f){
            timeElapsedRocketPowered = 0;
            rocketPoweredActive = false;
        }
    }
    
}

void GameController::MovePlayerLeft()
{
    if(player->GetSprite() == nullptr)
         return;
    if(player->GetSprite()->getPosition().x > 0 + player->GetSprite()->getContentSize().width)
        player->GetSprite()->setPosition( player->GetSprite()->getPosition() - Vec2(4.0f, 0) );
}

void GameController::MovePlayerRight()
{
    if(player->GetSprite() == nullptr)
        return;
    if(player->GetSprite()->getPosition().x < 640 - player->GetSprite()->getContentSize().width)
        player->GetSprite()->setPosition( player->GetSprite()->getPosition() + Vec2(4.0f, 0) );
}

void GameController::LaunchRocket()
{

    Rocket* pr = (Rocket*)ObjectPoolManager::getInstance()->CallGameObject(_ROCKET_SIMPLE);
    
    pr->SetStartPosition(this->player);
    
    addChild(pr->GetSprite());
    pr->GetSprite()->setPosition(player->GetSprite()->getPosition() + Vec2(0,70));
    pr->GetSprite()->setUserData((Rocket*)pr);
    pr->AddPhysicsBody();
    
    int duration = 1.5;
    auto actionMove = MoveTo::create(duration, Vec2(player->GetSprite()->getPositionX(),1136));
    auto actionRemove = RemoveSelf::create();
    
    pr->GetSprite()->runAction(Sequence::create(actionMove,actionRemove, nullptr));
}

void GameController::LaunchRocketPowered()
{

    RocketPowered* pr = (RocketPowered*)ObjectPoolManager::getInstance()->CallGameObject(_ROCKET_POWERFULL);
    
    pr->SetStartPosition(this->player);
    
    addChild(pr->GetSprite());
    pr->GetSprite()->setPosition(player->GetSprite()->getPosition() + Vec2(0,70));
    pr->GetSprite()->setUserData((Rocket*)pr);
    pr->AddPhysicsBody();
    
    int duration = 1.5;
    auto actionMove = MoveTo::create(duration, Vec2(player->GetSprite()->getPositionX(),1136));
    auto actionRemove = RemoveSelf::create();
    
    pr->GetSprite()->runAction(Sequence::create(actionMove,actionRemove, nullptr));
}

void GameController::DestroyRocket(Rocket* r)
{
    ObjectPoolManager::getInstance()->DestroyGameObject(3, r);
}

void GameController::StartEnemyMove(int columns, int rows)
{
    auto selfContentSize = this->getContentSize();
    int duration = 100.0;
    auto actionRemove = RemoveSelf::create();
    auto action_easy = MoveBy::create (duration , Vec2(enemy_easy_node->getPositionX(), -1136));
    auto action_hard = MoveBy::create (duration , Vec2(enemy_hard_node->getPositionX(), -1136));
    
    enemy_hard_node->runAction(action_hard);
    enemy_easy_node->runAction(action_easy);
    
}


bool GameController::onTouchBegan(Touch *touch, Event *event)
{
    if(e_game_state == GAME_OVER_STATE) return;
    
    Point touchLoc = touch->getLocationInView();
    
    if(touchLoc.x > this->getContentSize().width / 2)
    {
        e_game_state = ON_TOUCH_RIGHT_STATE;
    }else
    {
        e_game_state = ON_TOUCH_LEFT_STATE;
    }
    
    return false;
}

void GameController::onTouchMoved(Touch *touch, Event *event)
{
    if(e_game_state == GAME_OVER_STATE) return;
    
    Point touchLoc = touch->getLocationInView();
    
    if(touchLoc.x > this->getContentSize().width / 2)
    {
        e_game_state = ON_TOUCH_RIGHT_STATE;
    }else
    {
        e_game_state = ON_TOUCH_LEFT_STATE;
    }

}

void GameController::onTouchEnded(Touch *touch, Event *event)
{
    e_game_state = END_TOUCH_STATE;
}

bool GameController::onContactBegin(const cocos2d::PhysicsContact &contact)
{
    auto NodeA = contact.getShapeA()->getBody()->getNode();
    auto NodeB = contact.getShapeB()->getBody()->getNode();
    
    if(NodeA == NULL || NodeB == NULL)
        return;
    
    int tagA = NodeA->getTag();
    int tagB = NodeB->getTag();

    if(tagA == playerCategory && tagB == enemyCategory)
    {
        ObjectPoolManager::getInstance()->DestroyGameObject(tagA, player);
        e_game_state = GAME_OVER_STATE;
        GameOver();
    }
    else if(tagA == enemyCategory && tagB == playerCategory)
    {
        ObjectPoolManager::getInstance()->DestroyGameObject(tagB, player);
        e_game_state = GAME_OVER_STATE;
        GameOver();
    }
    else if(tagA == rocketCategory && tagB == enemyCategory){
        
        Rocket* r = (Rocket*)NodeA->getUserData();

        if(NodeB->getName() == "HARD")
        {
            EnemyHard* e_h = (EnemyHard*)NodeB->getUserData();
            if(r->GetSprite()->getName() == "POWER"){
                e_h->HitByRocket();
                score += 100;
            }else{
                e_h->HitByBullet();
            }
            
            if(e_h->life <= 0){
                ObjectPoolManager::getInstance()->DestroyGameObject(_ENEMY_HARD, (EnemyHard*)NodeB->getUserData());
                hitEnemyCount++;
                if(hitEnemyCount % 5 == 0){rocketPoweredActive = true;}
            }
        }
        else if(NodeB->getName() == "EASY")
        {
            EnemyEasy* e_e = (EnemyEasy*)NodeB->getUserData();
            if(r->GetSprite()->getName() == "POWER"){
                e_e->HitByRocket();
                score += 100;
            }else{
                e_e->HitByBullet();
            }
            
            if(e_e->life <= 0){
                ObjectPoolManager::getInstance()->DestroyGameObject(_ENEMY_EASY, (EnemyEasy*)NodeB->getUserData());
                hitEnemyCount++;
                if(hitEnemyCount % 5 == 0){rocketPoweredActive = true;}
            }
        }
        
        //NodeA->removeFromParent();
        ObjectPoolManager::getInstance()->DestroyGameObject(_ROCKET_SIMPLE, r);
        score += 100;

    }
    else if(tagA == enemyCategory && tagB == rocketCategory)
    {
        Rocket* r = (Rocket*)NodeB->getUserData();
        
        if(NodeA->getName() == "HARD")
        {
            EnemyHard* e_h = (EnemyHard*)NodeA->getUserData();
            if(r->GetSprite()->getName() == "POWER"){
                e_h->HitByRocket();
                score += 100;
            }else{
                e_h->HitByBullet();
            }
            ObjectPoolManager::getInstance()->DestroyGameObject(_ENEMY_HARD, (EnemyHard*)NodeA->getUserData());
        }
            
        else if(NodeA->getName() == "EASY")
        {
            EnemyEasy* e_e = (EnemyEasy*)NodeA->getUserData();
            if(r->GetSprite()->getName() == "POWER"){
                e_e->HitByRocket();
                score += 100;
            }else{
                e_e->HitByBullet();
            }
            ObjectPoolManager::getInstance()->DestroyGameObject(_ENEMY_EASY, (EnemyEasy*)NodeA->getUserData());
        }
        
        //NodeB->removeFromParent();
        ObjectPoolManager::getInstance()->DestroyGameObject(_ROCKET_SIMPLE, r);
        score += 100;
    }
    m_scoreLabel->setString(to_string(score));
    
    return true;
}


void GameController::GameOver()
{
    
    game_overLabel = Label::createWithTTF("GAME OVER", "fonts/arial.ttf", 90);
    if (game_overLabel == nullptr)
    {
        printf("'fonts/arial.ttf' is missing.");
    }
    else
    {
        game_overLabel->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2));
        this->addChild(game_overLabel, 8);
    }
}

