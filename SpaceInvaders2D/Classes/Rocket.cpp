//
//  Rocket.cpp
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 5.10.2020.
//

#include "Rocket.hpp"

Rocket::Rocket()
{
    this->sprite = Sprite::create(ROCKET_SIMPLE_SPRITE_PATH);
    this->sprite->setTag(rocketCategory);
}

void Rocket::Init(Vec2 start_position)
{
    this->startPos = start_position;
    this->AddPhysicsBody();
}


Sprite* Rocket::GetSprite()
{
    return this->sprite;
}

void Rocket::SetStartPosition(Player* player)
{
    this->startPos = player->GetSprite()->getPosition();
}

void Rocket::AddPhysicsBody()
{
    auto spriteSize = sprite->getContentSize();
    auto physicsBody = PhysicsBody::createBox(Size(spriteSize.width , spriteSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(true);
    physicsBody->setContactTestBitmask(true);
    sprite->setPhysicsBody(physicsBody);
    this->pBody = physicsBody;

}
