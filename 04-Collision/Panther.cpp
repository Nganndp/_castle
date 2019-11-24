#include "Panther.h"



CPanther::CPanther(CSimon *Simon, float _firstX)
{
	mSimon = Simon;
	//nx = -1;
	firstX = _firstX;

	this->AddAnimation(105); //idle
	this->AddAnimation(106); //run
	this->AddAnimation(823); //jump

	//freezed
	this->AddAnimation(112); //run

}

CPanther::~CPanther()
{
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDeleted)
		return;

	if (state == STATE_RUNNING || state == STATE_JUMPING || state == STATE_FALLING)
		CGameObject::Update(dt, coObjects);

	//fall down
	vy += 0.0035f*dt;


	if ((this->x - mSimon->x) < 80 && state != STATE_RUNNING && state != STATE_FALLING) //Simon đến gần
	{
		this->SetState(STATE_JUMPING);
		isOnGround = false;
	}
	if (abs(this->firstX - this->x) >= 30 && state != STATE_RUNNING)
	{
		this->SetState(STATE_FALLING);
	}
	if (state == STATE_FALLING && isOnGround == true)
	{
		this->SetState(STATE_RUNNING);
	}


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
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 		
		y += min_ty * dy + ny * 0.2f;

		if (nx == -1 || nx == 1) 
		{ 
			x += dx; 			
		}
	
		if (ny == 1)
		{
			y += dy;
		}
		if (ny == -1)
		{	
			isOnGround = true;
			vy = 0;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];



	if (vx < 0 && firstX - x >= 155)
	{
		nx = 1;
		x = x + 25;
		vx = -vx;
	}

}

void CPanther::Render(Camera * camera)
{
	if (state == STATE_RUNNING)
	{
		if (x - camera->GetPosition().x <= 0 || x - camera->GetPosition().x >= 320)
		{
			isDeleted = true;
			isOutOfCamera = true;
			return;
		}
	}



	int ani = 0; //panther idle

	if (state == STATE_RUNNING)
	{
		if (isFreezed || isStop)
			ani = 3;
		else
			ani = 1;
	}
	else if (state == STATE_JUMPING || state == STATE_FALLING)
		ani = 2;


	if(nx==-1)
		animations[ani]->Render(camera->transform(x, y));
	else 
		animations[ani]->Render(camera->transform(x, y),255,1);

	RenderBoundingBox(camera);
}

RECT CPanther::GetBound()
{
	return CGameObject::GetBound();
}

void CPanther::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (nx == -1)
	{
		left = x;
		top = y;
		right = x + 25;
		bottom = y + 16;
	}
	else 
	{
		left = x-25;
		top = y+1;
		right = x;
		bottom = y + 16;
	}
}

void CPanther::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case STATE_RUNNING:
		if (nx < 0)
			vx = -0.23f;
		else 
			vx = 0.23f;
		break;

	case STATE_JUMPING:
		if (nx < 0)
		{
			vy = -0.1f;
			vx = -0.12f;
		}
		else
		{
			vy = -0.1f;
			vx = 0.12f;
		}
		break;

	case STATE_FALLING:
		vy = 0.12f;
		break;
	}
}
