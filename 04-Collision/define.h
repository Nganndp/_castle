#pragma once
#include <string>
using namespace std;
class header
{
public:
//main
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 198

#define MAX_FRAME_RATE 120

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
#define ID_TEX_BBOX 11		

//Simon
#define SIMON_WALKING_SPEED		    0.1f 
#define SIMON_JUMP_SPEED_Y		    0.4f
#define SIMON_JUMP_DEFLECT_SPEED    0.2f
#define SIMON_GRAVITY			    0.002f
#define SIMON_DIE_DEFLECT_SPEED	    0.5f
#define PULL_UP_SIMON_AFTER_SITTING 10.0f

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_ATTACK          500
#define SIMON_STATE_SIT             600
#define SIMON_STATE_EAT_ITEM        700

#define SIMON_ANI_IDLE_RIGHT		0
#define SIMON_ANI_IDLE_LEFT			1
#define SIMON_ANI_WALKING_RIGHT		2
#define SIMON_ANI_WALKING_LEFT		3
#define SIMON_ANI_ATTACK_RIGHT		4
#define SIMON_ANI_ATTACK_LEFT		5
#define SIMON_ANI_JUMP_RIGHT        6
#define SIMON_ANI_JUMP_LEFT         7
#define SIMON_ANI_SIT_RIGHT         8
#define SIMON_ANI_SIT_LEFT          9
#define SIMON_ANI_EAT_RIGHT         10
#define SIMON_ANI_EAT_LEFT          11
#define SIMON_ANI_DIE		        99	

#define SIMON_LEVEL_MS_1            0
#define SIMON_LEVEL_MS_2            1
#define SIMON_LEVEL_MS_3            2

#define SIMON_IDLE_BBOX_WIDTH       16
#define SIMON_IDLE_BBOX_HEIGHT      30
#define SIMON_SIT_BBOX_HEIGHT       20

#define SIMON_JUMP_TIME             400
#define SIMON_ATTACK_TIME           300
#define SIMON_EAT_TIME              500

//Map
	//Torch
#define TORCH_BBOX_WIDTH 16
#define TORCH_BBOX_HEIGHT 15
#define TORCH_GRAVITY 0.0002f
#define TORCH_STATE_NORMAL 0
#define TORCH_STATE_LHEART 1
#define TORCH_STATE_SHEART 2
#define TORCH_STATE_MSUP 3
#define TORCH_STATE_DAGGER 4
#define TORCH_STATE_AXE 5

#define TORCH_ANI_NORMAL 0
#define TORCH_ANI_LHEART 1
#define TORCH_ANI_SHEART 2
#define TORCH_ANI_MSUP 3
#define TORCH_ANI_DAGHER 4
#define TORCH_ANI_AXE 5
	//Brick
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

//Wepon
   //Axe
#define AXE_GRAVITY 0.0002f
#define AXE_STATE_ATTACK 0
	//Dagger
#define DG_ATTACK_TIME 500
#define DG_FLY_SPEED 5.0f
#define DG_STATE_ATTACK_RIGHT 0
#define DG_STATE_ATTACK_LEFT 1
	//Holy Water
#define HW_GRAVITY 0.0002f
#define HW_STATE_BOTTLE 0
#define HW_STATE_FIRE 1
	//Morning Star
#define MS_ATTACK_TIME 300

#define MS_STATE_ATTACK 0
#define MS_STATE_ATTACK_2 1

#define MS_LEVEL_1 0
#define MS_LEVEL_2 1
#define MS_LEVEL_3 2

#define WHIP_ANI_NORMAL_RIGHT	0
#define WHIP_ANI_NORMAL_LEFT	1
#define WHIP_ANI_PURPLE_RIGHT	2
#define WHIP_ANI_PURPLE_LEFT	3

#define WHIP_NORMAL_BOX_WIDTH	15
#define WHIP_NORMAL_BOX_HEIGHT	15

#define WHIP_LONG_BOX_WIDTH		18
#define WHIP_LONG_BOX_HEIGHT	15
};


