#include "Fishman.h"


CFishman::~CFishman()
{
}

void CFishman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (active == false)
		return;
	CGameObject::Update(dt, coObjects);
	if (state == ENEMY_STATE_JUMPING)
		vy += -0.0007f * dt;
	if (state == ENEMY_STATE_FALLING)
	{
		vy += 0.0007f * dt;
	}
	else vy += 0.0001f * dt;
	if (isOnGround && state != ENEMY_STATE_SHEART && state != ENEMY_STATE_DIE)
	{
		if (isAttack == false)  
			SetState(ENEMY_STATE_MOVING);


		if (vx < 0 && x < movepoint - 10)
		{
			isAttack = true;
			nx = -1;
			x = movepoint - 10; vx = -vx;
			isFire = true;
		}
		else if (vx > 0 && x > movepoint + 50)
		{
			isAttack = true;
			nx = 1;
			x = movepoint + 50; vx = -vx;
			isFire = true;
		}


		if (isAttack)
		{
			SetState(ENEMY_STATE_ATTACK);

			if (timerAttack < 300)
			{
				timerAttack += dt;
			}
			else
			{
				isAttack = false;
				timerAttack = 0;
				if (nx == -1) 
				{
					nx = 1;
					x = movepoint;
				}
				else if (nx == 1)
				{
					nx = -1;
					x = movepoint + 35;
				}
				SetState(ENEMY_STATE_MOVING);
			}
		}
	}
	if (y - camera->GetPosition().y <= 100)  
	{
		SetState(ENEMY_STATE_FALLING);
	}
	if (state == ENEMY_STATE_FALLING)
	{
		if (isOnGround)
			this->SetState(ENEMY_STATE_MOVING);
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

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		if (!isStop)
		{
			x += dx; //dx=vx*dt
			y += dy;
		}
		isOnGround = false;
	}
	else
	{
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
			isOnGround = true;
		}

	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


}

void CFishman::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ENEMY_STATE_MOVING:
		if (nx == 1)
			vx = 0.03f;
		else
			vx = -0.03f;
		break;
	case ENEMY_STATE_ATTACK:
	case ENEMY_STATE_DIE:
	case ENEMY_STATE_SHEART:
	    vx = 0;
		break;
	}
	
}

void CFishman::Render(Camera* camera)
{
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
	else if (state == ENEMY_STATE_JUMPING || state == ENEMY_STATE_FALLING)
	{
		if (nx > 0)
			ani = FISHMAN_ANI_IDLE_RIGHT;
		else ani = FISHMAN_ANI_IDLE_LEFT;
	}
	else if (state == ENEMY_STATE_ATTACK)
	{
		if (nx > 0) ani = FISHMAN_ANI_ATTACK_RIGHT;
		else ani = FISHMAN_ANI_ATTACK_LEFT;
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

