#include "Dagger.h"

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) 
{
	if (active == true)
	{
		if (GetTickCount() - attack_start > SIMON_ATTACK_TIME + 300)
		{
			attack_start = 0;
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
			if (CheckOverlap(torch))
			{
				if (torch->GetState() == TORCH_STATE_NORMAL || torch->GetState() == TORCH_STATE_CANDLE)
				{
					active = false;
					torch->StartDieTime();
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
void CDagger::Render(Camera* camera)
{
	int ani;
	if (active == true)
	{
		if (simon->nx > 0)
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