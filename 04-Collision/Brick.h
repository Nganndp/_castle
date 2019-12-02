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
			LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Brickani.txt", this);
			type = BRICK;
			state = BRICK_STATE_NORMAL;
		}
		void SetMulwidth(int a)
		{
			multwidth = a;
		}
		void SetType(int a)
		{
			type = a;
		}
	void SetActive(boolean a) { active = a; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render(Camera*camera);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
