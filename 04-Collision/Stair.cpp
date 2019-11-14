#include "Stair.h"
void Stair::Render(Camera* camera)
{
	if (active != true)
		return;
	RenderBoundingBox(camera);
}

void Stair::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (active != true)
		return;
		l = x;
		t = y;
		b = y + STAIR_HEIGHT;
		r = x + STAIR_WIDTH;
}
