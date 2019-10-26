#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Game.h"
#define AXE_GRAVITY 0.0002f
#define AXE_STATE_ATTACK 0

class CAxe :public CGameObject
{
private:
	boolean active;
	CGameObject* simon;
	int attack;
	DWORD throw_start;
public:
	CAxe() :CGameObject()
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

