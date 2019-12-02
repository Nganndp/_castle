#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "LoadAnimations.h"
#include "Camera.h"
#include "define.h"


class CEffect : public CGameObject
{
	Camera* camera;
	DWORD dooractive_timer;
public:
	CEffect(Camera*camera) :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Effectani.txt", this);
		this->camera = camera;
	}
	void SetType(int a)
	{
		type = a;
	}

	void SetActive(boolean a) { active = a; }
	virtual void Render(Camera* camera);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


