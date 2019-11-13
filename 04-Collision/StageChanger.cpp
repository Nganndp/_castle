#include "StageChanger.h"
void StageChanger::Render(Camera* camera)
{
	if (active != true)
		return;
	RenderBoundingBox(camera);
}

void StageChanger::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (active != true)
		return;
	l = x;
	t = y;
	b = y + SC_HEIGHT;
	r = x + SC_WIDTH;
}

