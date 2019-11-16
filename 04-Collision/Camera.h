#pragma once
#include <d3dx9.h>
#include "define.h"

class Camera
{

public:
	float cam_x;
	float cam_y;
	int cammove = 0;
	bool CamMoving = false;
	float cameramovetime;
	DWORD cammove_start;
	Camera();
	~Camera();

	void Update(DWORD dt, int scene, int stage); 
	void SetCamera(float x, float y);
	void SetCamMoving(bool a) { CamMoving = a; }
	void StartCamMove(float a) { cammove = 1; cammove_start = GetTickCount(); cameramovetime = a; }
	int GetCamMove()
	{
		return cammove;
	}
	boolean GetCamMoving()
	{
		return CamMoving;
	}
	D3DXVECTOR2 GetPosition();
	D3DXVECTOR2 transform(float x_world, float y_world);

};

