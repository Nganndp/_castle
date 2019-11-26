#include "Axe.h"

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (active != true)
	{
		return;
	}

	CGameObject::Update(dt);
	vx = nx * AXE_FLY_SPEED;
	vy += AXE_GRAVITY; 
	y += dy;
	x += dx;

	if (GetTickCount() - throw_start < 500)
	{
		vy = -0.0093f * dt;
		//active = false;
	}
}

void CAxe::SetState(int state) {
	CGameObject::SetState(state);


}
void CAxe::Render(Camera *camera) {
	if (active == true)
	{
		int alpha = 255;
		animations[0]->Render(x,y, alpha);

		RenderBoundingBox(camera);
	}
}
void CAxe::AdjustPos()
{
	if (simon->nx > 0)
	{
		x = simon->x- 10;
		y = simon->y - 10;
	}
	else if (simon->nx < 0)
	{
		x = simon->x + 10;
		y = simon->y - 10;
	}
}
void CAxe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (active != true)
		return;
	left = x;
	top = y;
	right = x + 17;
	bottom = y + 17;
}