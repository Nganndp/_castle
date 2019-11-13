#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "define.h"


class StageChanger : public CGameObject
{
public:
	StageChanger() :CGameObject()
	{
	}
	boolean active = true;
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

