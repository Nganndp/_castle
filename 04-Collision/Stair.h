#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "define.h"
class Stair : public CGameObject
{
	boolean isTouchable = true;
	boolean active = true;
	int type;
public:
	Stair() :CGameObject()
	{
	}

	virtual void SetTouchable(boolean a)
	{
		isTouchable = a;
	}
	void SetType(int a)
	{
		type = a;
	}
	int GetType()
	{
		return type;
	}
	void SetActive(boolean a) { active = a; }
	virtual void Render(Camera* camera);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

