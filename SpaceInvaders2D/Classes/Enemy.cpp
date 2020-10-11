//
//  Enemy.cpp
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 11.10.2020.
//

#include "Enemy.hpp"



void Enemy::Init(Vec2 start_position)
{
    this->startPos = start_position;
    this->sprite->setPosition(startPos);
    this->sprite->setTag(enemyCategory);
    this->AddPhysicsBody();
}

void Enemy::HitByBullet()
{
    this->life -= 25;
    this->sprite->setOpacity(life);
}

void Enemy::HitByRocket()
{
    this->life -= 100;
}

void Enemy::AddPhysicsBody()
{
    auto spriteSize = sprite->getContentSize();
    auto physicsBody = PhysicsBody::createBox(Size(spriteSize.width , spriteSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(true);
    physicsBody->setContactTestBitmask(true);
    sprite->setPhysicsBody(physicsBody);
    this->pBody = physicsBody;

}

