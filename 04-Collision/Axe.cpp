#include "Axe.h"

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (active != true)
	{
		return;
	}

	CGameObject::Update(dt);

	vy += 0.007f; 
	y += dy;
	x += dx;

	if (GetTickCount() - throw_start < 500)
	{
		
		vy = -0.0093f * dt;
		
	}
	if (simon->nx > 0)
	{
		vx =  0.005f * dt;
	}
	else if(simon->nx < 0)
		vx = -0.005f * dt;
	}
void CAxe::SetState(int state) {
	CGameObject::SetState(state);


}
void CAxe::Render(Camera *camera) {
	if (simon->vx != 0)
	{
		return;
	}
	if (active == true)
	{
		int alpha = 255;
		animations[0]->Render(camera->transform(x,y), alpha);

		RenderBoundingBox(camera);
	}
}
void CAxe::AdjustPos()
{
	if (simon->nx > 0)
	{
		x = simon->x;
		y = simon->y + 5;
	}
	else if (simon->nx < 0)
	{
		x = simon->x;
		y = simon->y+ 5;
	}
}
void CAxe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + 17;
	bottom = y + 17;
}