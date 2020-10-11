//
//  Enemy.hpp
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 11.10.2020.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include "BaseCharacter.hpp"

class Enemy : public BaseCharacter
{
public:
    int life;
    void Init(Vec2 start_position);
    void AddPhysicsBody();
    void HitByBullet();
    void HitByRocket();

};

#endif /* Enemy_hpp */
