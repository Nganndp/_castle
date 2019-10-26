#pragma once
#include <cstdlib>
#include <ctime>
#include "GameObject.h"
#include "Simon.h"
#include "Torch.h"
#include "Game.h"
#include "Sprites.h"

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

