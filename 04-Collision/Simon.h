#pragma once
#include <iostream>
#include <memory>
#include<vector>
#include <algorithm>
#include "Camera.h"
#include "GameObject.h"
#include "debug.h"
#include "Game.h"
#include "Torch.h"
#include "MS.h"
#include "Brick.h"
#include "LoadAnimations.h"
#include "define.h"
class CSimon: public CGameObject
{
	int jump;
	int jumpmove;
	int attack;
	int sitattack;
	int right;
	int changecolor;
	int autowalking;
	bool active = true;
	bool sit = false;
    bool onGround = true;
	bool isOnStair = false;
	bool isStairUp = true;
	bool isThrowDagger = false;
	bool isThrowAxe = false;
	CGameObject* MS;
	DWORD jump_start;
	DWORD attack_start;
	DWORD sitattack_start;
	DWORD changecolor_start;
	DWORD autowalking_start;
public: 
	CSimon() : CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\simonani.txt", this);
		jump = 0;
		attack = 0;
		sitattack = 0;
		changecolor = 0;
		autowalking = 0;
		level = SIMON_LEVEL_MS_1;
	}
	void StandUp();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render(Camera *camera);
	int GetLevel()
	{
		return level;
	}
	int GetChangeColorTime()
	{
		return changecolor;
	}
	int GetAttackTime()
	{
		return attack;
	}
	int GetJumpTime()
	{
		return jump;
	}
	int GetAutoWalkingTime()
	{
		return autowalking;
	}
	boolean GetOnGround()
	{
		return onGround;
	}
	boolean GetOnStair()
	{
		return isOnStair;
	}
	boolean GetStairUp()
	{
		return isStairUp;
	}
	boolean GetActive() { return active; };
	boolean GetThrowDagger() { return isThrowDagger; }
	boolean GetThrowAxe() { return isThrowAxe; }

	void SetState(int state);
	void SetLevel(int level) {
		CGameObject::SetLevel(level);
	};
	void SetOnStair(bool a) {
		isOnStair = a;
	};
	void SetStairUp(bool a) {
		isStairUp = a;
	};
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
	void StartJump() { jump = 1; jump_start = GetTickCount(); }
	void StartJumpMove() { jumpmove = 1; jump_start = GetTickCount(); }
	void StartAttack() { attack = 1; attack_start = GetTickCount();
	animations[SIMON_ANI_ATTACK_RIGHT]->SetCurrentcFrame(-1);
	animations[SIMON_ANI_ATTACK_LEFT]->SetCurrentcFrame(-1);
	}
	void StartSitAttack() {
		sitattack = 1; sitattack_start = GetTickCount();
		animations[SIMON_ANI_SIT_ATTACK_RIGHT]->SetCurrentcFrame(-1);
		animations[SIMON_ANI_SIT_ATTACK_LEFT]->SetCurrentcFrame(-1);
	}
	void StartChangeColor() { changecolor = 1; changecolor_start = GetTickCount(); vx = 0; }
	void StartAutoWalking() { autowalking = 1; autowalking_start = GetTickCount(); }
	void SetSit(boolean a) { sit= a; };
	void SetJump(int a) { jump = a; }
	void CheckCollisionWithGround(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};