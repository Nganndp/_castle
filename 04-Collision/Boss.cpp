#include "Boss.h"


CBoss::~CBoss()
{
}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!active)
		return;
	CGameObject::Update(dt, coObjects);
	CheckCollisionWeapon();
	CheckCollisionSimon();
	CollisionWhenDead(coObjects);
	DeleateWaeponWhenUnactive();

	if (x <= camera->GetPosition().x)
		vx = -vx;
	if (x >= camera->GetPosition().x + SCREEN_WIDTH - BOSS_WIDTH)
		vx = -vx;
	if (y <= BOSS_ATTACK_HEIGHT)
		vy = 0;
	if (GetTickCount() - dietime_start > 600)
	{
		dietime_start = 0;
		die = 0;
	}
	if (state == BOSS_STATE_DIE && die == 0)
	{
		SetPosition(FirstX, FirstY);
		state = BOSS_STATE_BLOOD;
	}
	if (state == BOSS_STATE_BLOOD)
	{
		if (isOnGround == false)
		{
			vy = GRAVITY * dt;
		}
	}
	if (Simon->GetPosition().x > x&& state == BOSS_STATE_SLEEP)
	{
		state = BOSS_STATE_AWAKEN;
	}
	if (y <= 100 && state == BOSS_STATE_ATTACK && isWait == true)
	{
		state = BOSS_STATE_FLY;
	}
	if (x >= FirstX-10 && x <= FirstX+20 && state == BOSS_STATE_FLY)
	{
		isWait = false;
		vx = 0;
		state = BOSS_STATE_ATTACK;
	}
	if (state == BOSS_STATE_AWAKEN)
	{
		if (y <= BOSS_ATTACK_HEIGHT)
		{
			vy = BOSS_AWAKEN_SPEED_Y;
		}
		else
		{
			vx = 0;
			vy = 0;
			state = BOSS_STATE_ATTACK;
		}
	}
	if (state == BOSS_STATE_ATTACK)
	{
		if (timerAttack < BOSS_ATTACK_TIME)
		{
			timerAttack += dt;
		}
		else
		{
			timerAttack = 0;
			isAttack = true;
		}
		if (isAttack == true)
		{
			if (Simon->GetPosition().x < x)
			{
				vx = -BOSS_ATTACK_SPEED_X;
				vy = BOSS_ATTACK_SPEED_Y;
			}
			else
			{
				vx = BOSS_ATTACK_SPEED_X;
				vy = BOSS_ATTACK_SPEED_Y;
			}
			isAttack = false;
			isWait = true;
		}

		if (abs(y - Simon->GetPosition().y) <= 5)
		{
			vy = 0;
			if (abs(Simon->GetPosition().x - x) >= 5)
			{
				vy = BOSS_FLY_UP_SPEED;
			}
		}
	}

	if (state == BOSS_STATE_FLY)
	{
		if (x < FirstX)
		{
			vx = BOSS_FLY_SPEED_X;
		}
		else
		{
			vx = -BOSS_FLY_SPEED_X;
		}
	}
}

void CBoss::CollisionOccurred(vector<LPGAMEOBJECT>* coObjects)
{

}

void CBoss::CollisionWhenDead(vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BOSS_STATE_BLOOD)
	{
		Collision(coObjects);
	}
	else if (state != BOSS_STATE_BLOOD )
	{
		x += dx;
		y += dy;
	}
}
void CBoss::CheckCollisionSimon()
{
	if (CheckCollision(Simon))
	{
		if (state == BOSS_STATE_BLOOD )
		{
			SetActive(false);
		}
		else
		{
			if (Simon->GetUntouchable() == 0)
			{
				if (Simon->GetOnStair() == false)
				{
					Simon->StartIsDamaged();
				}
				Simon->StartIsUnTouchable(SIMON_UNTOUCHABLE_TIME);
			}
		}

	}
}

void CBoss::CheckCollisionWeapon()
{
	if (CheckCollision(MS))
	{
		if (MS->state == MS_STATE_ATTACK)
		{
			HP = HP - 1;
		}
		if (MS->state == MS_STATE_ATTACK_2)
		{
			HP = HP - 2;
		}
		if (MS->state == MS_STATE_ATTACK_3)
		{
			HP = HP - 3;
		}
	}
	for (int i = 0; i < simonaxe.size(); i++)
	{
		if (CheckCollision(simonaxe.at(i)) && isHurtbyweapon)
		{
			HP = HP - 4;
			isHurtbyweapon = false;
		}
	}
	for (int i = 0; i < simondagger.size(); i++)
	{
		if (CheckCollision(simondagger.at(i)))
		{
			HP = HP - 2;
			isHurtbyweapon = false;
		}
	}
	if (HP <= 0)
	{
		HP = 16;
		StartDieTime();
		state = BOSS_STATE_DIE;
	}
}

void CBoss::DeleateWaeponWhenUnactive()
{
	for (int i = 0; i < simonaxe.size(); i++)
	{
		if (simonaxe.at(i)->GetActive() == false)
		{
			simonaxe.erase(simonaxe.begin() + i);
		}
	}
	for (int i = 0; i < simondagger.size(); i++)
	{
		if (simondagger.at(i)->GetActive() == false)
		{
			simondagger.erase(simondagger.begin() + i);
		}
	}
}

void CBoss::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOSS_STATE_DIE:
	case BOSS_STATE_BLOOD:
		vx = 0;
	}
}

void CBoss::Render(Camera* camera)
{
	if (active == false)
		return;

	if (state == BOSS_STATE_SLEEP)
	{
		ani = BOSS_ANI_SLEEP;
	}
	else if (state == BOSS_STATE_BLOOD)
	{
		ani = BOSS_ANI_SHINING_BLOOD;
	}
	else if (state == BOSS_STATE_ATTACK || state == BOSS_STATE_FLY || BOSS_STATE_AWAKEN)
	{
		ani = BOSS_ANI_FLY;
	}
	if (die != 0)
	{
		ani = BOSS_ANI_DIE;
	}
	animations[ani]->Render(camera->transform(x, y), 255);
	RenderBoundingBox(camera);
}


void CBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BOSS_WIDTH;
	bottom = y + BOSS_HEIGHT;
	if (state == BOSS_STATE_BLOOD)
	{
		right = x + BOSS_BLOOD_WIDTH;
		bottom = y + BOSS_BLOOD_HEIGHT;
	}
}

