#pragma once
#include "LoadAnimations.h"
#include "GameObject.h"
class CFireBullet :public CGameObject
	{
		bool isStop = false;
	public:
		CFireBullet() :CGameObject()
		{
			LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Firebulletani.txt", this);
			type = FIREBULLET;
			active = true;
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

