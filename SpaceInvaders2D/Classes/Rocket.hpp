//
//  Rocket.hpp
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 5.10.2020.
//

#ifndef Rocket_hpp
#define Rocket_hpp

#include <stdio.h>
#include "Globals.h"
#include "cocos2d.h"
#include "Player.hpp"

using namespace cocos2d;

class Rocket : public BaseCharacter
{

    public:

        Rocket();
        void Init(Vec2 start_position);
        Sprite* GetSprite();
        void SetStartPosition(Player* player);
        void AddPhysicsBody();

};

#endif /* Rocket_hpp */
