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
		vy = -FISHMAN_JUMP_SPEED * dt;
	if (isOnGround && state != ENEMY_STATE_SHEART && state != ENEMY_STATE_DIE)
	{
		if (!isAttack)
		{
			SetState(ENEMY_STATE_MOVING);


			if (vx < 0 && x < movepoint - FISHMAN_MOVE_LEFT_RANGE)
			{
				isFire = true;
				isAttack = true;
				nx = -1;
				x = movepoint - FISHMAN_MOVE_LEFT_RANGE; vx = -vx;
			}
			else if (vx > 0 && x > movepoint + FISHMAN_MOVE_RIGHT_RANGE)
			{
				isFire = true;
				isAttack = true;
				nx = 1;
				x = movepoint + FISHMAN_MOVE_RIGHT_RANGE; vx = -vx;
			}
		}

		else if (isAttack)
		{
			SetState(ENEMY_STATE_ATTACK);

			if (timerAttack < FISHMAN_ATTACK_TIME)
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
	if (y - camera->GetPosition().y <= 80)  
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
		if (isOnGround)
		{
			vx = 0;
		}
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
	case ENEMY_STATE_FALLING:
		vy = 0.015f * dt;
		break;
	case ENEMY_STATE_MOVING:
		if (nx == 1)
			vx = 0.03f;
		else
			vx = -0.03f;
		break;
	case ENEMY_STATE_ATTACK:
	case ENEMY_STATE_DIE:
	    vx = 0;
		break;
	case ENEMY_STATE_SHEART:
		vx = 0;
		vy = GRAVITY * dt;
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
	left = x;
	top = y;
	right = x + FISHMAN_BOX_WIDTH;
	bottom = y + FISHMAN_BOX_HEIGHT;
	if (state == ENEMY_STATE_SHEART)
	{
		right = x + SHEART_WIDTH;
		bottom = y + SHEART_HEIGHT;
	}
}

