//
//  Globals.h
//  SpaceInvaders2D
//
//  Created by Ahmet Şentürk on 3.10.2020.
//

#ifndef Globals_h
#define Globals_h

#define PLAYER_SPRITE_PATH             "player_128.png"
#define ENEMY_EASY_SPRITE_PATH         "enemy1.png"
#define ENEMY_HARD_SPRITE_PATH         "enemy2.png"
#define ROCKET_SIMPLE_SPRITE_PATH      "bullet.png"
#define ROCKET_POWERFULL_SPRITE_PATH   "rocket.png"


#define ENEMY_LIFE_100                  100
#define ENEMY_LIFE_50                   50
#define PLAYER_LIFE                     1
#define ROWS                            2
#define COLUMNS                         5
#define ENEMY_COUNT                     ROWS * COLUMNS
#define ROCKET_POOL_COUNT               20
#define ENEMY_START_SPEED               -10

#define TYPE_COUNT_TO_BE_POOLED         5

#define ERROR_MESSAGE_POOL_SIZE         "You can not create pool much more than 'TYPE_COUNT_TO_BE_POOLED' "


typedef enum {
    _PLAYER                     = 0,
    _ENEMY_EASY                 = 100,
    _ENEMY_HARD                 = 200,
    _ROCKET_SIMPLE              = 300,
    _ROCKET_POWERFULL           = 400,
    _CHAR_TYPE_COUNT            = 5
}E_CHARACTER_TYPE;

typedef enum{
    _PLAYER_COUNT               = 1,
    _ENEMY_EASY_COUNT           = 10,
    _ENEMY_HARD_COUNT           = 10,
    _ROCKET_SIMPLE_COUNT        = 5,
    _ROCKET_POWERFULL_COUNT     = 5
}E_OBJECT_COUNTS_TO_BE_POOLED;

typedef enum{
    _ENEMY_EASY_BOUND           = _ENEMY_EASY       + _ENEMY_EASY_COUNT,
    _ENEMY_HARD_BOUND           = _ENEMY_HARD       + _ENEMY_HARD_COUNT,
    _PLAYER_BOUND               = _PLAYER           + _PLAYER_COUNT,
    _ROCKET_SIMPLE_BOUND        = _ROCKET_SIMPLE    + _ROCKET_SIMPLE_COUNT,
    _ROCKET_HARD_BOUND          = _ROCKET_POWERFULL + _ROCKET_POWERFULL_COUNT
}E_GAME_OBJECT_TAG_BOUNDS;



typedef enum {
    ON_TOUCH_RIGHT_STATE,
    ON_TOUCH_LEFT_STATE,
    END_TOUCH_STATE,
    GAME_OVER_STATE
}E_GAME_STATE;

typedef enum {
    ROCKET_SIMPLE,
    ROCKET_POWERED
}E_ROCKET_TYPE;



static const unsigned int rocketCategory        = 0x1 << 0;
static const unsigned int playerCategory        = 0x1 << 1;
static const unsigned int enemyCategory         = 0x1 << 2;
static const unsigned int spaceCategory         = 0x1 << 3;

#endif /* Globals_h */
