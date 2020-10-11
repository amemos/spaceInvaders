//
//  EnemyEasy.cpp
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 3.10.2020.
//

#include "EnemyEasy.hpp"

EnemyEasy::EnemyEasy()
{
    this->life = ENEMY_LIFE_50;
    this->sprite = Sprite::create(ENEMY_EASY_SPRITE_PATH);
}
