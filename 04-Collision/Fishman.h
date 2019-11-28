#pragma once
#include "LoadAnimations.h"
#include "GameObject.h"

class CFishman :public CGameObject
{
	bool isStop = false;
	int jump = 0;
	DWORD jump_start;
public:
	CFishman(D3DXVECTOR2 pos) :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Fishmanani.txt", this);
		state = ENEMY_STATE_MOVING;
		type = FISHMAN;
		FirstX = pos.x;
	};
	~CFishman();
	void StartJump() { jump = 1; jump_start = GetTickCount(); }
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


