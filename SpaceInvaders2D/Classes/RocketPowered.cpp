//
//  RocketPowered.cpp
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 12.10.2020.
//

#include "RocketPowered.hpp"

RocketPowered::RocketPowered()
{
    this->sprite = Sprite::create(ROCKET_POWERFULL_SPRITE_PATH);
    this->sprite->setTag(rocketCategory);
    this->sprite->setName("POWER");
}
