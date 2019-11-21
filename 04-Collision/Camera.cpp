#include "Camera.h"


Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update(DWORD dt, int scene, int stage)
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
	if (cam_x >= 1535 && stage == 2)
	{
		CamMoving = false;
	}
	else if (CamMoving == false)
	{
		if (scene == 1)
		{
			if (cam_x <= 0)
			{
				cam_x = 0;
			}
			else
				if (cam_x >= 770 - SCREEN_WIDTH)
				{
					cam_x = 770 - SCREEN_WIDTH;
				}
		}
		else if (scene == 2)
		{
			if (stage == 1)
			{
				if (cam_x <= 0)
				{
					cam_x = 0;
				}
				else
					if (cam_x >= 1550 - SCREEN_WIDTH)
					{
						cam_x = 1550 - SCREEN_WIDTH;
					}
			}
			if (stage == 2)
			{
				if (cam_x <= 1535)
				{
					cam_x = 1535;
				}
				else
					if (cam_x >= 2051 - SCREEN_WIDTH)
					{
						cam_x = 2051 - SCREEN_WIDTH;
					}
			}
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
