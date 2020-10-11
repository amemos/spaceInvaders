//
//  BaseGameCharacter.hpp
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 3.10.2020.
//

#ifndef BaseGameCharacter_hpp
#define BaseGameCharacter_hpp

#include "cocos2d.h"
#include "Globals.h"

using namespace cocos2d;



class BaseCharacter {

public:
    Vec2 startPos;
    E_CHARACTER_TYPE charType;
    Sprite* sprite;
    PhysicsBody* pBody;
    int pool_index;
    
    BaseCharacter(){};
    
protected:
    
    void Init(Sprite* sprite, Vec2 start_position, int life)
    {
        this->sprite = sprite;
        this->startPos = start_position;
        this->sprite->setPosition(startPos);
        this->AddPhysicBody();
    }
    
    void AddPhysicBody() {
        auto spriteSize = sprite->getContentSize();
        auto physicsBody = PhysicsBody::createBox(Size(spriteSize.width , spriteSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
        physicsBody->setDynamic(true);
        physicsBody->setContactTestBitmask(true);
        sprite->setPhysicsBody(physicsBody);
        this->pBody = physicsBody;
    }

    
public:

    Sprite* GetSprite()
    {
        return this->sprite;
    }
    
    PhysicsBody* GetPhysics()
    {
        return this->pBody;
    }
    
    E_CHARACTER_TYPE GetCharType()
    {
        return this->charType;
    }
    

    
};

#endif /* BaseGameCharacter_hpp */
