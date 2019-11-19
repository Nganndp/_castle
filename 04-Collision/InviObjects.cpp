#include "InviObjects.h"
void InviObjects::Render(Camera* camera)
{
	if (active != true)
		return;
	RenderBoundingBox(camera);
}

void InviObjects::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (active != true || isTouchable != true)
		return;
	l = x;
	t = y;
	b = y + INVI_HEIGHT;
	r = x + INVI_WIDTH;
	/*if (type == STAIR_TYPE_UP_LEFT)
	{
		r = x + (INVI_WIDTH/2);
	}*/
}

