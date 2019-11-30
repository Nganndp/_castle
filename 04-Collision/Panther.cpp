#include "Panther.h"


CPanther::~CPanther()
{
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (active == false)
		return;
	CGameObject::Update(dt, coObjects);
	if (state == ENEMY_STATE_SHEART)
		vy = GRAVITY * dt;
	else vy += 0.001f;
		if ((x - Simon->x) < 80 && state ==ENEMY_STATE_JUMPING || (x - Simon->x) < 80 && state == ENEMY_STATE_IDLE)
		{
			SetState(ENEMY_STATE_JUMPING);
			isOnGround = false;
		}
		if (abs(jumppoint -x) >= 30 && state == ENEMY_STATE_JUMPING)
		{
			SetState(ENEMY_STATE_FALLING);
		}
		if (state == ENEMY_STATE_FALLING && isOnGround == true)
		{
			SetState(ENEMY_STATE_MOVING);
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
				vx = -0.05f;
			}
		}
		if (state == ENEMY_STATE_MOVING && vx < 0 && x <= Simon->x - (SCREEN_WIDTH/2))
		{
			x = camera->GetPosition().x;
			nx = 1;
			vx = -vx;
		}
		
		if (GetTickCount() - dietime_start > 200)
		{
			dietime_start = 0;
			die = 0;
		}
		if (state == ENEMY_STATE_DIE && die == 0)
		{
			SetState(ENEMY_STATE_SHEART);
		}
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
        CalcPotentialCollisions(coObjects, coEvents);
		if (coEvents.size() == 0)
		{
			if (!isStop)
			{
				x += dx; 
				y += dy;
			}
			isOnGround = false;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// block 		
			y += min_ty * dy + ny * 0.2f;

			if (nx == -1 || nx == 1)
			{
				x += dx;
			}

			if (ny == 1)
			{
				y += dy;
			}
			if (ny == -1)
			{
				isOnGround = true;
				vy = 0;
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CPanther::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ENEMY_STATE_DIE:
		vx = 0;
		break;
	case ENEMY_STATE_MOVING:
		if (nx < 0)
		vx = -0.23f;
		else
		vx = 0.23f;
		break;

	case ENEMY_STATE_JUMPING:
		if (nx < 0)
		{
			vy = -0.1f;
			vx = -0.12f;
		}
		else
		{
			vy = -0.1f;
			vx = 0.12f;
		}
		break;

	case ENEMY_STATE_FALLING:
		vy = 0.12f;
		break;
	}
}

void CPanther::Render(Camera* camera)
{
	if (active != true)
		return;
	int ani = 0;
	if (state == ENEMY_STATE_MOVING)
	{
		if (nx > 0)
		{
			ani = PANTHER_ANI_RUNNING_RIGHT;
		}
		else ani = PANTHER_ANI_RUNNING_LEFT;
	}
	else if (state == ENEMY_STATE_SHEART)
	{
		ani = PANTHER_ANI_SHEART;
	}
	else if (state == ENEMY_STATE_JUMPING || state == ENEMY_STATE_FALLING)
		ani = PANTHER_ANI_JUMPING;
    if (die != 0)
	{
		ani = PANTHER_ANI_DIE;
	}
	animations[ani]->Render(camera->transform(x, y), 255);
	RenderBoundingBox(camera);
}

void CPanther::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 1;
	top = y;
	right = x + 34;
	bottom = y + 18;
	if (state == ENEMY_STATE_SHEART)
	{
		right = x + SHEART_WIDTH;
		bottom = y + SHEART_HEIGHT;
	}
}
