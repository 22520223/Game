#pragma once

//
// This file contains all IDs of game assets 
//

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_ENEMY2 30
#define ID_TEX_MAP 40
#define ID_TILE 50

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_MUSHROOM 6
#define OBJECT_TYPE_LUCKYBRICK	7
#define OBJECT_TYPE_LUCKYBRICKCOIN	8
#define OBJECT_TYPE_BLOCK	9
#define OBJECT_TYPE_CHECKFALL	10
#define OBJECT_TYPE_MAP	11
#define OBJECT_TYPE_GOOMBAFLY	12
#define OBJECT_TYPE_LEAF	13
#define OBJECT_TYPE_PLANTBULLET	14
#define OBJECT_TYPE_FIRE	15
#define OBJECT_TYPE_PIPE	16
#define OBJECT_TYPE_KOOPASFLY	17
#define OBJECT_TYPE_PLANTPIRANHA	18
#define OBJECT_TYPE_BREAKABLEBRICK	19
#define OBJECT_TYPE_MAPUNDER 20
#define OBJECT_TYPE_BUTTON 21
#define OBJECT_TYPE_EFFECTS 22
#define OBJECT_TYPE_LUCKYBOXUP 23

#define OBJECT_TYPE_PORTAL	50

enum SCENE
{
	SCENE_MENU = 0,
	SCENE_1 = 1,
	SCENE_2 = 2
};

#define ID_SPRITE_TILE 0

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

#define ID_SPRITE_MARIO_SUPER (ID_SPRITE_MARIO + 4000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SUPER + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SUPER_WALKING (ID_SPRITE_MARIO_SUPER + 200)
#define ID_SPRITE_MARIO_SUPER_WALKING_LEFT (ID_SPRITE_MARIO_SUPER_WALKING + 10)
#define ID_SPRITE_MARIO_SUPER_WALKING_RIGHT (ID_SPRITE_MARIO_SUPER_WALKING + 20)
#define ID_SPRITE_MARIO_SUPER_RUNNING (ID_SPRITE_MARIO_SUPER + 300)
#define ID_SPRITE_MARIO_SUPER_RUNNING_LEFT (ID_SPRITE_MARIO_SUPER_RUNNING + 10)
#define ID_SPRITE_MARIO_SUPER_RUNNING_RIGHT (ID_SPRITE_MARIO_SUPER_RUNNING + 20)
#define ID_SPRITE_MARIO_SUPER_JUMP (ID_SPRITE_MARIO_SUPER + 400)
#define ID_SPRITE_MARIO_SUPER_JUMP_WALK (ID_SPRITE_MARIO_SUPER_JUMP + 10)
#define ID_SPRITE_MARIO_SUPER_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SUPER_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SUPER_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SUPER_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SUPER_JUMP_RUN (ID_SPRITE_MARIO_SUPER_JUMP + 20)
#define ID_SPRITE_MARIO_SUPER_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SUPER_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SUPER_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SUPER_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_SUPER_SIT (ID_SPRITE_MARIO_SUPER + 500)
#define ID_SPRITE_MARIO_SUPER_SIT_LEFT (ID_SPRITE_MARIO_SUPER_SIT + 10)
#define ID_SPRITE_MARIO_SUPER_SIT_RIGHT (ID_SPRITE_MARIO_SUPER_SIT + 20)
#define ID_SPRITE_MARIO_SUPER_BRACE (ID_SPRITE_MARIO_SUPER + 600)
#define ID_SPRITE_MARIO_SUPER_BRACE_LEFT (ID_SPRITE_MARIO_SUPER_BRACE + 10)
#define ID_SPRITE_MARIO_SUPER_BRACE_RIGHT (ID_SPRITE_MARIO_SUPER_BRACE + 20)
#define ID_SPRITE_MARIO_SUPER_HIT (ID_SPRITE_MARIO_SUPER + 700)
#define ID_SPRITE_MARIO_SUPER_HIT_LEFT (ID_SPRITE_MARIO_SUPER_HIT + 10)
#define ID_SPRITE_MARIO_SUPER_HIT_RIGHT (ID_SPRITE_MARIO_SUPER_HIT + 20)
#define ID_SPRITE_MARIO_SUPER_HIT_FORWARD (ID_SPRITE_MARIO_SUPER_HIT + 30)
#define ID_SPRITE_MARIO_SUPER_HIT_BACKWARD (ID_SPRITE_MARIO_SUPER_HIT + 40)
#define ID_SPRITE_MARIO_SUPER_FLY (ID_SPRITE_MARIO_SUPER + 800)
#define ID_SPRITE_MARIO_SUPER_FLY_LEFT (ID_SPRITE_MARIO_SUPER_FLY + 10)
#define ID_SPRITE_MARIO_SUPER_FLY_RIGHT (ID_SPRITE_MARIO_SUPER_FLY + 20)
#define ID_SPRITE_MARIO_SUPER_FLY_LEFT_SLOW (ID_SPRITE_MARIO_SUPER_FLY + 30)
#define ID_SPRITE_MARIO_SUPER_FLY_RIGHT_SLOW (ID_SPRITE_MARIO_SUPER_FLY + 40)

#pragma endregion 

#define ID_SPRITE_BRICK 20000

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)

