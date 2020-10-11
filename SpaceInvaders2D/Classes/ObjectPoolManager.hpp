//
//  ObjectPoolManager.hpp
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 10.10.2020.
//

#ifndef ObjectPoolManager_hpp
#define ObjectPoolManager_hpp

#include <iostream>
#include "ObjectPooler.hpp"
#include "Player.hpp"
#include "EnemyEasy.hpp"
#include "EnemyHard.hpp"
#include "Rocket.hpp"
#include "RocketPowered.hpp"
#include "Globals.h"
#include <cocos2d.h>

using namespace std;


class ObjectPoolManager
{
private:
    static ObjectPoolManager* instance;
public:
    static ObjectPoolManager* getInstance();
    
private:
    Scene* gameScene;
    array<int, _CHAR_TYPE_COUNT> pool_count;
    int pool_index;
    
public:
    ObjectPooler<Player>            player_pool;
    ObjectPooler<EnemyEasy>         e_easy_pool;
    ObjectPooler<EnemyHard>         e_hard_pool;
    ObjectPooler<Rocket>            rocket_pool;
    ObjectPooler<RocketPowered>     rocket_powered_pool;

    
    ObjectPoolManager();
    void CreateGameContent(Scene* game_scene);
    void CreateNewPool(E_CHARACTER_TYPE char_type, int pool_size);
    void DestroyGameObject(int game_object_tag, BaseCharacter* bc);
    BaseCharacter* CallGameObject(E_CHARACTER_TYPE char_type);
};

#endif /* ObjectPoolManager_hpp */
