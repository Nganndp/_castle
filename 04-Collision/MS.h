#pragma once
#include <cstdlib>
#include <ctime>
#include "GameObject.h"
#include "Simon.h"
#include "Torch.h"
#include "Game.h"
#include "Sprites.h"
#include "LoadAnimations.h"
#include "define.h"
class CMS :public CGameObject
{
public:
	int attack;
	CGameObject* simon;
	DWORD attack_start;
	int attackStart;
	boolean active = false;
	int level;
	int MSUpDropTime;
public:
	CMS() :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ani\\MSani.txt", this);
		attack = 0;
		MSUpDropTime = 0;

	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetActive(boolean a)
	{
		active = a;
	}
	void StartAttack() {
		attack = 1;
		attack_start = GetTickCount(); 
		animations[1]->SetCurrentcFrame(-1);
		animations[0]->SetCurrentcFrame(-1);
		animations[2]->SetCurrentcFrame(-1);
		animations[3]->SetCurrentcFrame(-1);
	}
	void GetSimon(CGameObject* Simon) {
		this->simon = Simon; 
	}
	void AdjustMSPos();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

