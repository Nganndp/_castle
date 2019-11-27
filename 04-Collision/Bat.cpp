#include "Bat.h"


CBat::~CBat()
{
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (active == false)
		return;

	if (GetTickCount() - dietime_start > 200)
	{
		dietime_start = 0;
		die = 0;
	}
	if (state != BAT_STATE_FLYING && die == 0)
	{
		state = BAT_STATE_SHEART;
	}
	if (state == BAT_STATE_FLYING)
	{
		if (isStop)
			return;
		if (nx > 0)
			x += dx;
		else
			x -= dx;

		y += dy;
	}
	if (vy < 0 && y < FirstY)
	{
		y = FirstY; vy = -vy;
	}

	if (vy > 0 && y > FirstY + 20)
	{
		y = FirstY + 20; vy = -vy;
	}
}

void CBat::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case BAT_STATE_DIE:
	case BAT_STATE_SHEART:
	case BAT_STATE_IDLE:
		vx = 0;
		break;
	}
}

void CBat::Render(Camera* camera)
{
	if (active != true)
		return;
	int ani = 0;
	if (state == BAT_STATE_FLYING)
	{
		if (nx > 0)
		{
			ani = BAT_ANI_FLYING_RIGHT;
		}
		else ani = BAT_ANI_FLYING_LEFT;
	}
	else if (state == BAT_STATE_SHEART)
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
	right = x + 16;
	bottom = y + 14;
	if (state == BAT_STATE_SHEART)
	{
		right = x + 9;
		bottom = y + 9;
	}
}

