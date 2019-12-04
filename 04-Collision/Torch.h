#pragma once
#include "GameObject.h"
#include "Brick.h"
#include "define.h"
#include "LoadAnimations.h"

class CTorch : public CGameObject
{
	int ani = 0;
	int normalwidth;
	int normalheight;
	int candlewidth;
	int candleheight;
	int sheartswidth;
	int sheartheight;
	int lheartwidth;
	int lheartheight;
	int daggerwidth;
	int daggerheight;
	int moneywidth;
	int moneyheight;
	int otherswidth;
	int othersheight;
	int end;
public:

	CTorch() :CGameObject()
	{
		LoadAnimations::LoadAnimationFromFile("ReadFile\\Ani\\Torchani.txt", this);
		LoadElementFromFile(SOURCE_TORCH_ELEMENT_TXT);
		type = TORCH;
		isOnGround = false;
	};
	~CTorch();
	int GetState()
	{
		return state;
	}
	void SetState(int state)
	{
		this->state = state;
	}
	void SetType(int a)
	{
		type = a;
	}
	void LoadElementFromFile(string source);
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
	void CollisionOccurred(vector<LPGAMEOBJECT>* coObjects) override;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render(Camera* camera);
};