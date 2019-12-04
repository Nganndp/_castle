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
	if (state == ENEMY_STATE_IDLE)
	{
		vy = 0;
	}
	if (state == ENEMY_STATE_MOVING)
	{
		vy = PANTHER_GRAVITY;
	}
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
				if (vx < 0 && x < FirstX - ENEMY_SHEART_RANGE)
				{
					x = FirstX - ENEMY_SHEART_RANGE; vx = -vx;
				}

				if (vx > 0 && x > FirstX + ENEMY_SHEART_RANGE)
				{
					x = FirstX + ENEMY_SHEART_RANGE; vx = -vx;
				}
				vx = ENEMY_SHEART_SPEED;
			}
		}
		if (vx < 0 && x <= camera->GetPosition().x)
		{
			x = camera->GetPosition().x;
			nx = 1;
			vx = -vx;
		}
		
		if (GetTickCount() - dietime_start > ENEMY_DIE_TIME)
		{
			dietime_start = 0;
			die = 0;
		}
		if (state == ENEMY_STATE_DIE && die == 0)
		{
			SetState(ENEMY_STATE_SHEART);
		}
		Collision(coObjects);
}

void CPanther::CollisionOccurred(vector<LPGAMEOBJECT>* coObjects)
{

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
		vx = -PANTHER_SPEED;
		else
		vx = PANTHER_SPEED;
		break;

	case ENEMY_STATE_JUMPING:
		vy = PANTHER_JUMP_SPEED_Y;
		if (nx < 0)
		{
			vx = -PANTHER_JUMP_SPEED_X;
		}
		else
		{
			vx = PANTHER_JUMP_SPEED_X;
		}
		break;

	case ENEMY_STATE_FALLING:
		vy = PANTHER_JUMP_SPEED_X;
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
	left = x;
	top = y;
	right = x + 34;
	bottom = y + 15;
	if (state == ENEMY_STATE_SHEART)
	{
		right = x + SHEART_WIDTH;
		bottom = y + SHEART_HEIGHT;
	}
}
