#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "define.h"
#include "LoadAnimations.h"

class CTorch : public CGameObject
{
	int state = 0;
	int ani = 0;
	int type;

public: 	
	CTorch() :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Torchani.txt", this);
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
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render(Camera* camera);
};