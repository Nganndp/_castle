#include "Simon.h"

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (isOnStair == false)
	{
		vy += SIMON_GRAVITY * dt;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	//timer
	if (GetTickCount() - jump_start > SIMON_JUMP_TIME)
	{
		jump_start = 0;
		jump = 0;
		jumpmove = 0;

	}
	else
	{
		if (GetTickCount() - jump_start < (SIMON_JUMP_TIME))
		{
			if (onGround)
			{
				vy = -SIMON_JUMP_SPEED_Y;
				onGround = false;
			}
			else
			{
				vx = 0;
			}
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
	if (GetTickCount() - autowalking_start > SIMON_AUTO_GO_TIME)
	{
		autowalking_start = 0;
		autowalking = 0;

	}
	//auto walking 
	if (autowalking != 0)
	{
		if (nx > 0)
		{
			x += SIMON_WALKING_STAIR_SPEED;
			if (isOnStair)
			{
				y += -SIMON_WALKING_STAIR_SPEED;
			}
		}
		else if (nx < 0)
		{
			x -= SIMON_WALKING_STAIR_SPEED;
			if (isOnStair)
			{
				y += -SIMON_WALKING_STAIR_SPEED;
			}
		}
	}
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	//check overlap
	vector<LPGAMEOBJECT> tor;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CTorch*>(coObjects->at(i)))
			tor.push_back(coObjects->at(i));
	}
	for (UINT i = 0; i < tor.size(); i++)
	{
		CTorch* torch = dynamic_cast<CTorch*>(tor[i]);
		if (CheckOverlap(torch) != true)
		{
			torch->SetTouchable(true);

		}
	}
	vector<LPGAMEOBJECT> InvObjects;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<InviObjects*>(coObjects->at(i)))
			InvObjects.push_back(coObjects->at(i));
	}
	for (UINT i = 0; i < InvObjects.size(); i++)
	{
		InviObjects* InOb = dynamic_cast<InviObjects*>(InvObjects[i]);
		if (CheckOverlap(InOb) != true)
		{
			InOb->SetTouchable(true);

		}
	}
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick*>(e->obj))
			{
				// block 
				x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
				SetOnGround(true);
			}
			else if (dynamic_cast<InviObjects*>(e->obj))
			{
				if ((e->obj)->active == true)
				{
					InviObjects* InOb = dynamic_cast<InviObjects*>(e->obj);
					if (CheckOverlap(InOb) != true)
					{
						InOb->SetTouchable(false);
					}
				}
			}
			else if (dynamic_cast<CTorch*>(e->obj))
			{
				if ((e->obj)->active == true)
				{
					CTorch* tor = dynamic_cast<CTorch*>(e->obj);
					if (CheckOverlap(tor) != true)
					{
						switch (tor->GetState())
						{
						case TORCH_STATE_NORMAL:
						case TORCH_STATE_CANDLE:
							tor->SetTouchable(false); 
							break;
						case TORCH_STATE_LHEART:
							tor->SetActive(false);
							break;
						case TORCH_STATE_SHEART:
							tor->SetActive(false);
							break;
						case TORCH_STATE_MSUP:
							StartChangeColor();
							tor->SetActive(false);
							if (this->GetLevel() == SIMON_LEVEL_MS_1)
							{
								this->SetLevel(SIMON_LEVEL_MS_2);
							}
							else if (this->GetLevel() == SIMON_LEVEL_MS_2)
							{
								this->SetLevel(SIMON_LEVEL_MS_3);
							}
							break;
						case TORCH_STATE_DAGGER:
							tor->SetActive(false);
							isThrowDagger = true;
							isThrowAxe = false;
							break;
						case TORCH_STATE_AXE:
							tor->SetActive(false);
							isThrowAxe = true;
							isThrowDagger = false;
							break;
						}
					}
				}
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
    int alpha = 255;
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
	left = x + 8;
	top = y;
	right = left + SIMON_IDLE_BBOX_WIDTH;
	bottom = y + SIMON_IDLE_BBOX_HEIGHT;
	if (state == SIMON_STATE_SIT)
	{
		right = left + SIMON_IDLE_BBOX_WIDTH;
		bottom = y + SIMON_SIT_BBOX_HEIGHT;
	}
}