#define ID_SPRITE_COIN 40000

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)

#define ID_SPRITE_MUSHROOM 60000
#define ID_SPRITE_MUSHROOM_WALK (ID_SPRITE_MUSHROOM + 1000)

#define ID_SPRITE_LUCKYBRICK 70000
#define ID_SPRITE_LUCKYBRICK_STATE1 (ID_SPRITE_LUCKYBRICK+10)
#define ID_SPRITE_LUCKYBRICK_STATE2 (ID_SPRITE_LUCKYBRICK+20)
#define ID_SPRITE_LUCKYBRICK_STATE3 (ID_SPRITE_LUCKYBRICK+30)
#define ID_SPRITE_LUCKYBRICK_STATE4 (ID_SPRITE_LUCKYBRICK+40)
#define ID_SPRITE_LUCKYBRICK_STATE5 (ID_SPRITE_LUCKYBRICK+50)

#define ID_SPRITE_BLOCK 90000
#define ID_SPRITE_BLOCK_STATE (ID_SPRITE_BLOCK+10)

#define ID_SPRITE_KOOPAS 100000
#define ID_SPRITE_KOOPAS_LEFT (ID_SPRITE_KOOPAS + 20)
#define ID_SPRITE_KOOPAS_RIGHT (ID_SPRITE_KOOPAS + 10)
#define ID_SPRITE_KOOPAS_IDLE (ID_SPRITE_KOOPAS + 30)
#define ID_SPRITE_KOOPAS_IDLE_RIGHT (ID_SPRITE_KOOPAS + 40)
#define ID_SPRITE_KOOPAS_IDLE_LEFT (ID_SPRITE_KOOPAS + 50)

#define ID_SPRITE_MAP 110000
#define ID_SPRITE_MAP (ID_SPRITE_KOOPAS + 10)

#define ID_SPRITE_GOOMBAFLY 120000
#define ID_SPRITE_GOOMBAFLY_WALK (ID_SPRITE_GOOMBAFLY + 10)
#define ID_SPRITE_GOOMBAFLY_FLY (ID_SPRITE_GOOMBAFLY + 20)

#define ID_SPRITE_LEAF 130000
#define ID_SPRITE_LEAF_FALL (ID_SPRITE_LEAF + 10)

#define ID_SPRITE_PLANTBULLET 140000
#define ID_SPRITE_PLANTBULLET_TOP_LEFT (ID_SPRITE_PLANTBULLET + 10)
#define ID_SPRITE_PLANTBULLET_BOT_LEFT (ID_SPRITE_PLANTBULLET + 30)
#define ID_SPRITE_PLANTBULLET_TOP_RIGHT (ID_SPRITE_PLANTBULLET + 20)
#define ID_SPRITE_PLANTBULLET_BOT_RIGHT (ID_SPRITE_PLANTBULLET + 40)
#define ID_SPRITE_PLANTBULLET_UP_LEFT (ID_SPRITE_PLANTBULLET + 50)
#define ID_SPRITE_PLANTBULLET_UP_RIGHT (ID_SPRITE_PLANTBULLET + 60)

#define ID_SPRITE_FIRE 150000
#define ID_SPRITE_FIRE1 (ID_SPRITE_FIRE + 10)
#define ID_SPRITE_FIRE2 (ID_SPRITE_FIRE + 20)
#define ID_SPRITE_FIRE3 (ID_SPRITE_FIRE + 30)
#define ID_SPRITE_FIRE4 (ID_SPRITE_FIRE + 40)

#define ID_SPRITE_PIPE 160000
#define ID_SPRITE_PIPE_IDLE (ID_SPRITE_PIPE + 10)

#define ID_SPRITE_KOOPASFLY 170000
#define ID_SPRITE_KOOPASFLY_LEFT (ID_SPRITE_KOOPASFLY + 20)
#define ID_SPRITE_KOOPASFLY_RIGHT (ID_SPRITE_KOOPASFLY + 10)
#define ID_SPRITE_KOOPASFLY (ID_SPRITE_KOOPASFLY + 30)

#define ID_SPRITE_PIRANHA 180000
#define ID_SPRITE_PIRANHA_UP_DOWN (ID_SPRITE_PIRANHA + 10)

#define ID_SPRITE_BREAKABLEBRICK 190000

#define ID_SPRITE_PLANTFORM 200000

#define ID_SPRITE_BUTTON 210000

#define ID_SPRITE_EFFECTS 220000
#define ID_SPRITE_POINT_100 (ID_SPRITE_EFFECTS + 10)
#define ID_SPRITE_POINT_200 (ID_SPRITE_EFFECTS + 20)
#define ID_SPRITE_POINT_400 (ID_SPRITE_EFFECTS + 30)
#define ID_SPRITE_POINT_800 (ID_SPRITE_EFFECTS + 40)
#define ID_SPRITE_POINT_1000 (ID_SPRITE_EFFECTS + 50)
#define ID_SPRITE_POINT_2000 (ID_SPRITE_EFFECTS + 60)
#define ID_SPRITE_POINT_4000 (ID_SPRITE_EFFECTS + 70)
#define ID_SPRITE_POINT_8000 (ID_SPRITE_EFFECTS + 80)