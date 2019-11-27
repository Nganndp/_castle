#include "MS.h"

void CMS::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{

	if (GetTickCount() - attack_start > 300)
	{
		if (active == true)
			attack_start = 0;
			attack = 0;
	}
	AdjustMSPos();
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
