#include "CEffect.h"

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (active != true)
		return;
	x += dx;
	y += dy;
	if (type == EFFECT_TYPE_DOOR)
	{
		vy = 0;
	}
	else 
	vy += (GRAVITY/2) *dt;
	if (y > camera->GetPosition().y + SCREEN_HEIGHT || x > camera->GetPosition().x + SCREEN_WIDTH || x + 17 < camera->GetPosition().x)
	{
		SetActive(false);
	}
}

void CEffect::Render(Camera* camera)
{
	if (active != true)
		return;
	int ani;
	if (type == EFFECT_TYPE_DOOR)
	{
		ani = 0;
	}
	else if (type == EFFECT_TYPE_BRICK)
	{
		ani = 1;
	}
	else if (type == EFFECT_TYPE_WATER)
	{
		ani = 2;
	}
	animations[ani]->Render(camera->transform(x, y), 255);
	RenderBoundingBox(camera);
}

void CEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	l = x;
	t = y;
	b = y + BRICK_BBOX_HEIGHT;
	r = x + BRICK_BBOX_WIDTH;
}

