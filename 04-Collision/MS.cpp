#include "MS.h"
#include "Game.h"
#include "Simon.h"

void CMS::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (GetTickCount() - attack_start > MS_ATTACK_TIME)
	{
		attack_start = 0;
		attack = 0;
	}
	AdjustMSPos();
	float min_tx, min_ty, nx = 0, ny;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	vector<LPGAMEOBJECT> tor;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CTorch*>(coObjects->at(i)))
			tor.push_back(coObjects->at(i));
	}
	for (UINT i = 0; i < tor.size(); i++)
	{
		CTorch* torch = dynamic_cast<CTorch*>(tor[i]);
		if (CheckOverlap(torch))
		{
			if (torch->GetState() == TORCH_STATE_NORMAL)
			{
				MSUpDropTime++;
				int a;
					srand(time(NULL));
					a = rand() % 2 + 1;
					if (MSUpDropTime < 2)
					{
						torch->SetState(3);
					}
					else   
						switch (a)
						{
						case 1:
							torch->SetState(4); break;
						case 2:
							torch->SetState(5); break;
						}
			}
		}
	}
}

void CMS::Render() {
	if (simon->vx != 0)
		{
			return;
		}
		int ani;
		if (active == true)
		{
			if (state == MS_STATE_ATTACK)
			{
				if (attack == 0)
				{
					active = false;
				}
				if (simon->nx > 0)
				{
					ani = 0;
					if (animations[ani]->GetCurrentFrame() == 3)
					{
						animations[ani]->SetCurrentcFrame(-1);
						SetActive(false);
					}
				}
				else
					ani = 1;
				if (animations[ani]->GetCurrentFrame() == 3)
				{
					animations[ani]->SetCurrentcFrame(-1);
					SetActive(false);
				}
				int alpha = 255;
				animations[ani]->Render(x, y, alpha);

				RenderBoundingBox();
			}
			if (state == MS_STATE_ATTACK_2)
			{
				if (attack == 0)
				{
					active = false;
				}
				if (simon->nx > 0)
				{
					ani = 2;
					if (animations[ani]->GetCurrentFrame() == 3)
					{
						animations[ani]->SetCurrentcFrame(-1);
						SetActive(false);
					}
				}
				else
					ani = 3;
				if (animations[ani]->GetCurrentFrame() == 3)
				{
					animations[ani]->SetCurrentcFrame(-1);
					SetActive(false);
				}
				int alpha = 255;
				animations[ani]->Render(x, y, alpha);

				RenderBoundingBox();
			}
		
		}
}

void CMS::SetState(int state) {
	CGameObject::SetState(state);
}
void CMS::AdjustMSPos()
{
	int ani;
	if (attack != 0)
	{
		if (state == MS_STATE_ATTACK)
		{
			if (simon->nx > 0)
			{
				ani = 0;
				if (animations[ani]->GetCurrentFrame() == 0) {
					x = simon->x - 7;
					y = simon->y + 2;
				}

				else if (animations[ani]->GetCurrentFrame() == 1) {
					x = simon->x - 16;
					y = simon->y;
				}

				else if (animations[ani]->GetCurrentFrame() == 2) {
					x = simon->x + 16;
					y = simon->y + 6;
				}
			}
			else if (simon->nx < 0)
			{
				ani = 1;
				if (animations[ani]->GetCurrentFrame() == 0) {
					x = simon->x + 16;
					y = simon->y;
				}

				else if (animations[ani]->GetCurrentFrame() == 1) {
					x = simon->x + 16;
					y = simon->y + 6;
				}

				else if (animations[ani]->GetCurrentFrame() == 2) {
					x = simon->x - 22;
					y = simon->y + 6;
				}
			}
		}
		if (state == MS_STATE_ATTACK_2)
		{
			if (simon->nx > 0)
			{
				ani = 2;
				if (animations[ani]->GetCurrentFrame() == 0) {
					x = simon->x - 7;
					y = simon->y + 2;
				}

				else if (animations[ani]->GetCurrentFrame() == 1) {
					x = simon->x - 16;
					y = simon->y;
				}

				else if (animations[ani]->GetCurrentFrame() == 2) {
					x = simon->x + 16;
					y = simon->y + 6;
				}
			}
			else if (simon->nx < 0)
			{
				ani = 3;
				if (animations[ani]->GetCurrentFrame() == 0) {
					x = simon->x + 16;
					y = simon->y;
				}

				else if (animations[ani]->GetCurrentFrame() == 1) {
					x = simon->x + 16;
					y = simon->y + 6;
				}

				else if (animations[ani]->GetCurrentFrame() == 2) {
					x = simon->x - 22;
					y = simon->y + 6;
				}
			}
		}
	}
}
void CMS::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (active == true)
	{
		top = y;
		left = x;
		right = x + 22;
		bottom = y + 10;
	}
}
