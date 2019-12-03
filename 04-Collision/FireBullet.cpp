#include "FireBullet.h"


CFireBullet::~CFireBullet()
{
}

void CFireBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (active == false)
		return;
	CGameObject::Update(dt, coObjects);
	x += dx; 
	if (nx > 0)
		vx = BULLET_SPEED;
	else vx = -BULLET_SPEED;
}

void CFireBullet::SetState(int state)
{
	CGameObject::SetState(state);
}

void CFireBullet::Render(Camera* camera)
{
	if (active != true)
		return;
	int ani;
	if (nx > 0)
		ani = 0;
	else ani = 1;
	animations[ani]->Render(camera->transform(x, y), 255);
	RenderBoundingBox(camera);
}

void CFireBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x ;
	top = y;
	right = x + SHEART_WIDTH;
	bottom = y + SHEART_HEIGHT;
}

