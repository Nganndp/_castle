#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "LoadAnimations.h"
#include "Camera.h"
#include "define.h"


class CBrick : public CGameObject
{
	int multwidth;
	public:
		CBrick() :CGameObject()
		{
			LoadAnimations::LoadAnimationFromFile("ani\\Brickani.txt", this);
		}
		void SetMulwidth(int a)
		{
			multwidth = a;
		}
		boolean active = true;
		void SetActive(boolean a) { active = a; }
	virtual void Render(Camera*camera);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
