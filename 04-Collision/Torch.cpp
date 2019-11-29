#include "Torch.h"

void CTorch::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (active == false || isTouchable != true)
	{
		return;
	}
		if (state == TORCH_STATE_NORMAL)
		{
			left = x;
			top = y;
			right = x + 16;
			bottom = y + 30;

		}
		else if (state == TORCH_STATE_LHEART || state == TORCH_STATE_CANDLE)
		{
			left = x;
			top = y;
			right = x + 15;
			bottom = y + 10;
		}
		else if (state == TORCH_STATE_SHEART || state == TORCH_STATE_DAGGER)
		{
			left = x;
			top = y;
			right = x + 9;
			bottom = y + 9;
		}
		else
		{
			left = x;
			top = y;
			right = x + 15;
			bottom = y + 17;
		}
}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (active != true)
		return;
	if (state != TORCH_STATE_NORMAL && state != TORCH_STATE_CANDLE && die ==0)
	{
		vy = GRAVITY * dt;
	if (isOnGround == false)
	    {
		if (vx < 0 && x < FirstX-15)
		{
	    	x = FirstX-15; vx = -vx;
		}
        else if (vx > 0 && x > FirstX + 15)
		{
			x = FirstX + 15; vx = -vx;
		}
		if (state == TORCH_STATE_SHEART || state == TORCH_STATE_LHEART)
		{
			vx = -0.05f;
		}
		else vx = 0;
		}
	}
	if (GetTickCount() - dietime_start > 300)
	{
		dietime_start = 0;
		die = 0;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	    // block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		if (ny == -1) { isOnGround = true; vy = 0; vx = 0; }
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CTorch::Render(Camera * camera)
{
	if (active != true)
		return;
	if (state == TORCH_STATE_NORMAL)
	{
		ani = TORCH_ANI_NORMAL;
	}
	if (state == TORCH_STATE_LHEART)
	{
		ani = TORCH_ANI_LHEART;
	}
	if (state == TORCH_STATE_SHEART)
	{
		ani = TORCH_ANI_SHEART;
	}
	if (state == TORCH_STATE_MSUP)
	{
		ani = TORCH_ANI_MSUP;
	}
	if (state == TORCH_STATE_DAGGER)
	{
		ani = TORCH_ANI_DAGGER;
	}
	if (state == TORCH_STATE_AXE)
	{
		ani = TORCH_ANI_AXE;
	}
	if (state == TORCH_STATE_CANDLE)
	{
		ani = TORCH_ANI_CANDLE;
	}
	if (state == TORCH_STATE_HOLYWATER)
	{
		ani = TORCH_ANI_HOLYWATER;
	}
	if (state == TORCH_STATE_CROSS)
	{
		ani = TORCH_ANI_CROSS;
	}
	if (state == TORCH_STATE_CLOCK)
	{
		ani = TORCH_ANI_CLOCK;
	}	
	if (state == TORCH_STATE_MONEY1)
	{
		ani = TORCH_ANI_MONEY1;
	}
	if (state == TORCH_STATE_MONEY2)
	{
		ani = TORCH_ANI_MONEY2;
	}
	if (state == TORCH_STATE_MONEY3)
	{
		ani = TORCH_ANI_MONEY3;
	}
	if (die != 0)
	{
		ani = TORCH_ANI_DESTROYED;
	}
	animations[ani]->Render(camera->transform(x,y), 255);
		RenderBoundingBox(camera);
}
