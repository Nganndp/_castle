#pragma once
#include <d3dx9.h>
#include "define.h"

class Camera
{

public:
	float cam_x;
	float cam_y;
	int cammove = 0;
	int startpoint;
	int endpoint;
	bool CamMoving = false;
	float cameramovetime;
	DWORD cammove_start;
	Camera();
	~Camera();
	int GetCamMove()
	{
		return cammove;
	}
	int GetStartPoint()
	{
		return startpoint;
	}
	int GetEndPoint()
	{
		return endpoint;
	}
	boolean GetCamMoving()
	{
		return CamMoving;
	}
	D3DXVECTOR2 GetPosition();
	D3DXVECTOR2 transform(float x_world, float y_world);
	void SetStartPoint(int a)
	{
		startpoint = a;
	}
	void SetEndPoint(int b)
	{
		endpoint = b;
	}
	void SetCamerax(float x)
	{
		this->cam_x = x;
	}
	void SetCamera(float x, float y);
	void SetCamMoving(bool a) { CamMoving = a; }
	void StartCamMove(float a) { cammove = 1; cammove_start = GetTickCount(); cameramovetime = a; }
	void Update(DWORD dt, float start, float end);
};

