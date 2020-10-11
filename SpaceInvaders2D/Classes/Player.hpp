//
//  Player.hpp
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 3.10.2020.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "BaseCharacter.hpp"

//using nampespace cocos2d;

class Player : public BaseCharacter{
        
    public:
        Player();
    
    void Init(Vec2 start_position);
        Sprite* GetSprite();
        void AddPhysicsBody() ;
        

};

#endif /* Player_hpp */
