#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_MAP 30
#define ID_TEX_PLATFORM 40
#define ID_TEX_ENEMIES_3 50
#define ID_TEX_ENEMIES_4 60
#define ID_TEX_TILES 70
#define ID_TEX_MICS_LEFT 80
#define ID_TEX_MICS_RIGHT 90
#define ID_TEX_MARIO_NEW1 100
#define ID_TEX_TAIL_HITBOX 110
#define ID_TEX_ENEMIES_2 120





#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_BRICK_2	113
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3

#define OBJECT_TYPE_COIN	4

#define OBJECT_TYPE_BRICK_Q_COIN	1000
#define OBJECT_TYPE_BRICK_Q_MUSHROOM	2000
#define OBJECT_TYPE_BRICK_Q_LEAF	3000



#define OBJECT_TYPE_BRICK_Q_EMPTY		9
#define OBJECT_TYPE_BRICK_Q		8



#define OBJECT_TYPE_MUSHROOM	17
#define OBJECT_TYPE_PLATFORM	5

#define OBJECT_TYPE_MAP	99
#define OBJECT_TYPE_PLATFORM1	67
#define OBJECT_TYPE_LONG_PIPE	55
#define OBJECT_TYPE_PLANT_SHOOT_RED	 88
#define OBJECT_TYPE_GREEN_PLANT_SHOOT  177
#define OBJECT_TYPE_GREEN_PLANT_NOT_SHOOT  178
#define OBJECT_TYPE_PIPE_EMPTY	89
#define OBJECT_TYPE_PIPE_M_EMPTY 98
#define OBJECT_TYPE_BULLET_PLANT	130
#define OBJECT_TYPE_KOOPA_GREEN_WALKING	140

#define OBJECT_TYPE_RED_KOOPA_WALKING	150
#define OBJECT_TYPE_GREEN_KOOPA_WALKING	155

#define OBJECT_TYPE_PARA_GOOMBA	160


#define OBJECT_TYPE_PORTAL	50
#define OBJECT_TYPE_BOX	10

#define OBJECT_TYPE_CHECKFALL_KOOPA	666
#define OBJECT_TYPE_FIRE_BULLET_OF_PLANT 123

#define OBJECT_TYPE_BULLET_FIRE_RED	190
#define OBJECT_TYPE_GOOMBA_UNDER_KOOPA	192

#define OBJECT_TYPE_WHIPPING	194

#define OBJECT_TYPE_GREEN_KOOPA_INITI_WALKING	195


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#define ID_SPRITE_RACOON (ID_SPRITE_MARIO + 4000)//14000
#define ID_SPRITE_RACOON_IDLE (ID_SPRITE_RACOON + 100)//14100
#define ID_SPRITE_RACOON_IDLE_LEFT (ID_SPRITE_RACOON_IDLE + 10)//14110
#define ID_SPRITE_RACOON_IDLE_RIGHT (ID_SPRITE_RACOON_IDLE + 20)//14120

#define ID_SPRITE_RACOON_WALKING (ID_SPRITE_RACOON + 200)//14200
#define ID_SPRITE_RACOON_WALKING_LEFT (ID_SPRITE_RACOON_WALKING + 10)//14210
#define ID_SPRITE_RACOON_WALKING_RIGHT (ID_SPRITE_RACOON_WALKING + 20)//14220
#define ID_SPRITE_RACOON_RUNNING (ID_SPRITE_RACOON + 300)//14300
#define ID_SPRITE_RACOON_RUNNING_LEFT (ID_SPRITE_RACOON_RUNNING + 10)//14310
#define ID_SPRITE_RACOON_RUNNING_RIGHT (ID_SPRITE_RACOON_RUNNING + 20)//14320
#define ID_SPRITE_RACOON_JUMP (ID_SPRITE_RACOON + 400)//14400
#define ID_SPRITE_RACOON_JUMP_WALK (ID_SPRITE_RACOON_JUMP + 10)//14410
#define ID_SPRITE_RACOON_JUMP_WALK_LEFT (ID_SPRITE_RACOON_JUMP_WALK + 2)//14412
#define ID_SPRITE_RACOON_JUMP_WALK_RIGHT (ID_SPRITE_RACOON_JUMP_WALK + 6)//14416
#define ID_SPRITE_RACOON_JUMP_RUN (ID_SPRITE_RACOON_JUMP + 20)//14420
#define ID_SPRITE_RACOON_JUMP_RUN_LEFT (ID_SPRITE_RACOON_JUMP_RUN + 2)//14422
#define ID_SPRITE_RACOON_JUMP_RUN_RIGHT (ID_SPRITE_RACOON_JUMP_RUN + 6)//14426

#define ID_SPRITE_RACOON_SIT (ID_SPRITE_RACOON + 500)//14500
#define ID_SPRITE_RACOON_SIT_LEFT (ID_SPRITE_RACOON_SIT + 10)//14510
#define ID_SPRITE_RACOON_SIT_RIGHT (ID_SPRITE_RACOON_SIT + 20)//14520

#define ID_SPRITE_RACOON_BRACE (ID_SPRITE_RACOON + 600)//14600
#define ID_SPRITE_RACOON_BRACE_LEFT (ID_SPRITE_RACOON_BRACE + 10)//14610
#define ID_SPRITE_RACOON_BRACE_RIGHT (ID_SPRITE_RACOON_BRACE + 20)//14620

#define ID_SPRITE_RACOON_ATTACK (ID_SPRITE_RACOON_BRACE + 30)//14630

#pragma endregion 

#define ID_SPRITE_BRICK 20000
#define ID_SPRITE_BIN1 70001
#define ID_SPRITE_BIN2 70002

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)

#define ID_SPRITE_COIN 40000
#define ID_SPRITE_MAP 999
#define ID_SPRITE_PLATFORM1 61000


#define ID_SPRITE_BRICK_Q 20010
#define ID_SPRITE_BRICK_Q_EMPTY 21000
#define ID_SPRITE_MUSHROOM 459000
#define ID_SPRITE_LONG_PIPE 202

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)