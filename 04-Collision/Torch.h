#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "define.h"
#include "LoadAnimations.h"

class CTorch : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Camera * camera);
	
	boolean isTouchable = true;
	boolean active = true;
	int state = 0;
	int ani = 0;
	int type;

public: 	
	CTorch() :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Torchani.txt", this);
	};
	boolean GetActive()
	{
		return active;
	}
	int GetState()
	{
		return state;
	}
	void SetActive(boolean a)
	{
		active = a;
	}
	void SetTouchable(boolean a)
	{
		isTouchable = a;
	}
	void SetState(int state)
	{
		this->state = state;
	}
	void SetType(int a)
	{
		type = a;
	}
};