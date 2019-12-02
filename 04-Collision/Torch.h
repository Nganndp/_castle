#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "define.h"
#include "LoadAnimations.h"

class CTorch : public CGameObject
{
	int ani = 0;
    bool isTouchable = true;
public:

	CTorch() :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Torchani.txt", this);
		type = TORCH;
		isOnGround = false;
	};
	int GetState()
	{
		return state;
	}
	void SetState(int state)
	{
		this->state = state;
	}
	void SetType(int a)
	{
		type = a;
	}
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
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render(Camera* camera);
};