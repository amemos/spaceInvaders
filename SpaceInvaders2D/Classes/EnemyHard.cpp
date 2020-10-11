//
//  EnemyHard.cpp
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 3.10.2020.
//

#include "EnemyHard.hpp"

EnemyHard::EnemyHard()
{
    this->life = ENEMY_LIFE_100;
    this->sprite = Sprite::create(ENEMY_HARD_SPRITE_PATH);
}

