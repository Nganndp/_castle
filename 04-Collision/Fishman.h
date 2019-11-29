#pragma once
#include "LoadAnimations.h"
#include "GameObject.h"
#include "Camera.h"

class CFishman :public CGameObject
{
	bool isStop = false;
	bool isFalling;
	bool isAttack;
	DWORD timerAttack = 0;
public:
	CFishman(CGameObject * Simon, Camera * camera, float movepoint) :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Fishmanani.txt", this);
		SetState(ENEMY_STATE_JUMPING);
		type = FISHMAN;
		active = true;
		isStop = false;
		this->movepoint = movepoint;
		this->Simon = Simon;
		this->camera = camera;
	};
	~CFishman();
	float movepoint;
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


