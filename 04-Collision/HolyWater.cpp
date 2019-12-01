#include "HolyWater.h"

void CHolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (active != true)
	{
		return;
	}

	CGameObject::Update(dt, colliable_objects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	if (active == true)
	{
		CalcPotentialCollisions(colliable_objects, coEvents);
	}
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		//block 	
		x += min_tx * dx;
		y += min_ty * dy + ny * 0.2f;

		if (ny == -1)
		{
			isOnGround = true;
			vy = 0;
			vx = 0;
		}

	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (isOnGround == false)
	{
		if (abs(x - this->firstPos) <= 25) 
		{
			if (nx == 1)
			{
				vx = 0.1f;

			}
			else
			{
				vx = -0.1f;
			}
			vy = -0.02f; 

		}
		else 
		{

			if (nx == 1)
			{
				vx = 0.08f;
			}
			else
			{
				vx = -0.08f;
			}
			vy = 0.14f;
		}
		this->SetPosition(x, y);
	}
	if (isOnGround)
	{
		if (fire_timer < 1000)
			fire_timer+= dt;
		else
		{
			SetActive(false);
			return;
		}
	}

}
void CHolyWater::SetState(int state) {
	CGameObject::SetState(state);


}
void CHolyWater::Render(Camera* camera) {
	if (active == true)
	{
		if (isOnGround)
			animations[HW_ANI_FIRE]->Render(camera->transform(x, y), 255);
		else
			animations[HW_ANI_BOTTLE]->Render(camera->transform(x, y),255);

		RenderBoundingBox(camera);
	}
}

void CHolyWater::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 18;
	bottom = y + 14;
}