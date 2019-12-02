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
	if (type == SC_TYPE_CHANGE_SCENE || type == SC_TYPE_AUTO_HELPER)
	{
		r = x + (INVI_WIDTH-8);
	}
}

