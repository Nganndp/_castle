#pragma once
#include "Enemy.h"
#include "GameObject.h"

class CFireBall:public CEnemy
{
public:
	CFireBall();
	~CFireBall();

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render(Camera *camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	RECT GetBound();
};

