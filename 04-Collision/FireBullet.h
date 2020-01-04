#pragma once
#include "LoadAnimations.h"
#include "GameObject.h"
#include "Simon.h"
class CFireBullet :public CGameObject
	{
		bool isStop = false;
		CGameObject* Simon;
		CGameObject* MS;
	public:
		CFireBullet(CGameObject*Simon, CGameObject*MS) :CGameObject()
		{
			LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Firebulletani.txt", this);
			type = FIREBULLET;
			active = true;
			this->Simon = Simon;
			this->MS = MS;
		};
		~CFireBullet();
		bool GetStop()
		{
			return isStop;
		}
		void SetStop(bool a) { isStop = a; }
		void SetState(int state);
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
		void GetBoundingBox(float& left, float& top, float& right, float& bottom);


};

