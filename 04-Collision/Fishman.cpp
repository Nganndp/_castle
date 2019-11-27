#include "Fishman.h"


CFishman::~CFishman()
{
}

void CFishman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (active == false)
		return;
	CGameObject::Update(dt, coObjects);

	vy += TORCH_GRAVITY * dt;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		if (!isStop)
			x += dx;

		if (!isStop)
		{
			if (ny == 1) 	
				y += dy;
		}
		if (ny == -1)
		{
			y += min_ty * dy + ny * 0.2f;
		}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


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
			vx = 0.052f;
		else
			vx = -0.052f;
	}
}

void CFishman::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ENEMY_STATE_DIE:
	case ENEMY_STATE_SHEART:
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
	if (die != 0)
	{
		ani = FISHMAN_ANI_DIE;
	}
	animations[ani]->Render(camera->transform(x, y), 255);
	RenderBoundingBox(camera);
}

void CFishman::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (jump != 0)
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
}

