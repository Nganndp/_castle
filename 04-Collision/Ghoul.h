#pragma once
#include "Enemy.h"
#include "LoadAnimations.h"
#include "GameObject.h"

class CGhoul:public CGameObject
{
	int die = 0;
	DWORD dietime_start;
public:
	CGhoul():CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Ghoulani.txt", this);
		state = GHOUL_STATE_WALKING;
		active = true;
		nx = -1;
	};
	~CGhoul();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render(Camera* camera);
	void StartDieTime() { die = 1; dietime_start = GetTickCount(); }
	RECT GetBound()
	{
		RECT rect;
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		return rect;
	}
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	
};


