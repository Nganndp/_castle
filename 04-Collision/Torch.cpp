#include "Torch.h"

void CTorch::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (active == false)
	{
		return;
	}
	if (isTouchable)
	{
		if (state == 0)
		{
			left = x;
			top = y;
			right = x + 16;
			bottom = x + 30;

		}
		else if(state == 3 || state == 5)
		{
			left = x;
			top = y;
			right = x+15;
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
}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//CGameObject::Update(dt, coObjects);
	if (active == true)
	{
		if (state != TORCH_STATE_NORMAL)
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
		ani = 0;
	}
	if (state == 1)
	{
		ani = 1;
	}
	if (state == 2)
	{
		ani = 2;
	}
	if (state == 3)
	{
		ani = 3;
	}
	if (state == 4)
	{
		ani = 4;
	}
	if (state == 5)
	{
		ani = 5;
	}

	animations[ani]->Render(camera->transform(x,y), 255);
		RenderBoundingBox(camera);
}
