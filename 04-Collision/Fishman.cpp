#include "Fishman.h"


CFishman::~CFishman()
{
}

void CFishman::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (active == false)
		return;
	CGameObject::Update(dt, coObjects);
	
	if (state == ENEMY_STATE_JUMPING)
		vy = -FISHMAN_JUMP_SPEED * dt;
	if (isOnGround && state != ENEMY_STATE_SHEART && state != ENEMY_STATE_DIE)
	{
		if (!isAttack)
		{
			SetState(ENEMY_STATE_MOVING);


			if (vx < 0 && x < movepoint - FISHMAN_MOVE_LEFT_RANGE)
			{
				isFire = true;
				isAttack = true;
				nx = -1;
				x = movepoint - FISHMAN_MOVE_LEFT_RANGE; vx = -vx;
			}
			else if (vx > 0 && x > movepoint + FISHMAN_MOVE_RIGHT_RANGE)
			{
				isFire = true;
				isAttack = true;
				nx = 1;
				x = movepoint + FISHMAN_MOVE_RIGHT_RANGE; vx = -vx;
			}
		}

		else if (isAttack)
		{
			SetState(ENEMY_STATE_ATTACK);

			if (timerAttack < FISHMAN_ATTACK_TIME)
			{
				timerAttack += dt;
			}
			else
			{
				isAttack = false;
				timerAttack = 0;
				if (nx == -1) 
				{
					nx = 1;
					x = movepoint;
				}
				else if (nx == 1)
				{
					nx = -1;
					x = movepoint + 35;
				}
				SetState(ENEMY_STATE_MOVING);
			}
		}
	}
	if (y - camera->GetPosition().y <= 80)  
	{
		SetState(ENEMY_STATE_FALLING);
	}
	if (state == ENEMY_STATE_FALLING)
	{
		if (isOnGround)
			this->SetState(ENEMY_STATE_MOVING);
	}
	if (state == ENEMY_STATE_SHEART)
	{
		if (isOnGround == false)
		{
			if (vx < 0 && x < FirstX - ENEMY_SHEART_RANGE)
			{
				x = FirstX - ENEMY_SHEART_RANGE; vx = -vx;
			}

			if (vx > 0 && x > FirstX + ENEMY_SHEART_RANGE)
			{
				x = FirstX + ENEMY_SHEART_RANGE; vx = -vx;
			}
			vx = ENEMY_SHEART_SPEED;
		}
		if (isOnGround)
		{
			vx = 0;
		}
	}
	if (GetTickCount() - dietime_start > ENEMY_DIE_TIME)
	{
		dietime_start = 0;
		die = 0;
	}
	if (state == ENEMY_STATE_DIE && die == 0)
	{
		SetState(ENEMY_STATE_SHEART);
	}
	if (isFire)
	{
		firebullet = new CFireBullet();
		if (nx > 0)
		{
			firebullet->nx = 1;
			firebullet->SetPosition(x + 18, y + 5);
		}
		else
		{
			firebullet->nx = -1;
			firebullet->SetPosition(x - 9, y + 5);
		}
		firebullets.push_back(firebullet);
		isFire = false;
	}
	for (int i = 0; i < firebullets.size(); i++)
	{
		firebullets[i]->Update(dt, coObjects);
	}
	Collision(coObjects);
}

void CFishman::CollisionOccurred(vector<LPGAMEOBJECT>* coObjects)
{

}

void CFishman::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case ENEMY_STATE_FALLING:
		vy = FISHMAN_JUMP_SPEED * dt;
		break;
	case ENEMY_STATE_MOVING:
		if (nx == 1)
			vx = FISHMAN_SPEED;
		else
			vx = -FISHMAN_SPEED;
		break;
	case ENEMY_STATE_ATTACK:
	case ENEMY_STATE_DIE:
	    vx = 0;
		break;
	case ENEMY_STATE_SHEART:
		vx = 0;
		vy = GRAVITY * dt;
		break;
	}
	
}

void CFishman::Render(Camera* camera)
{
	if (active != true)
		return;
	int ani = 0;
	if (state == ENEMY_STATE_MOVING)
	{
		if (nx > 0)
		{
			ani = FISHMAN_ANI_WALKING_RIGHT;
		}
		else ani = FISHMAN_ANI_WALKING_LEFT;
	}
	else if (state == ENEMY_STATE_SHEART)
	{
		ani = FISHMAN_ANI_SHEART;
	}
	else if (state == ENEMY_STATE_JUMPING || state == ENEMY_STATE_FALLING)
	{
		if (nx > 0)
			ani = FISHMAN_ANI_IDLE_RIGHT;
		else ani = FISHMAN_ANI_IDLE_LEFT;
	}
	else if (state == ENEMY_STATE_ATTACK)
	{
		if (nx > 0) ani = FISHMAN_ANI_ATTACK_RIGHT;
		else ani = FISHMAN_ANI_ATTACK_LEFT;
	}
	if (die != 0)
	{
		ani = FISHMAN_ANI_DIE;
	}
	animations[ani]->Render(camera->transform(x, y), 255);
	RenderBoundingBox(camera);
	for (int i = 0; i < firebullets.size(); i++)
	{
		firebullets[i]->Render(camera);
	}
}

void CFishman::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FISHMAN_BOX_WIDTH;
	bottom = y + FISHMAN_BOX_HEIGHT;
	if (state == ENEMY_STATE_SHEART)
	{
		right = x + SHEART_WIDTH;
		bottom = y + SHEART_HEIGHT;
	}
}

