#pragma once
#include "LoadAnimations.h"
#include "GameObject.h"

class CPanther :public CGameObject
{
	bool isStop = false;
	int action = 0;
	DWORD action_start;
public:
	CPanther(CGameObject *simon, float jumprange) :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Pantherani.txt", this);
		state = ENEMY_STATE_IDLE;
		type = PANTHER;
		active = true;
		action = 0;
		Simon = simon;
		this->jumprange = jumprange;
	};
	~CPanther();
	float jumprange;
	CGameObject* Simon;
	void StartAction() { action = 1; action_start = GetTickCount(); }
	bool GetStop()
	{
		return isStop;
	}
	void SetStop(bool a) { isStop = a; }
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render(Camera* camera);
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
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);


};


