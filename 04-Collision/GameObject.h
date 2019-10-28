#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <algorithm>
#include "debug.h"
#include "Game.h"
#include "MathHelper.h"
#include "Textures.h"
#include "Sprites.h"
#include "define.h"



using namespace std;

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:

	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;
	int level = 1;
	int nx;	 
	int bboxcolor;

	int state;
	boolean active = true;
	boolean isTouchable;
	DWORD dt; 
    CTextures* texture;
	CSprite* sprite;
	CAnimation* animation;

	vector<LPANIMATION> animations;

public: 
	void SetTouchable(boolean a)
	{
		isTouchable = a;
	}
	void SetPlusLevel()
	{
		this->level++;
	}
	int GetLevel()
	{
		return level;
	}
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void Setbboxcolor() {
		if (bboxcolor == 80)bboxcolor = 0;
		else bboxcolor = 80;
	}
	virtual void SetActive(boolean a) { active = a; };
	int GetState() { return this->state; }

	void RenderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);

	void AddAnimation(int aniId);

	CGameObject();
	bool CheckOverlap(LPGAMEOBJECT coO);
	bool CheckCollision(CGameObject* object);
	int GetDirect() { return nx; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	virtual void SetLevel(int level) { this->level = level; }
	RECT CGameObject::GetBound()
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

