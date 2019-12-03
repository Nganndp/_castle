#include "Simon.h"

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//adjust Simon pos
	if (x < startpoint)
		x = startpoint;
	if (x > endpoint - 39)
		x = endpoint - 39;
	if (isOnStair == false)
	{
		vy += SIMON_GRAVITY * dt;
	}

	if (state != SIMON_STATE_DIE)

		//timer
		if (GetTickCount() - jump_start > SIMON_JUMP_TIME)
		{
			jump_start = 0;

		}
		else
		{
			if (GetTickCount() - jump_start < SIMON_JUMP_TIME)
			{
				if (isOnGround)
				{
					vy = -SIMON_JUMP_SPEED_Y;
					isOnGround = false;
				}
			}
		}
	if (GetTickCount() - isDamaged_start > SIMON_IS_DAMAGED_TIME)
	{
		isDamaged_start = 0;
		isDamaged = 0;
	}
	else
	{
		if (GetTickCount() - isDamaged_start < (SIMON_IS_DAMAGED_TIME/2))
		{
			if (nx > 0)
			{
				vx = -0.05f;
			}
			else { vx = 0.05f; }
			dx = vx * dt;
			if (isOnGround)
			{
			    vy = -SIMON_JUMP_SPEED_Y;
			    isOnGround = false;
		        //dx = 0;
			}
		}
		else if (GetTickCount() - isDamaged_start >= (SIMON_JUMP_TIME / 2))
		{
			dx = vx * dt;
			if (isOnGround)
			{
				SetState(SIMON_STATE_IDLE);
			}
		}
	}
	if (GetTickCount() - isUntouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		isUntouchable_start = 0;
		isUntouchable = 0;
		alpha = 255;
	}
	else
	{
		if (GetTickCount() - isUntouchable_start < SIMON_UNTOUCHABLE_TIME)
		{
			alpha = 150;
		}
	}
	if (GetTickCount() - attack_start > SIMON_ATTACK_TIME)
	{
		attack_start = 0;
		attack = 0;
	}
	if (GetTickCount() - sitattack_start > SIMON_ATTACK_TIME)
	{
		sitattack_start = 0;
		sitattack = 0;
	}
	if (GetTickCount() - changecolor_start > SIMON_EAT_TIME)
	{
		changecolor_start = 0;
		changecolor = 0;

	}
	if (GetTickCount() - autowalking_start > autowalkingtime)
	{
		autowalking_start = 0;
		autowalking = 0;

	}
	//auto walking 
	if (autowalking != 0)
	{
		vx = 0;
		vy = 0;
		if (nx > 0)
		{
			x += SIMON_AUTO_WALKING_STAIR_SPEED;
			if (isOnStair)
			{
				y += -SIMON_AUTO_WALKING_STAIR_SPEED;
			}
		}
		else if (nx < 0)
		{
			x -= SIMON_AUTO_WALKING_STAIR_SPEED;
			if (isOnStair)
			{
				y += -SIMON_AUTO_WALKING_STAIR_SPEED;
			}
		}
	}
	// No collision occured, proceed normally
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{
				x += min_tx * dx + nx * 0.4;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.4f;
				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
				if (ny == 1 && isOnStair)
				{
					y += dy;
				}
				if (nx != 0 && isOnStair)
				{
					x += dx;
				}
				if (ny == -1)
				{
					jump = 0;
					jumpmove = 0;
				}
				jump_start = 10000;
				isOnGround = true;
			}

		}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render(Camera *camera)
{
	if (active != true)
		return;
	int ani = 0;
	if (state == SIMON_STATE_DIE) {
		ani = SIMON_ANI_DIE;
	}
	else if (state == SIMON_STATE_SIT)
	{
		if (nx > 0)
		{
			ani = SIMON_ANI_SIT_RIGHT;
		}
		else ani = SIMON_ANI_SIT_LEFT;
	}
	else if (state == SIMON_STATE_IDLE)
	{
		if (isOnStair == true)
		{
			if (isStairUp == true)
			{
				if (nx > 0) ani = SIMON_ANI_UP_STAIR_IDLE_RIGHT;
				else ani = SIMON_ANI_DOWN_STAIR_IDLE_LEFT;
			}
			else if (isStairUp == false)
			{
				if (nx > 0) ani = SIMON_ANI_DOWN_STAIR_IDLE_RIGHT;
				else ani = SIMON_ANI_UP_STAIR_IDLE_LEFT;
					
			}
		}
		else if (isOnStair == false)
		{
			if (nx > 0) ani = SIMON_ANI_IDLE_RIGHT;
				else ani = SIMON_ANI_IDLE_LEFT;
		}
	}
	else if (state == SIMON_STATE_WALKING_UP_STAIR)
	{
		if (nx > 0)
		{
			ani = SIMON_ANI_WALKING_UP_STAIR_RIGHT;
		}
		else ani = SIMON_ANI_WALKING_UP_STAIR_LEFT;
	}
	else if (state == SIMON_STATE_WALKING_DOWN_STAIR)
	{
		if (nx > 0)
		{
			ani = SIMON_ANI_WALKING_DOWN_STAIR_RIGHT;
		}
		else ani = SIMON_ANI_WALKING_DOWN_STAIR_LEFT;
	}
	else if (state == SIMON_STATE_WALKING_DOWN_STAIR)
	{
		ani = SIMON_ANI_WALKING_LEFT;
	}
	else if (state == SIMON_STATE_WALKING_RIGHT)
	{
		ani = SIMON_ANI_WALKING_RIGHT;
	}
	else if (state == SIMON_STATE_WALKING_LEFT)
	{
	    ani = SIMON_ANI_WALKING_LEFT;
	}
	if (changecolor!=0)
	{
		if (nx > 0) 
			ani = SIMON_ANI_EAT_RIGHT;
		else ani = SIMON_ANI_EAT_LEFT;
	}
	if (attack != 0)
	{
		if (isOnStair == true)
		{
			if (isStairUp == true)
			{
				if (nx > 0) ani = SIMON_ANI_UP_STAIR_ATTACK_RIGHT;
				else ani = SIMON_ANI_UP_STAIR_ATTACK_LEFT;
			}
			else if (isStairUp == false)
			{
				if (nx > 0) ani = SIMON_ANI_DOWN_STAIR_ATTACK_RIGHT;
				else ani = SIMON_ANI_DOWN_STAIR_ATTACK_LEFT;
			}
		}
		else if (isOnStair == false) {
			if (nx > 0)
				ani = SIMON_ANI_ATTACK_RIGHT;
			else ani = SIMON_ANI_ATTACK_LEFT;
		}
	}
	if (sitattack != 0)
	{
		if (nx > 0)
			ani = SIMON_ANI_SIT_ATTACK_RIGHT;
		else ani = SIMON_ANI_SIT_ATTACK_LEFT;
	}
	if (jump != 0 || jumpmove !=0)
	{
		if (state == SIMON_STATE_ATTACK)
			return;
		if (nx > 0)
			ani = SIMON_ANI_JUMP_RIGHT;
		else ani = SIMON_ANI_JUMP_LEFT;
	}
	if (isDamaged)
	{
		if (nx > 0)
		{
			ani = SIMON_ANI_IS_DAMAGED_LEFT;
		}
		else ani = SIMON_ANI_IS_DAMAGED_RIGHT;
	}
	if (autowalking != 0)
	{
		ani = SIMON_ANI_WALKING_RIGHT;
		if (isOnStair)
		{
			if (nx > 0)
			{
				ani = SIMON_ANI_WALKING_UP_STAIR_RIGHT;
			}
			else if (nx < 0)
			{
				ani = SIMON_ANI_WALKING_UP_STAIR_LEFT;
			}
		}
	}
	animations[ani]->Render(camera->transform(x, y), alpha);
	RenderBoundingBox(camera);
}

