#include "Axe.h"

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (active != true)
	{
		return;
	}

	CGameObject::Update(dt);

	if (y > camera->GetPosition().y + SCREEN_HEIGHT || x > camera->GetPosition().x + SCREEN_WIDTH || x + AXE_WIDTH < camera->GetPosition().x)
	{
		SetActive(false);
	}
	vy += AXE_GRAVITY * dt; 
	y += dy;
	x += dx;

	if (abs(x - this->firstPos) <= 15) 
	{
		if (nx > 0)
		{
			vx = AXE_FLY_SPEED * dt;
		}
		else
		{
			vx = -AXE_FLY_SPEED * dt;
		}
		vy = -AXE_DROP_SPEED;
	}
	else 
	{
		if (nx > 0)
		{
			vx = AXE_FLY_SPEED * dt;
		}
		else
		{
			vx = -AXE_FLY_SPEED * dt;
		}
		if (abs(x - this->firstPos) >= AXE_FLY_RANGE)  
			vy = AXE_DROP_SPEED;
    }

	this->SetPosition(x, y);
}
void CAxe::SetState(int state) {
	CGameObject::SetState(state);


}
void CAxe::Render(Camera* camera) {
	if (active == true)
	{
		int alpha = 255;
		animations[0]->Render(camera->transform(x, y), alpha);

		RenderBoundingBox(camera);
	}
}
void CAxe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + AXE_WIDTH;
	bottom = y + AXE_HEIGHT;
}