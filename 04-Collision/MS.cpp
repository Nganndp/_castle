#include "MS.h"

void CMS::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (GetTickCount() - attack_start > 300)
	{
		if (active == true)
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
			if (torch->GetState() == TORCH_STATE_NORMAL || torch->GetState() == TORCH_STATE_CANDLE)
			{
				MSUpDropTime++;
				int a;
					srand(time(NULL));
					a = rand() % 30 + 1;
					if (MSUpDropTime < 3)
					{
						torch->SetState(TORCH_STATE_MSUP);
					}
					else   
						switch (a)
						{
						case 1:
						case 2:
						case 3:
						case 4:
						case 5:
						case 6:
						case 7:
						case 8:
						case 9:
						case 10:
						case 11:
						case 12:
						case 13:
						case 14:
						case 15:
						case 16:
						case 17:
						case 18:
						case 19:
						case 20:
						case 21:
						case 22:
						case 23:
						case 24:
						case 25:
							torch->SetState(TORCH_STATE_SHEART); break;
						case 26:
							torch->SetState(TORCH_STATE_LHEART); break;
						case 27:
							torch->SetState(TORCH_STATE_DAGGER); break;
						case 28:
							torch->SetState(TORCH_STATE_HOLYWATER); break;
						case 29:
							torch->SetState(TORCH_STATE_CROSS); break;
						case 30:
							torch->SetState(TORCH_STATE_AXE); break;
						}
			}
		}
	}
}

void CMS::Render(Camera * camera) {
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
			animations[ani]->Render(camera->transform(x,y), alpha);

			RenderBoundingBox(camera);
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
				animations[ani]->Render(camera->transform(x,y), alpha);

				RenderBoundingBox(camera);
		}
		if (state == MS_STATE_ATTACK_3)
		{
			if (attack == 0)
			{
				active = false;
			}
			if (simon->nx > 0)
			{
				ani = 4;
				if (animations[ani]->GetCurrentFrame() == 9)
				{
					animations[ani]->SetCurrentcFrame(-1);
					SetActive(false);
				}
			}
			else
				ani = 5;
			if (animations[ani]->GetCurrentFrame() == 9)
			{
				animations[ani]->SetCurrentcFrame(-1);
				SetActive(false);
			}
			int alpha = 255;
			animations[ani]->Render(camera->transform(x,y), alpha);

			RenderBoundingBox(camera);
		}

	}
}

void CMS::SetState(int state) {
	CGameObject::SetState(state);
}
void CMS::AdjustMSPos()
{
	if (attack != 0)
	{
		if (state == MS_STATE_ATTACK || MS_STATE_ATTACK_2)
		{
			if (simon->nx > 0)
			{
				if (GetTickCount() - attack_start <= 120) {
					x = simon->x - 5;
					y = simon->y + 3.5;
				}

				else if (GetTickCount() - attack_start <= 240) {
					x = simon->x - 5;
					y = simon->y + 1;
				}

				else if (GetTickCount() - attack_start <= 360) {
					x = simon->x + 27;
					y = simon->y + 7;
				}
			}
			else if (simon->nx < 0)
			{
				if (GetTickCount() - attack_start <= 120) {
					x = simon->x + 24;
					y = simon->y + 3.5;
				}

				else if (GetTickCount() - attack_start <= 240) {
					x = simon->x + 24;
					y = simon->y + 1;
				}

				else if (GetTickCount() - attack_start <= 360) {
					x = simon->x - 22;
					y = simon->y + 7;
				}
			}
		}
		if (state == MS_STATE_ATTACK_3)
		{
			if (simon->nx > 0)
			{
				if (GetTickCount() - attack_start <= 120) {
					x = simon->x - 5;
					y = simon->y + 3.5;
				}

				else if (GetTickCount() - attack_start <= 240) {
					x = simon->x - 6;
					y = simon->y + 1;
				}

				else if (GetTickCount() - attack_start <= 360) {
					x = simon->x + 25;
					y = simon->y + 7;
				}
			}
			else if (simon->nx < 0)
			{
				if (GetTickCount() - attack_start <= 120) {
					x = simon->x + 24;
					y = simon->y + 3.5;
				}

				else if (GetTickCount() - attack_start <= 240) {
					x = simon->x + 24;
					y = simon->y + 2;
				}

				else if (GetTickCount() - attack_start <= 360) {
					x = simon->x - 28;
					y = simon->y + 7;
				}
			}
		}
	}
}
void CMS::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (active == true)
	{
		if (state == MS_STATE_ATTACK_3)
		{
			if (GetTickCount() - attack_start >= 240)
			{
				top = y;
				left = x;
				right = x + 40;
				bottom = y + 10;
			}



		}
		else if (state == MS_STATE_ATTACK || state == MS_STATE_ATTACK_2)
		{
			if (GetTickCount() - attack_start >= 240)
			{
				top = y;
				left = x;
				right = x + 24;
				bottom = y + 10;
			}
		}
	}
}
