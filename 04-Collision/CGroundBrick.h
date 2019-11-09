#pragma once
#include "GameObject.h"
#include "define.h"


class CGroundBrick : public CGameObject
{
public:
	CGroundBrick() :CGameObject()
	{
	}
	boolean active = true;
	void SetActive(boolean a) { active = a; }
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

