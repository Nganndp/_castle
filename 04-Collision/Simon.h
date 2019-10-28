#pragma once
#include <iostream>
#include <memory>
#include<vector>
#include <algorithm>
#include "GameObject.h"
#include "debug.h"
#include "Game.h"
#include "Torch.h"
#include "MS.h"
#include "Brick.h"
#include "define.h"
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
	boolean GetOnGround()
	{
		return onGround;
	}
	boolean GetActive() { return active; };
	boolean GetThrowDagger() { return isThrowDagger; }
	boolean GetThrowAxe() { return isThrowAxe; }

	void SetState(int state);
	void SetLevel(int level) {
		CGameObject::SetLevel(level);
	};
	void SetRight(int right) {
		right = right;
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
	void StartAttack() { attack = 1; attack_start = GetTickCount(); }
	void StartChangeColor() { changecolor = 1; changecolor_start = GetTickCount(); }
	void SetSit(boolean a) { sit= a; };
	void SetJump(int a) { jump = a; }
	void CheckCollisionWithGround(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};