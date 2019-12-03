#include "Camera.h"


Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update(DWORD dt, float start, float end)
{
	if (GetTickCount() - cammove_start > cameramovetime)
	{
		cammove_start = 0;
		cammove = 0;
    }
	if (cammove != 0)
	{
		cam_x += 1;
	}
	if (cam_x >= startpoint && endpoint == end)
	{
		CamMoving = false;
	}
    if (CamMoving == false)
	{
		if (cam_x <= startpoint)
		{
			cam_x = startpoint;
		}
			else
		if (cam_x >= endpoint - SCREEN_WIDTH)
		{
			cam_x = endpoint - SCREEN_WIDTH;
		}
	}
}


void Camera::SetCamera(float x, float y)
{
	cam_x = x;
	cam_y = y;
}

D3DXVECTOR2 Camera::GetPosition()
{
	return D3DXVECTOR2(cam_x, cam_y);
}

D3DXVECTOR2 Camera::transform(float x_world, float y_world)
{
	return D3DXVECTOR2(x_world - cam_x, y_world - cam_y);
}
