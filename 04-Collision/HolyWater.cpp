#include "HolyWater.h"

void CHW::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (active != true)
	{
		return;
	}

	CGameObject::Update(dt);

	vy += 0.007f;
	y += dy;
	x += dx;

	if (GetTickCount() - throw_start < (SIMON_JUMP_TIME))
	{

		vy = -0.0093f * dt;

	}
	if (simon->nx > 0)
	{
		vx = 0.005f * dt;
	}
	else if (simon->nx < 0)
		vx = -0.005f * dt;
}
void CHW::SetState(int state) {
	CGameObject::SetState(state);


}
void CHW::Render() {
	if (simon->vx != 0)
	{
		return;
	}
	if (active == true)
	{
		int alpha = 255;
		animations[0]->Render(x, y, alpha);

		RenderBoundingBox();
	}
}
void CHW::AdjustPos()
{
	if (simon->nx > 0)
	{
		x = simon->x + 16;
		y = simon->y - 5;
	}
	else if (simon->nx < 0)
	{
		x = simon->x - 16;
		y = simon->y - 5;
	}
}
void CHW::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 9;
	bottom = y + 17;
}