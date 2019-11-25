#include "Ghoul.h"


CGhoul::~CGhoul()
{
}

void CGhoul::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (active == false)
		return;
	if (isDie == true)
	{
		StartDieTime();
		isDie = false;
	}
	CGameObject::Update(dt, coObjects);
	
	vy += TORCH_GRAVITY*dt;


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
			x += dx; //dx=vx*dt
			y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		y += min_ty * dy + ny * 0.2f;

			// block 
			if (nx != 1)
				x += min_tx * dx + nx * 0.2f;;

			if (nx == 1)  //đụng trái	
				x += dx;

		if (ny != 0) vy = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (GetTickCount() - dietime_start > 200)
	{
		dietime_start = 0;
		die = 0;
		
	}
	if (state != GHOUL_STATE_WALKING && die == 0)
	{
		state = GHOUL_STATE_SHEART;
    }
	if (state == GHOUL_STATE_WALKING)
	{
		if (isStop)
			return;
		if (nx > 0)
			vx = 0.052f;
		else
			vx = -0.052f;
	}
}

void CGhoul::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case GHOUL_STATE_DIE:
	case GHOUL_STATE_SHEART:
	case GHOUL_STATE_IDLE:
		vx = 0;
		break;
	}
}

void CGhoul::Render(Camera * camera)
{
	//CGameObject::Render(camera);
	if (active != true)
		return;
	int ani = 0;
	 if (state == GHOUL_STATE_WALKING)
	 {
		if (nx > 0)
		{
			ani = GHOUL_ANI_WALKING_RIGHT;
		}
		else ani = GHOUL_ANI_WALKING_LEFT;
	 }
	 else if (state == GHOUL_STATE_SHEART)
	 {
		 ani = GHOUL_ANI_SHEART;
	 }
	 if (die != 0)
	 {
		 ani = GHOUL_ANI_DIE;
	 }
	 animations[ani]->Render(camera->transform(x, y), 255);
	RenderBoundingBox(camera);
}

void CGhoul::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
		left = x+1;
		top = y;
		right = x + 16;
		bottom = y + 32;
		if (state == GHOUL_STATE_SHEART)
		{
			right = x + 9;
			bottom = y + 9;
		}
}
