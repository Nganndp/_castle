#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <algorithm>
#include "debug.h"
#include "Game.h"
#include "MathHelper.h"
#include "Camera.h"
#include "Textures.h"
#include "Sprites.h"
#include "define.h"



using namespace std;

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:

	float x;
	float y;
	float tempx;
	float tempy;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	float FirstX;
	float FirstY;

	int level = 1;
	int nx;
	int ny;
	int bboxcolor;
	int die = 0;
	int action = 0;
	DWORD dietime_start;
	DWORD action_start;

	int state;
	bool active = true;
	bool isTouchable;
	bool isOnGround;
	bool isStop;
	bool isFire;

	DWORD dt;
	CTextures* texture;
	CSprite* sprite;
	CAnimation* animation;

	vector<LPANIMATION> animations;

public:
	int type;
	virtual void SetTouchable(boolean a)
	{
		isTouchable = a;
	}
	virtual void SetActive(boolean a)
	{
		active = a;
	}
	int GetLevel()
	{
		return level;
	}
	virtual boolean GetActive()
	{
		return active;
	}
	void StartDieTime() { die = 1; dietime_start = GetTickCount(); }
	void StartAction() { action = 1; action_start = GetTickCount(); }
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	D3DXVECTOR2 GetPosition() { return D3DXVECTOR2(x, y); }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	void Setbboxcolor() {
		if (bboxcolor == 80)bboxcolor = 0;
		else bboxcolor = 80;
	}
	int GetState() { return this->state; }

	void RenderBoundingBox(Camera* camera);

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);

	void AddAnimation(int aniId);

	CGameObject();
	bool CheckOverlap(LPGAMEOBJECT coO);
	bool CheckCollision(CGameObject* object);
	int GetDirect() { return nx; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render(Camera* camera) = 0;
	virtual void SetState(int state) { this->state = state; }
	virtual void SetLevel(int level) { this->level = level; }
	virtual void CollisionOccurred(vector<LPGAMEOBJECT>* coObjects);
	virtual void Collision(vector<LPGAMEOBJECT>* coObjects);
	virtual RECT GetBound()
	{
		RECT rect;
		float l, t, r, b;
		GetBoundingBox(l, t, r, b);
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		return rect;
	}


	~CGameObject();
};

