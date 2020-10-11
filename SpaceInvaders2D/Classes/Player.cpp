//
//  Player.cpp
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 3.10.2020.
//

#include "Player.hpp"

Player::Player()
{
    this->sprite = Sprite::create(PLAYER_SPRITE_PATH);
}

void Player::Init(Vec2 start_position)
{

    this->charType = _PLAYER;
    this->startPos = start_position;
    this->sprite->setPosition(startPos);
    this->sprite->setTag(playerCategory);
    this->AddPhysicBody();

};


Sprite* Player::GetSprite()
{
    return this->sprite;
}


void Player::AddPhysicsBody()
{
    auto spriteSize = sprite->getContentSize();
    auto physicsBody = PhysicsBody::createBox(Size(spriteSize.width , spriteSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(true);
    physicsBody->setContactTestBitmask(true);
    sprite->setPhysicsBody(physicsBody);
    this->pBody = physicsBody;

}
