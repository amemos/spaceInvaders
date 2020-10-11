//
//  ObjectPoolManager.cpp
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 10.10.2020.
//

#include "ObjectPoolManager.hpp"

ObjectPoolManager* ObjectPoolManager::instance = nullptr;

ObjectPoolManager* ObjectPoolManager::getInstance()
{
    if (instance == nullptr) {
        instance = new ObjectPoolManager();
    }
    return instance;
}


ObjectPoolManager::ObjectPoolManager()
{
    
}

void ObjectPoolManager::CreateGameContent(Scene* game_scene)
{
    this->pool_count = {_PLAYER_COUNT, _ENEMY_EASY_COUNT, _ENEMY_HARD_COUNT, _ROCKET_SIMPLE_COUNT, _ROCKET_POWERFULL_COUNT};
    this->pool_index = 0;
    
    for (int i = 0; i < _CHAR_TYPE_COUNT; i++)
    {
        CreateNewPool((E_CHARACTER_TYPE)i, pool_count[i]);
    }
}

void ObjectPoolManager::CreateNewPool(E_CHARACTER_TYPE char_type, int pool_size)
{
    if(pool_index == (TYPE_COUNT_TO_BE_POOLED - 1))
    {
        cout << ERROR_MESSAGE_POOL_SIZE << endl;
        return;
    }
    
    switch (char_type) {
        case _PLAYER:
            for (int i = 0; i < pool_size; i++)
            {
                Player* p = (Player*)player_pool.createOne();
                p->GetSprite()->setTag(pool_count[pool_index] + i);
            }
            break;
        case _ENEMY_EASY:
            for (int i = 0; i < pool_size; i++)
            {
                EnemyEasy* e_e = (EnemyEasy*)e_easy_pool.createOne();
                e_e->GetSprite()->setTag(pool_count[pool_index] + i);
            }

            break;
        case _ENEMY_HARD:
            for (int i = 0; i < pool_size; i++)
            {
                EnemyHard* e_h = (EnemyHard*)e_hard_pool.createOne();
                e_h->GetSprite()->setTag(pool_count[pool_index] + i);
            }

            break;
        case _ROCKET_SIMPLE:
            for (int i = 0; i < pool_size; i++)
            {
                Rocket* r = (Rocket*)rocket_pool.createOne();
                r->GetSprite()->setTag(pool_count[pool_index] + i);
            }

            break;
        case _ROCKET_POWERFULL:
            for (int i = 0; i < pool_size; i++)
            {
                Rocket* r = (Rocket*)rocket_pool.createOne();
                r->GetSprite()->setTag(pool_count[pool_index] + i);
            }

            break;
            
        default:
            break;
    }
    pool_index++;
}

void ObjectPoolManager::DestroyGameObject(int game_object_tag, BaseCharacter* bc)
{
    E_CHARACTER_TYPE char_type_index = (E_CHARACTER_TYPE)(game_object_tag / 100);
    bc->GetSprite()->removeFromParent();
    switch (game_object_tag) {
           case _PLAYER:
            player_pool.pushBackToPool((Player*)bc);

               break;
           case _ENEMY_EASY:
            e_easy_pool.pushBackToPool((EnemyEasy*)bc);

               break;
           case _ENEMY_HARD:
            e_hard_pool.pushBackToPool((EnemyHard*)bc);

               break;
           case _ROCKET_SIMPLE:
            rocket_pool.pushBackToPool((Rocket*)bc);

               break;
           case _ROCKET_POWERFULL:
            rocket_pool.pushBackToPool((Rocket*)bc);

               break;
               
           default:
               break;
       }
    
}

BaseCharacter* ObjectPoolManager::CallGameObject(E_CHARACTER_TYPE char_type)
{
    switch (char_type) {
           case _PLAYER:
                return player_pool.createOne();
            
           case _ENEMY_EASY:
                return e_easy_pool.createOne();

           case _ENEMY_HARD:
                return e_hard_pool.createOne();
            
           case _ROCKET_SIMPLE:
                return rocket_pool.createOne();

           case _ROCKET_POWERFULL:
                return rocket_powered_pool.createOne();
            
           default:
               break;
       }

}
