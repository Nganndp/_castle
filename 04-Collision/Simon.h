#pragma once
#include <iostream>
#include <memory>
#include "GameObject.h"
#include "MS.h"
#include "Brick.h"

#define SIMON_WALKING_SPEED		    0.1f 
#define SIMON_JUMP_SPEED_Y		    0.5f
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

#define SIMON_JUMP_TIME             500
#define SIMON_ATTACK_TIME           300
#define SIMON_EAT_TIME              500


class CSimon: public CGameObject
{
	int jump;
	int attack;
	int right;
	int changecolor;
	bool active = true;
	bool sit = false;
    bool onGround = true;
	bool isThrowDagger = false;
	bool isThrowAxe = true;
	CGameObject* MS;
	DWORD jump_start;
	DWORD attack_start;
	DWORD changecolor_start;
public: 
	CSimon() : CGameObject()
	{
		jump = 0;
		attack = 0;
		changecolor = 0;
		level = SIMON_LEVEL_MS_1;
		sit = false;
	}
	void StandUp();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int level) {
		CGameObject::SetLevel(level);
	};
	void SetRight(int right) {
		right = right;
	};
	void GetPlusLevel()
	{
		this->level++;
	}
	int GetLevel()
	{
		return level;
	}
	boolean GetActive() { return active; };
	boolean GetThrowDagger() { return isThrowDagger; }
	boolean GetThrowAxe() { return isThrowAxe; }
	void SetActive(boolean a) {
		active = a;
	}
	void SetMS(CGameObject* MS)
	{
		this->MS = MS;

	}
	void SetOnGround(boolean a)
	{
		onGround = a;
	}
	int GetChangeColorTime()
	{
		return changecolor;
	}
	boolean GetOnGround()
	{
		return onGround;
	}
	void StartJump() { jump = 1; jump_start = GetTickCount(); }
	void StartAttack() { attack = 1; attack_start = GetTickCount(); }
	void StartChangeColor() { changecolor = 1; changecolor_start = GetTickCount(); }
	void SetSit(boolean a) { sit= a; };
	void CheckCollisionWithGround(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};