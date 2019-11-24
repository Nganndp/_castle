#pragma once
#include "Enemy.h"
#include "Simon.h"


class CPanther:public CEnemy
{
public:
	CPanther(CSimon *Simon, float _firstX);
	~CPanther();

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render(Camera *camera);
	RECT GetBound();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	CSimon *mSimon;
	void SetState(int state);
	float firstX;
};

