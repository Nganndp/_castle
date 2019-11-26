#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Game.h"
#include "LoadAnimations.h"
#include "define.h"

class CAxe :public CGameObject
{
private:
	CGameObject* simon;
	int attack;
	DWORD throw_start;
public:
	CAxe() :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Axeani.txt", this);
		attack = 0;
		active = false;

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render(Camera * camera);
	void GetSimon(CGameObject* Simon) {
		simon = Simon;
		nx = Simon->nx;
	}
	void SetState(int state);
	void AdjustPos();
	void StartAttack() {
		throw_start = GetTickCount();
		AdjustPos();
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

