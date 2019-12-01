#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "LoadAnimations.h"
#include "define.h"

class CAxe :public CGameObject
{
private:
	float firstPos;
	DWORD throw_timer;
	Camera* camera;
public:
	CAxe(float pos, Camera * camera, int nx) :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Axeani.txt", this);
		firstPos = pos;
		this->camera = camera;
		this->nx = nx;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render(Camera * camera);
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

