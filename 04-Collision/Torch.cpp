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
		else if (state == TORCH_STATE_AXE || state == TORCH_STATE_MSUP)
		{
			left = x;
			top = y;
			right = x + 15;
			bottom = y + 17;
		}
		else
		{
			left = x;
			top = y;
			right = x + 15;
			bottom = y + 10;
		}
}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//CGameObject::Update(dt, coObjects);
	if (active == true)
	{
		if (state != TORCH_STATE_NORMAL && state != TORCH_STATE_CANDLE)
		{
			vy += TORCH_GRAVITY * dt;
		}
		CGameObject::Update(dt);
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		if (coEvents.size() == 0)
		{
			y += dy;
		}
		else
		{
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
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}

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
	animations[ani]->Render(camera->transform(x,y), 255);
		RenderBoundingBox(camera);
}
