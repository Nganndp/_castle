#pragma once
#include "LoadAnimations.h"
#include "GameObject.h"
#include "Camera.h"

class CPanther :public CGameObject
{
public:
	CPanther(CGameObject *simon, Camera *camera, float jumppoint) :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Pantherani.txt", this);
		state = ENEMY_STATE_IDLE;
		type = PANTHER;
		active = true;
		action = 0;
		isStop = false;
		Simon = simon;
		this->jumppoint = jumppoint;
		this->camera = camera;
	};
	~CPanther();
	float jumppoint;
	CGameObject* Simon;
	Camera* camera;
	bool GetStop()
	{
		return isStop;
	}
	void SetStop(bool a) { isStop = a; }
	void SetState(int state);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render(Camera* camera);
	RECT GetBound()
	{
		RECT rect;
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		return rect;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);


};


