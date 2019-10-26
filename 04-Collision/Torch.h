#pragma once
#include "GameObject.h"
#include "Brick.h"

#define TORCH_BBOX_WIDTH 16
#define TORCH_BBOX_HEIGHT 15
#define TORCH_GRAVITY 0.0002f
#define TORCH_STATE_NORMAL 0
#define TORCH_STATE_LHEART 1
#define TORCH_STATE_SHEART 2
#define TORCH_STATE_MSUP 3
#define TORCH_STATE_DAGGER 4
#define TORCH_STATE_AXE 5

#define TORCH_ANI_NORMAL 0
#define TORCH_ANI_LHEART 1
#define TORCH_ANI_SHEART 2
#define TORCH_ANI_MSUP 3
#define TORCH_ANI_DAGHER 4
#define TORCH_ANI_AXE 5

class CTorch : public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	boolean isTouchable = true;
	boolean active = true;
	int state = 0;
	int ani = 0;

public: 	
	boolean GetActive()
	{
		return active;
	}
	int GetState()
	{
		return state;
	}
	void SetActive(boolean a)
	{
		active = a;
	}
	void SetTouchable(boolean a)
	{
		isTouchable = a;
	}
	void SetState(int state)
	{
		this->state = state;
	}
};