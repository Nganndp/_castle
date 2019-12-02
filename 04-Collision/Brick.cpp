#include "Brick.h"

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (active != true)
		return;
	y += dy;
	if (state == BBRICK_STATE_CHIKEN || state == BBRICK_STATE_MONEY || state == BBRICK_STATE_DOUBLE_SHOOT)
	{
		vy = GRAVITY * dt;
	}
	else vy = 0;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents); float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	// block 
	x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	y += min_ty * dy + ny * 0.4f;

	if (nx != 0) vx = 0;
	if (ny != 0) vy = 0;
	if (ny == -1) { isOnGround = true; vy = 0; vx = 0; }
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CBrick::Render(Camera * camera)
{
	if (active != true)
		return;
	int ani;
	if (state == BBRICK_STATE_NORMAL || state == BBRICK_STATE_MONEY_BRICK || state == BBRICK_STATE_DOUBLE_SHOOT_BRICK)
	{
		ani = BBRICK_ANI_BRICK;
		animations[ani]->Render(camera->transform(x, y), 255);
	}
	else if (state == BBRICK_STATE_CHIKEN_BRICK)
	{
		ani = BBRICK_ANI_CHIKEN_BRICK;
		animations[ani]->Render(camera->transform(x, y), 255);
	}
	else if (state == BBRICK_STATE_MONEY)
	{
		ani = BBRICK_ANI_MONEY;
		animations[ani]->Render(camera->transform(x, y), 255);
	}
	else if (state == BBRICK_STATE_CHIKEN)
	{
		ani = BBRICK_ANI_CHIKEN;
		animations[ani]->Render(camera->transform(x, y), 255);
	}
	else if (state == BBRICK_STATE_DOUBLE_SHOOT)
	{
		ani = BBRICK_ANI_DOUBLE_SHOOT;
		animations[ani]->Render(camera->transform(x, y), 255);
	}
	RenderBoundingBox(camera);
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	b = y + BRICK_BBOX_HEIGHT;
	r = x + (BRICK_BBOX_WIDTH * multwidth);
	if (state == BBRICK_STATE_CHIKEN_BRICK)
	{
		b = y + BRICK_BBOX_HEIGHT*2;
	}
	if (state == BBRICK_STATE_MONEY || state == BBRICK_STATE_CHIKEN || state == BBRICK_STATE_DOUBLE_SHOOT)
	{
		r = x + 14;
		b = y + 14;
	}
}
