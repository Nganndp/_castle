#include "Dagger.h"
#include "Simon.h"

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	if (active = true)
	{
		    if (GetTickCount() - attack_start > SIMON_ATTACK_TIME + 300)
			{
				attack_start = 0;
				active = false;
				waiting = false;
			}
			vx = nx * DG_FLY_SPEED;
			x += vx;
		vector<LPGAMEOBJECT> tor;
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CTorch*>(coObjects->at(i)))
				tor.push_back(coObjects->at(i));
		}
		for (UINT i = 0; i < tor.size(); i++)
		{
			CTorch* torch = dynamic_cast<CTorch*>(tor[i]);
			if (CheckCollision(torch))
			{
				this->SetPosition(-100, 0);
				this->SetActive(false);
				int a;
				srand(time(NULL));
				a = rand() % 2 + 1;
				switch (a)
				{
				case 1:
					torch->SetState(2); break;
				case 2:
					torch->SetState(5); break;
				}
			}
		}
	}
}
void CDagger::SetState(int state) {
	CGameObject::SetState(state);


}
void CDagger::AdjustPos()
{
	if (simon->nx > 0)
	{
			x = simon->x;
			y = simon->y;
	}
	else if (simon->nx < 0)
	{
			x = simon->x;
			y = simon->y;
	}
}
void CDagger::Render() {
	if (simon->vx != 0)
	{
		return;
	}
	int ani;
	if (active == true)
	{
		if (attack == 0)
		{
			active = false;
		}
		if (simon->nx > 0)
		{
			ani = 0;
		}
		else
			ani = 1;
		int alpha = 255;
		animations[ani]->Render(x, y, alpha);

		RenderBoundingBox();
	}
}
void CDagger::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	top = y;
		left = x;
		right = x + 17;
		bottom = y + 10;
}