void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_IDLE:
		vx = 0;
		if (isOnStair)
		{
			vy = 0;
		}
		break;
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_ATTACK:
		vx = 0;
		break;
	case SIMON_STATE_SIT:
		vx = 0;
		if (!sit) SitDown();
		break;
	case SIMON_STATE_WALKING_UP_STAIR:
		if (isStairUp == true)
			{
				vx = SIMON_WALKING_SPEED;
				vy = -SIMON_WALKING_SPEED;
				nx = 1;
			}
		else if (isStairUp == false)
			{
				vx = -SIMON_WALKING_SPEED;
				vy = -SIMON_WALKING_SPEED;
				nx = -1;
			}
		break;
	case SIMON_STATE_WALKING_DOWN_STAIR:
		if (isStairUp == false)
		{
			vx = SIMON_WALKING_SPEED;
			vy = SIMON_WALKING_SPEED;
			nx = 1;
		}
		else if (isStairUp == true)
		{
			vx = -SIMON_WALKING_SPEED;
			vy = SIMON_WALKING_SPEED;
			nx = -1;
		}
		break;
	}
}
void CSimon::SitDown() {
	y += PULL_UP_SIMON_AFTER_SITTING;
	sit = true;
}
void CSimon::StandUp()
{
	y = y - PULL_UP_SIMON_AFTER_SITTING;
	sit = false;
}
void CSimon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x + 9;
	top = y;
	right = left + SIMON_IDLE_BBOX_WIDTH;
	bottom = y + SIMON_IDLE_BBOX_HEIGHT;
	if (state == SIMON_STATE_SIT)
	{
		right = left + SIMON_IDLE_BBOX_WIDTH;
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
	}
}

