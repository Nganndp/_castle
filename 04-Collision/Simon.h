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
#include "InviObjects.h"
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
	int isDamaged;
	int isUntouchable;
	int alpha;
	int numweapon;
	int startpoint;
	int endpoint;
	int untouchabletime;
	float autowalkingtime;
	bool active = true;
	bool sit = false;
	bool jumping = false;
	bool isOnStair = false;
	bool isStairUp = true;
	bool isThrowDagger = false;
	bool isThrowAxe = false;
	bool isThrowHolyWater = true;
	bool autowalkingdoor = false;
	bool isEatCross;
	bool isEatClock;
	DWORD jump_start;
	DWORD attack_start;
	DWORD sitattack_start;
	DWORD changecolor_start;
	DWORD autowalking_start;
	DWORD autowalkingdoor_start;
	DWORD isDamaged_start;
	DWORD isUntouchable_start;
public: 
	CSimon() : CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\simonani.txt", this);
		numweapon = 1;
		jump = 0;
		attack = 0;
		sitattack = 0;
		changecolor = 0;
		autowalking = 0;
		isDamaged = 0;
		isUntouchable = 0;
		isOnGround = true;
		alpha = 255;
		level = SIMON_LEVEL_MS_1;
	}
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
	int GetIsDamaged()
	{
		return isDamaged;
	}
	int GetUntouchable()
	{
		return isUntouchable;
	}
	int GetAlpha()
	{
		return alpha;
	}
	int GetNumWeapon()
	{
		return numweapon;
	}
	int GetStartPoint()
	{
		return startpoint;
	}
	int GetEndPOint()
	{
		return endpoint;
	}
	boolean GetSit()
	{
		return sit;
	}
	boolean GetOnGround()
	{
		return isOnGround;
	}
	boolean GetOnStair()
	{
		return isOnStair;
	}
	boolean GetStairUp()
	{
		return isStairUp;
	}
	boolean GetEatCross()
	{
		return isEatCross;
	}
	boolean GetEatClock()
	{
		return isEatClock;
	}
	boolean GetActive() { return active; };
	boolean GetThrowDagger() { return isThrowDagger; }
	boolean GetThrowAxe() { return isThrowAxe; }
	boolean GetThrowHolyWater() { return isThrowHolyWater; }
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
	void SetOnGround(boolean a)
	{
		isOnGround = a;
	}
	void SetAlpha(int a)
	{
		alpha = a;
	}
	void SetEatCross(bool a) {
		isEatCross = a;
	}
	void SetEatClock(bool a) {
		isEatClock = a;
	}
	void SetThrowDagger(bool a)
	{
		isThrowDagger = a;
	}
	void SetThrowAxe(bool a)
	{
		isThrowAxe = a;
	}
	void SetThrowHolyWater(bool a)
	{
		isThrowHolyWater = a;
	}
	void SetNumWeapon(int a)
	{
		numweapon = a;
	}
	void SetStartPoint(int a)
	{
		startpoint = a;
	}
	void SetEndPoint(int b)
	{
		endpoint = b;
	}
	void StartJump() { jump = 1; jump_start = GetTickCount(); }
	void StartJumpMove() { jumpmove = 1; jump_start = GetTickCount(); }
	void StartAttack() { attack = 1; attack_start = GetTickCount();
	RestartAttack();
	}
	void StartSitAttack() {
		sitattack = 1; sitattack_start = GetTickCount();
		RestartAttack();
	}
	void RestartAttack()
	{
		animations[SIMON_ANI_ATTACK_RIGHT]->SetCurrentcFrame(-1);
		animations[SIMON_ANI_ATTACK_LEFT]->SetCurrentcFrame(-1);
		animations[SIMON_ANI_SIT_ATTACK_RIGHT]->SetCurrentcFrame(-1);
		animations[SIMON_ANI_SIT_ATTACK_LEFT]->SetCurrentcFrame(-1);
	}
	void StartChangeColor() { changecolor = 1; changecolor_start = GetTickCount(); vx = 0; }
	void StartAutoWalking(float a) { autowalking = 1; autowalking_start = GetTickCount(); autowalkingtime = a; }
	void StartIsDamaged() { isDamaged = 1; isDamaged_start = GetTickCount(); RestartAttack();}
	void StartIsUnTouchable(int a) { isUntouchable = 1; isUntouchable_start = GetTickCount(); untouchabletime = a; }
	void SetSit(boolean a) { sit= a; };
	void SetJump(int a) { jump = a; }
	void StandUp();
	void SitDown();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render(Camera* camera);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};