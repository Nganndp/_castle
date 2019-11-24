#pragma once
#include "Enemy.h"
#include "FireBall.h"
#include "Simon.h"


class CFishmen:public CEnemy
{
public:
	CFishmen(float _firstX, CSimon* Simon);
	~CFishmen();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render(Camera *camera);
	RECT GetBound();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void SetState(int state);

	float firstX;
	bool isFalling;
	bool isAttack;
	DWORD timerAttack = 0;

protected:
	CSimon *mSimon;

};

