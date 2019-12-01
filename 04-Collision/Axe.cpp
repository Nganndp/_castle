#include "Axe.h"

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (active != true)
	{
		return;
	}

	CGameObject::Update(dt);

	if (y > camera->GetPosition().y + SCREEN_HEIGHT || x > camera->GetPosition().x + SCREEN_WIDTH || x + 17 < camera->GetPosition().x)
	{
		SetActive(false);
	}
	vy += 0.0001f * dt; 
	y += dy;
	x += dx;

	if (abs(x - this->firstPos) <= 15) 
	{
		if (nx > 0)
		{
			vx = 0.0093f * dt;
		}
		else
		{
			vx = -0.0093f * dt;
		}
		vy = -0.17f;
	}
	else 
	{
		if (nx > 0)
		{
			vx = 0.0093f * dt;
		}
		else
		{
			vx = -0.0093f * dt;
		}
		if (abs(x - this->firstPos) >= 70)  
			vy = 0.15f;
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
	right = x + 17;
	bottom = y + 17;
}