#pragma once
#include <string>
using namespace std;
class header
{
public:
	//main
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 255
#define SPAWN_DELAY_TIMER 15000
#define STOP_ENEMY_TIMER 5000
#define SHEART_WIDTH 8
#define SHEART_HEIGHT 8

#define MAX_FRAME_RATE 120
#define GRAVITY 0.0015f
#define ID_TEX_SIMON 1
#define ID_TEX_MISC 2
#define ID_TEX_TORCH 3
#define ID_TEX_DAGGERR 4
#define ID_TEX_DAGGERL 5
#define ID_TEX_LHEART 6
#define ID_TEX_SHEART 7
#define ID_TEX_MSUP 8
#define ID_TEX_AXE 9
#define ID_TEX_ENTRANCESTAGE 10
#define ID_TEX_CASTLE 11
#define ID_TEX_UNDERGROUND 12
#define ID_TEX_BBOX 13	
#define ID_TEX_ENEMY 14

//Source file
#define SOURCE_ENTRANCE_PNG L"textures\\entrance_tilemap.png"
#define SOURCE_ENTRANCE_TXT "ReadFile\\Map\\entrance.txt"
#define SOURCE_CASTLE_PNG L"textures\\castle_tilemap.png"
#define SOURCE_CASTLE_TXT "ReadFile\\Map\\castle.txt"

//Simon
#define SIMON_WALKING_SPEED		    0.05f 
#define	SIMON_AUTO_WALKING_STAIR_SPEED   0.2f
#define SIMON_JUMP_SPEED_X			0.12f
#define SIMON_JUMP_SPEED_Y		    0.22f
#define SIMON_JUMP_DEFLECT_SPEED    0.1f
#define SIMON_GRAVITY			    0.001f
#define SIMON_DIE_DEFLECT_SPEED	    0.5f
#define PULL_UP_SIMON_AFTER_SITTING 8

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_ATTACK          500
#define SIMON_STATE_SIT             600
#define SIMON_STATE_EAT_ITEM        700
#define SIMON_STATE_SIT_ATTACK      800
#define SIMON_STATE_ON_STAIR_ATTACK 101
#define SIMON_STATE_ON_STAIR_IDLE   102
#define SIMON_STATE_WALKING_UP_STAIR 103
#define SIMON_STATE_WALKING_DOWN_STAIR 104

#define SIMON_ANI_IDLE_RIGHT		    0
#define SIMON_ANI_IDLE_LEFT			    1
#define SIMON_ANI_WALKING_RIGHT		    2
#define SIMON_ANI_WALKING_LEFT		    3
#define SIMON_ANI_ATTACK_RIGHT		    4
#define SIMON_ANI_ATTACK_LEFT		    5
#define SIMON_ANI_JUMP_RIGHT            6
#define SIMON_ANI_JUMP_LEFT             7
#define SIMON_ANI_SIT_RIGHT             8
#define SIMON_ANI_SIT_LEFT              9
#define SIMON_ANI_EAT_RIGHT             10
#define SIMON_ANI_EAT_LEFT              11
#define SIMON_ANI_SIT_ATTACK_RIGHT      12
#define SIMON_ANI_SIT_ATTACK_LEFT       13
#define SIMON_ANI_UP_STAIR_IDLE_RIGHT   14
#define SIMON_ANI_UP_STAIR_IDLE_LEFT    15
#define SIMON_ANI_DOWN_STAIR_IDLE_RIGHT 16
#define SIMON_ANI_DOWN_STAIR_IDLE_LEFT  17
#define SIMON_ANI_WALKING_UP_STAIR_RIGHT 18
#define SIMON_ANI_WALKING_UP_STAIR_LEFT  19
#define SIMON_ANI_WALKING_DOWN_STAIR_RIGHT 20
#define SIMON_ANI_WALKING_DOWN_STAIR_LEFT 21
#define SIMON_ANI_UP_STAIR_ATTACK_RIGHT 22
#define SIMON_ANI_UP_STAIR_ATTACK_LEFT  23
#define SIMON_ANI_DOWN_STAIR_ATTACK_RIGHT 24
#define SIMON_ANI_DOWN_STAIR_ATTACK_LEFT  25
#define SIMON_ANI_IS_DAMAGED_LEFT 26
#define SIMON_ANI_IS_DAMAGED_RIGHT 27
#define SIMON_ANI_DIE		            99	

#define SIMON_LEVEL_MS_1            0
#define SIMON_LEVEL_MS_2            1
#define SIMON_LEVEL_MS_3            2

#define SIMON_IDLE_BBOX_WIDTH       12
#define SIMON_IDLE_BBOX_HEIGHT      30
#define SIMON_SIT_BBOX_HEIGHT       22

#define SIMON_JUMP_TIME             500
#define SIMON_ATTACK_TIME           300
#define SIMON_EAT_TIME              500
#define SIMON_AUTO_GO_TIME          1200
#define SIMON_AUTO_GO_SCENE1          1000
#define SIMON_UNTOUCHABLE_TIME  3000
#define	SIMON_IS_DAMAGED_TIME 450

//Map
#define BRICK 0
#define BREAKABLE_BRICK 2
#define TORCH 1
#define STAGECHANGER 3
    //Brick
#define BRICK_STATE_NORMAL -1
#define BBRICK_STATE_MONEY_BRICK 0
#define BBRICK_STATE_CHIKEN_BRICK 1
#define BBRICK_STATE_DOUBLE_SHOOT_BRICK 2
#define BBRICK_STATE_NORMAL 3
#define BBRICK_STATE_MONEY 4
#define BBRICK_STATE_CHIKEN 5
#define BBRICK_STATE_DOUBLE_SHOOT 6

#define BBRICK_ANI_BRICK 0
#define BBRICK_ANI_CHIKEN_BRICK 1
#define BBRICK_ANI_MONEY 2
#define BBRICK_ANI_CHIKEN 3
#define BBRICK_ANI_DOUBLE_SHOOT 4
	//Torch
#define TORCH_STATE_NORMAL 0
#define TORCH_STATE_LHEART 1
#define TORCH_STATE_SHEART 2
#define TORCH_STATE_MSUP 3
#define TORCH_STATE_DAGGER 4
#define TORCH_STATE_AXE 5
#define TORCH_STATE_CANDLE 6
#define TORCH_STATE_HOLYWATER 7
#define TORCH_STATE_CROSS 8
#define TORCH_STATE_CLOCK 9
#define TORCH_STATE_MONEY1 10
#define TORCH_STATE_MONEY2 11
#define TORCH_STATE_MONEY3 12
#define TORCH_STATE_CHIKEN 13
#define TORCH_STATE_DOUBLE_SHOOT 14
#define TORCH_STATE_MONEY4 15

#define TORCH_ANI_NORMAL 0
#define TORCH_ANI_LHEART 1
#define TORCH_ANI_SHEART 2
#define TORCH_ANI_MSUP 3
#define TORCH_ANI_DAGGER 4
#define TORCH_ANI_AXE 5
#define TORCH_ANI_CANDLE 6
#define TORCH_ANI_HOLYWATER 7
#define TORCH_ANI_CROSS 8
#define TORCH_ANI_CLOCK 9
#define TORCH_ANI_MONEY1 10
#define TORCH_ANI_MONEY2 11
#define TORCH_ANI_MONEY3 12
#define TORCH_ANI_DESTROYED 13
#define TORCH_ANI_CHIKEN 14
#define TORCH_ANI_DOUBLE_SHOOT 15
#define TORCH_ANI_MONEY4 16
	//Brick
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16
#define BRICK_TYPE_NORMAL 0
#define BRICK_TYPE_GROUND 1

//Invisible Objects
#define INVI_WIDTH 10
#define INVI_HEIGHT 10
	//Stage Changer
#define SC_TYPE_CHANGE_SCENE 1006
#define SC_TYPE_DOOR 1001
#define SC_TYPE_UNDER_GROUND 1002
#define SC_TYPE_DOOR_BOSS 1003
#define SC_TYPE_AUTO_HELPER 1004
#define SC_TYPE_AUTO_CLOSE_DOOR 1005
#define SC_TYPE_UNDER_TO_LAND 1007
	//Stair
#define STAIR_TYPE_RIGHT_UP_HELPER 99
#define STAIR_TYPE_LEFT_UP_HELPER -99
#define STAIR_TYPE_UP_RIGHT 100
#define STAIR_TYPE_DOWN_LEFT -100
#define STAIR_TYPE_UP_LEFT 101
#define STAIR_TYPE_DOWN_RIGHT -101
    //Enemy Spawner
#define GHOUL_SPAWNER 50
#define BAT_SPAWNER 51
#define FISHMAN_SPAWNER 52
#define PANTHER_SPAWNER 53
    //Money Spawner
#define MONEY_SPAWNER 54

//Wepon
   //Axe
#define AXE_GRAVITY  0.007f; 
#define AXE_FLY_SPEED 0.1f
#define AXE_STATE_ATTACK 0
	//Dagger
#define DG_ATTACK_TIME 500
#define DG_FLY_SPEED 3.0f
#define DG_STATE_ATTACK_RIGHT 0
#define DG_STATE_ATTACK_LEFT 1
	//Holy Water
#define HW_GRAVITY 0.0002f
#define HW_STATE_BOTTLE 0
#define HW_STATE_FIRE 1
#define HW_ANI_BOTTLE 0
#define HW_ANI_FIRE 1
	//Morning Star
#define MS_ATTACK_TIME 300

#define MS_STATE_ATTACK 0
#define MS_STATE_ATTACK_2 1
#define MS_STATE_ATTACK_3 2

#define MS_LEVEL_1 0
#define MS_LEVEL_2 1
#define MS_LEVEL_3 2

#define WHIP_NORMAL_BOX_WIDTH	15
#define WHIP_NORMAL_BOX_HEIGHT	15

#define WHIP_LONG_BOX_WIDTH		18
#define WHIP_LONG_BOX_HEIGHT	15

//Enemy
#define GHOUL 2000
#define PANTHER 2001
#define BAT 2002
#define FISHMAN 2003
#define FIREBULLET 2004

#define ENEMY_STATE_MOVING 0
#define ENEMY_STATE_DIE 1
#define ENEMY_STATE_IDLE 2
#define ENEMY_STATE_SHEART 3
#define ENEMY_STATE_JUMPING 4
#define ENEMY_STATE_FALLING 5
#define ENEMY_STATE_ATTACK 6

//Ghoul
#define GHOUL_ANI_IDLE_RIGHT 0
#define GHOUL_ANI_IDLE_LEFT 1
#define GHOUL_ANI_WALKING_RIGHT 2
#define GHOUL_ANI_WALKING_LEFT 3
#define GHOUL_ANI_DIE 4
#define GHOUL_ANI_SHEART 5

//Bat
#define BAT_ANI_IDLE_RIGHT 0
#define BAT_ANI_IDLE_LEFT 1
#define BAT_ANI_FLYING_RIGHT 2
#define BAT_ANI_FLYING_LEFT 3
#define BAT_ANI_DIE 4
#define BAT_ANI_SHEART 5

//Fishman
#define FISHMAN_ANI_IDLE_RIGHT 0
#define FISHMAN_ANI_IDLE_LEFT 1
#define FISHMAN_ANI_WALKING_RIGHT 2
#define FISHMAN_ANI_WALKING_LEFT 3
#define FISHMAN_ANI_DIE 4
#define FISHMAN_ANI_SHEART 5
#define FISHMAN_ANI_ATTACK_RIGHT 6
#define FISHMAN_ANI_ATTACK_LEFT 7

//Panther
#define PANTHER_ANI_IDLE 0
#define PANTHER_ANI_RUNNING_RIGHT 1
#define PANTHER_ANI_RUNNING_LEFT 2
#define PANTHER_ANI_JUMPING 3
#define PANTHER_ANI_DIE 4
#define PANTHER_ANI_SHEART 5

   //Effect
#define EFFECT_TYPE_DOOR 1
#define EFFECT_TYPE_WATER 2
#define EFFECT_TYPE_BRICK 3
#define EFFECT_ANI_DOOR 0
#define EFFECT_ANI_WATER 2
#define EFFECT_ANI_BRICK 1
};


