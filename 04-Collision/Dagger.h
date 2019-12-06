#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "LoadAnimations.h"
#include "define.h"
class CDagger :public CGameObject
{
public:
	Camera* camera;
public:
	CDagger(Camera*camera, int nx) :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Daggerani.txt", this);
		this->camera = camera;
		this->nx = nx;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void Render(Camera* camera);
	void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

