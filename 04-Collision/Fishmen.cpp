#include "Fishmen.h"



CFishmen::CFishmen(float _firstX, CSimon *Simon)
{
	vy = -0.2f;
	firstX = _firstX;

	mSimon = Simon;

	this->AddAnimation(813);
	this->AddAnimation(814);
	this->AddAnimation(815);
	this->AddAnimation(835); //freezed
}

CFishmen::~CFishmen()
{
}

void CFishmen::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDeleted)
		return;

	CGameObject::Update(dt, coObjects);

	if (isFalling)
		vy += 0.001f*dt;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		if (!isFreezed && !isStop)
		{
			x += dx; //dx=vx*dt
			y += dy;
		}
		isOnGround = false;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		if (!isFreezed && !isStop)
			x += dx;



		if (!isFreezed && !isStop)
		{
			if (ny == 1)  //nếu đụng trên đầu thì ko block		
				y += dy;
		}
		if (ny == -1)
		{
			y += min_ty * dy + ny * 0.2f;
			isOnGround = true;
		}

	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];


	if (isOnGround)
	{
		if (isAttack == false)  //ko bắn đạn thì đi
			SetState(STATE_WALKING);


		if (vx < 0 && x < firstX - 10)
		{
			isAttack = true;
			nx = -1;
			x = firstX - 10; vx = -vx;
			isCreateFireBall = true;

		}
		else if (vx > 0 && x > firstX + 50)
		{
			isAttack = true;
			nx = 1;
			x = firstX + 50; vx = -vx;
			isCreateFireBall = true;

		}


		if (isAttack)
		{
			SetState(STATE_ATTACK);

			if (timerAttack < 300)
			{
				timerAttack += dt;
			}
			else
			{
				isAttack = false;
				timerAttack = 0;
				if (nx == -1) //bắn xong thì cho quay đầu đi tiếp
				{
					nx = 1;
					x = firstX;
				}
				else if (nx == 1)
				{
					nx = -1;
					x = firstX + 35;
				}
				SetState(STATE_WALKING);
			}
		}
	}


}

void CFishmen::Render(Camera * camera)
{
	CEnemy::Render(camera);

	if (this->y > 520) //nếu rơi xuống nước lại thì xóa nó
	{
		isDeleted = true;
		isOutOfCamera = true;
	}

	if (this->y - camera->GetPosition().y <= 76)  //khi fishmen nhảy qua khỏi mặt đất
	{
		isFalling = true;
		if (isOnGround)
			this->SetState(STATE_WALKING);
	}



	int ani = 0;

	if (isFreezed || isStop)
	{
		ani = 3;
	}
	else
	{
		if (state == STATE_WALKING)
		{
			ani = ANI_WALKING;
		}
		else if (state == STATE_ATTACK)
		{
			ani = ANI_ATTACK;
		}
	}

	if (nx == 1)
		animations[ani]->Render(camera->transform(x, y), 255, 1);
	else
		animations[ani]->Render(camera->transform(x, y));

	RenderBoundingBox(camera);
}

RECT CFishmen::GetBound()
{
	return CGameObject::GetBound();
}

void CFishmen::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (nx == 1)
	{
		left = x - 15;
		top = y;
		right = x;
		bottom = y + 32;
	}
	else
	{
		left = x;
		top = y;
		right = x + 15;
		bottom = y + 32;
	}
}

void CFishmen::SetState(int state)
{
	CGameObject::SetState(state);

	if (state == STATE_WALKING)
	{
		if (nx == 1)
			vx = 0.03f;
		else
			vx = -0.03f;
	}
	else if (state == STATE_ATTACK)
	{
		vx = 0;
	}
}
