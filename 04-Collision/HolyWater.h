#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Game.h"
#define HW_GRAVITY 0.0002f
#define HW_STATE_BOTTLE 0
#define HW_STATE_FIRE 1

class CHW :public CGameObject
{
private:
	boolean active;
	CGameObject* simon;
	int attack;
	DWORD throw_start;
public:
	CHW() :CGameObject()
	{
		level = 1;
		attack = 0;

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void GetSimon(CGameObject* Simon) {
		this->simon = Simon;
	}
	void SetState(int state);
	void AdjustPos();
	void StartAttack() {
		active = true;
		throw_start = GetTickCount();
		AdjustPos();
	}
	bool GetActive()
	{
		return active;
	}
	void SetActive(boolean a)
	{
		active = a;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

