#include "Camera.h"


Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update(DWORD dt, int scene)
{
	if (scene == 1)
	{
		if (cam_x <= 0)
		{
			cam_x = 0;
		}
		else
			if (cam_x >= 770 - 320)
			{
				cam_x = 770 - 320;
			}
	}
	else if (scene == 2)
	{
		if (cam_x <= 0)
		{
			cam_x = 0;
		}
		else
			if (cam_x >= 2816 - 320)
			{
				cam_x = 2816 - 320;
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
