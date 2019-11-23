#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "LoadAnimations.h"
#include "Camera.h"
#include "define.h"


class CBrick : public CGameObject
{
	int multwidth;
	boolean active = true;
	public:
		CBrick() :CGameObject()
		{
			LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Brickani.txt", this);
			type = BRICK;
		}
		void SetMulwidth(int a)
		{
			multwidth = a;
		}
		
		void SetActive(boolean a) { active = a; }
	virtual void Render(Camera*camera);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
