#include "Fishman.h"


CFishman::~CFishman()
{
}

void CFishman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (active == false)
		return;
	CGameObject::Update(dt, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		if (!isStop)
		{
			x += dx;
			if (ny == 1) 	
				y += dy;
		}
		if (ny == -1)
		{
			y += min_ty * dy + ny * 0.2f;
			if (state == ENEMY_STATE_SHEART)
			{
					isOnGround = true; 
					vy = 0;
					vx = 0; 
			}
		}
	

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (jump != 0)
	{
		vy += -SIMON_GRAVITY*2 * dt;
	}
	else vy += TORCH_GRAVITY * dt;
	if (GetTickCount() - dietime_start > 200)
	{
		dietime_start = 0;
		die = 0;
	}
	if (GetTickCount() - jump_start > 2000)
	{
		jump_start = 0;
		jump = 0;
	}
	if (GetTickCount() - action_start > 5000)
	{
		action_start = 0;
		action = 0;
	}
	if (action == 0)
	{
		StartAction();
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
			vx = 0.052f;
		else
			vx = -0.052f;
	}
	if (state == ENEMY_STATE_MOVING)
	{
		if (vx < 0 && x < FirstX)
		{
			x = FirstX; vx = -vx;
		}

		else if (vx > 0 && x > FirstX + 20)
		{
			x = FirstX + 20; vx = -vx;
		}
    }
	if (state == ENEMY_STATE_SHEART)
	{
		if (isOnGround == false)
		{
			if (vx < 0 && x < FirstX)
			{
				x = FirstX; vx = -vx;
			}

			else if (vx > 0 && x > FirstX + 15)
			{
				x = FirstX + 15; vx = -vx;
			}
			vx = 0.05f;
		}

	}
}

void CFishman::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ENEMY_STATE_IDLE:
		vx = 0;
		break;
	}
}

void CFishman::Render(Camera* camera)
{
	//CGameObject::Render(camera);
	if (active != true)
		return;
	int ani = 0;
	if (state == ENEMY_STATE_MOVING)
	{
		if (nx > 0)
		{
			ani = FISHMAN_ANI_WALKING_RIGHT;
		}
		else ani = FISHMAN_ANI_WALKING_LEFT;
	}
	else if (state == ENEMY_STATE_SHEART)
	{
		ani = FISHMAN_ANI_SHEART;
	}
	//if (action == 0)
	//{
	//	if (nx > 0)
	//		ani = FISHMAN_ANI_ATTACK_RIGHT;
	//	else ani = FISHMAN_ANI_ATTACK_LEFT;
	//}
	if (die != 0)
	{
		ani = FISHMAN_ANI_DIE;
	}
	animations[ani]->Render(camera->transform(x, y), 255);
	RenderBoundingBox(camera);
}

void CFishman::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 1;
	top = y;
	right = x + 16;
	bottom = y + 32;
	if (state == ENEMY_STATE_SHEART)
	{
		right = x + 9;
		bottom = y + 9;
	}
}

