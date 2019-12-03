#pragma once
#include "LoadAnimations.h"
#include "GameObject.h"

class CBat :public CGameObject
{
	bool isStop = false;
public:
	CBat(D3DXVECTOR2 pos) :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Batani.txt", this);
		state = ENEMY_STATE_MOVING;
		type = BAT;
		vx = BAT_SPEED_X;
		vy = BAT_SPEED_Y;
		active = true;
		FirstY = pos.y;
    };
	~CBat();
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


