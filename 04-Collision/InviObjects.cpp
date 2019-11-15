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
	b = y + SC_HEIGHT;
	r = x + SC_WIDTH;
	if (type == STAIR_TYPE_UP_RIGHT || type == STAIR_TYPE_DOWN_RIGHT || type == STAIR_TYPE_UP_LEFT || type == STAIR_TYPE_DOWN_LEFT)
	{
		b = y + STAIR_HEIGHT;
		r = x + STAIR_WIDTH;
	}
}

