#include "Torch.h"

void CTorch::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (active == false)
	{
		return;
	}
		if (state == TORCH_STATE_NORMAL)
		{
			left = x;
			top = y;
			right = x + normalwidth;
			bottom = y + normalheight;

		}
		else if (state == TORCH_STATE_CANDLE)
		{
			left = x;
			top = y;
			right = x + candlewidth;
			bottom = y + candleheight;
		}
		else if (state == TORCH_STATE_LHEART)
		{
			left = x;
			top = y;
			right = x + lheartwidth;
			bottom = y + lheartheight;
		}
		else if (state == TORCH_STATE_DAGGER)
		{
			left = x;
			top = y;
			right = x + daggerwidth;
			bottom = y + daggerheight;
		}
		else if (state == TORCH_STATE_SHEART)
		{
			left = x;
			top = y;
			right = x + sheartswidth;
			bottom = y + sheartheight;
		}
		else if (state == TORCH_STATE_MONEY1 || state == TORCH_STATE_MONEY2 || state == TORCH_STATE_MONEY3 || state == TORCH_STATE_MONEY4)
		{
			left = x;
			top = y;
			right = x + moneywidth;
			bottom = y + moneyheight;
		}
		else
		{
			left = x;
			top = y;
			right = x + otherswidth;
			bottom = y + othersheight;
		}
}

void CTorch::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (active != true)
		return;
	if (state != TORCH_STATE_NORMAL && state != TORCH_STATE_CANDLE && state != TORCH_STATE_INVI_POT_TORCH && state != TORCH_STATE_AXE_TORCH && die ==0)
	{
		vy = GRAVITY*2 * dt;
	if (isOnGround == false)
	    {
		if (vx < 0 && x < FirstX- ENEMY_SHEART_RANGE)
		{
	    	x = FirstX- ENEMY_SHEART_RANGE; vx = -vx;
		}
        else if (vx > 0 && x > FirstX + ENEMY_SHEART_RANGE)
		{
			x = FirstX + ENEMY_SHEART_RANGE; vx = -vx;
		}
		if (state == TORCH_STATE_SHEART || state == TORCH_STATE_LHEART)
		{
			vx = ENEMY_SHEART_SPEED;
		}
		else vx = 0;
		}
	}
	if (GetTickCount() - dietime_start > ENEMY_DIE_TIME)
	{
		dietime_start = 0;
		die = 0;
	}
	Collision(coObjects);
}

void CTorch::CollisionOccurred(vector<LPGAMEOBJECT>* coObjects)
{
	if (isOnGround)
	{
		vx = 0;
	}
}

void CTorch::Render(Camera * camera)
{
	if (active != true)
		return;
	if (state == TORCH_STATE_NORMAL)
	{
		ani = TORCH_ANI_NORMAL;
	}
	if (state == TORCH_STATE_LHEART)
	{
		ani = TORCH_ANI_LHEART;
	}
	if (state == TORCH_STATE_SHEART)
	{
		ani = TORCH_ANI_SHEART;
	}
	if (state == TORCH_STATE_MSUP)
	{
		ani = TORCH_ANI_MSUP;
	}
	if (state == TORCH_STATE_DAGGER)
	{
		ani = TORCH_ANI_DAGGER;
	}
	if (state == TORCH_STATE_AXE)
	{
		ani = TORCH_ANI_AXE;
	}
	if (state == TORCH_STATE_CANDLE || state == TORCH_STATE_INVI_POT_TORCH || state == TORCH_STATE_AXE_TORCH)
	{
		ani = TORCH_ANI_CANDLE;
	}
	if (state == TORCH_STATE_HOLYWATER)
	{
		ani = TORCH_ANI_HOLYWATER;
	}
	if (state == TORCH_STATE_CROSS)
	{
		ani = TORCH_ANI_CROSS;
	}
	if (state == TORCH_STATE_CLOCK)
	{
		ani = TORCH_ANI_CLOCK;
	}	
	if (state == TORCH_STATE_MONEY1)
	{
		ani = TORCH_ANI_MONEY1;
	}
	if (state == TORCH_STATE_MONEY2)
	{
		ani = TORCH_ANI_MONEY2;
	}
	if (state == TORCH_STATE_MONEY3)
	{
		ani = TORCH_ANI_MONEY3;
	}
	if (state == TORCH_STATE_CHIKEN)
	{
		ani = TORCH_ANI_CHIKEN;
	}
	if (state == TORCH_STATE_DOUBLE_SHOOT)
	{
		ani = TORCH_ANI_DOUBLE_SHOOT;
	}
	if (state == TORCH_STATE_MONEY4)
	{
		ani = TORCH_ANI_MONEY4;
	}
	if (state == TORCH_STATE_INVI_POT)
	{
		ani = TORCH_ANI_INVI_POT;
	}
	if (die != 0)
	{
		ani = TORCH_ANI_DESTROYED;
	}
	animations[ani]->Render(camera->transform(x,y), 255);
		RenderBoundingBox(camera);
}
void CTorch::LoadElementFromFile(string source)
{
	vector<int> numbers;
	int flag = 0;
	int number;
	int arr[15];
	int simonstartx;
	int simonstarty;
	ifstream file_objects(source);
	if (file_objects.is_open())
	{
		while (!file_objects.eof())
		{
			while (file_objects >> number)
			{
				arr[flag] = number;
				flag++;
				if (flag == 14)
				{
					normalwidth = arr[0];
					normalheight = arr[1];
					candlewidth = arr[2];
					candleheight = arr[3];
					sheartswidth = arr[4];
					sheartheight = arr[5];
					lheartwidth = arr[6];
					lheartheight = arr[7];
					daggerwidth = arr[8];
					daggerheight = arr[9];
					moneywidth = arr[10];
					moneyheight = arr[11];
					otherswidth = arr[12];
					othersheight = arr[13];
					end = arr[14];
				}
			}
		}
	}
}
