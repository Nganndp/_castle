#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "LoadAnimations.h"
#include "define.h"


class CBrick : public CGameObject
{
	int type;
	int multwidth;
	public:
		CBrick() :CGameObject()
		{
			LoadAnimations::LoadAnimationFromFile("ani\\Brickani.txt", this);
		}
		void SetType(int a)
		{
			type = a;
		}void SetMulwidth(int a)
		{
			multwidth = a;
		}
		boolean active = true;
		void SetActive(boolean a) { active = a; }
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
