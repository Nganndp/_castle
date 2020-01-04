#pragma once
#include "GameObject.h"
#include "LoadAnimations.h"
#include "Simon.h"
#include "Camera.h"
#include "MS.h"
#include "Axe.h"
#include "Dagger.h"
#include "HolyWater.h"
class CBoss :public CGameObject
{
	CSimon* Simon;
	CMS* MS;
	CAxe* Axe;
	CDagger* Dagger;
	Camera* camera;
	DWORD timerWait = 0;
	DWORD timerAttack = 0;
	vector<LPGAMEOBJECT> simondagger;
	vector<LPGAMEOBJECT> simonaxe;
	vector<LPGAMEOBJECT> simonholywater;
	int ani;
	int HP;
	bool isAttack;
	bool isWait;
	bool isHurtbyweapon;
public:
	CBoss(CSimon * simon, CMS *MS, Camera *camera): CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Bossani.txt", this);
		Simon = simon;
		this->camera = camera;
		this->MS = MS;
		HP = 16;
		type = BOSS;
	};
	~CBoss();
	void GetSimonAxe(CAxe* axe)
	{
		isHurtbyweapon = true;
		simonaxe.push_back(axe);
	}
	void GetSimonDagger(CDagger* dagger)
	{
		isHurtbyweapon = true;
		simondagger.push_back(dagger);
	}
	void GetSimonHolyWater(CHolyWater* holywater)
	{
		isHurtbyweapon = true;
		simonholywater.push_back(holywater);
	}
	void SetFirstPos(int x, int y)
	{
		this->FirstX = x;
		this->FirstY = y;
	}
	void DeleateWaeponWhenUnactive();
	void CollisionWhenDead(vector<LPGAMEOBJECT>* coObjects);
	void CheckCollisionWeapon();
	void CheckCollisionSimon();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render(Camera* camera);
	RECT GetBound()
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
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void CollisionOccurred(vector<LPGAMEOBJECT>* coObjects) override;
};

