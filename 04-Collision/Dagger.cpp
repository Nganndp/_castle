#include "Dagger.h"

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (active == false)
	{
		return;
	}
	if (y > camera->GetPosition().y + SCREEN_HEIGHT || x > camera->GetPosition().x + SCREEN_WIDTH || x + 17 < camera->GetPosition().x)
	{
		SetActive(false);
	}
	CGameObject::Update(dt);

	x += dx;

	if (nx > 0)
		this->vx = 0.2f;
	else
		this->vx = -0.2f;
}
void CDagger::SetState(int state) {
	CGameObject::SetState(state);


}

void CDagger::Render(Camera* camera)
{
	int ani;
	if (active == true)
	{
		if (nx > 0)
		{
			ani = 0;
		}
		else
			ani = 1;
		int alpha = 255;
		animations[ani]->Render(camera->transform(x, y), alpha);

		RenderBoundingBox(camera);
	}
}
void CDagger::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	top = y;
	left = x;
	right = x + 17;
	bottom = y + 10;
}