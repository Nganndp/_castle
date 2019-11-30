#include "Bat.h"


CBat::~CBat()
{
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (active == false)
		return;
	CGameObject::Update(dt, coObjects);
	if (state == ENEMY_STATE_SHEART)
	{
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		y += min_ty * dy + ny * 0.2f;

		// block 
		if (nx != 1)
			x += min_tx * dx + nx * 0.2f;;

		if (nx == 1)  
			x += dx;
		if (ny == -1) { isOnGround = true; vy = 0; vx = 0; }
		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	if (GetTickCount() - dietime_start > 200)
	{
		dietime_start = 0;
		die = 0;
	}
	if (state != ENEMY_STATE_MOVING && die == 0)
	{
		state = ENEMY_STATE_SHEART;
	}
	if (state == ENEMY_STATE_MOVING)
	{
		if (isStop)
			return;
		if (nx > 0)
			x += dx;
		else
			x -= dx;

		y += dy;
		if (vy < 0 && y < FirstY)
		{
			y = FirstY; vy = -vy;
		}

		if (vy > 0 && y > FirstY + 20)
		{
			y = FirstY + 20; vy = -vy;
		}
	}
	if (state == ENEMY_STATE_SHEART)
	{
		if (isOnGround == false)
		{
			if (vx < 0 && x < FirstX - 15)
			{
				x = FirstX - 15; vx = -vx;
			}

			if (vx > 0 && x > FirstX + 15)
			{
				x = FirstX + 15; vx = -vx;
			}
			vy = GRAVITY * dt;
			vx = -0.05f;
		}
	}
}

void CBat::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
    case ENEMY_STATE_IDLE:
		vx = 0;
		break;
	}
}

void CBat::Render(Camera* camera)
{
	if (active != true)
		return;
	int ani = 0;
	if (state == ENEMY_STATE_MOVING)
	{
		if (nx > 0)
		{
			ani = BAT_ANI_FLYING_RIGHT;
		}
		else ani = BAT_ANI_FLYING_LEFT;
	}
	else if (state == ENEMY_STATE_SHEART)
	{
		ani = BAT_ANI_SHEART;
	}
	if (die != 0)
	{
		ani = BAT_ANI_DIE;
	}
	animations[ani]->Render(camera->transform(x, y), 255);
	RenderBoundingBox(camera);
}

void CBat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 1;
	top = y;
	right = x + 18;
	bottom = y + 17;
	if (state == ENEMY_STATE_SHEART)
	{
		right = x + SHEART_WIDTH;
		bottom = y + SHEART_HEIGHT;
	}
}

