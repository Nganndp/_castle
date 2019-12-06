#include "HolyWater.h"

void CHolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (active != true)
	{
		return;
	}

	CGameObject::Update(dt, coObjects);
	Collision(coObjects);
	if (isOnGround == false)
	{
		if (abs(x - this->firstPos) <= HW_FLY_RANGE) 
		{
			if (nx == 1)
			{
				vx = HW_SPEED;

			}
			else
			{
				vx = -HW_SPEED;
			}
			vy = -HW_GRAVITY; 

		}
		else 
		{

			if (nx == 1)
			{
				vx = HW_DROP_SPEED;
			}
			else
			{
				vx = -HW_DROP_SPEED;
			}
			vy = HW_DROP_GRAVITY;
		}
		this->SetPosition(x, y);
	}
	if (isOnGround)
	{
		if (fire_timer < HW_FIRE_TIME)
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
	right = x + HW_FIRE_WIDTH;
	bottom = y + HW_FIRE_HEIGHT;
}