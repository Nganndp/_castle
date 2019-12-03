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
	if (y > camera->GetPosition().y + SCREEN_HEIGHT || x > camera->GetPosition().x + SCREEN_WIDTH || x < camera->GetPosition().x - 20)
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
		ani = EFFECT_ANI_DOOR;
	}
	else if (type == EFFECT_TYPE_BRICK)
	{
		ani = EFFECT_ANI_BRICK;
	}
	else if (type == EFFECT_TYPE_WATER)
	{
		ani = EFFECT_ANI_WATER;
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

