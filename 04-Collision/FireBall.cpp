#include "FireBall.h"



CFireBall::CFireBall()
{
}


CFireBall::~CFireBall()
{
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isDeleted)
	{
		return;
	}

	CGameObject::Update(dt);
	x += dx;


	if (isFlip)
		this->vx = 0.08f;
	else
		this->vx = -0.08f;

}

void CFireBall::Render(Camera * camera)
{
	if (this->isDeleted)
		return;

	if (x - camera->GetPosition().x >= 290 || x - camera->GetPosition().x <= 0) 
	{
		isDeleted = true;
		return;
	}

	animations[0]->Render(camera->transform(x,y));

	RenderBoundingBox(camera);
}

void CFireBall::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 8;
	bottom = y + 6;
}

RECT CFireBall::GetBound()
{
	return CGameObject::GetBound();
}
