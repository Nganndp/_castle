#include "CGroundBrick.h"
void CGroundBrick::Render()
{
	if (active != true)
		return;
	RenderBoundingBox();
}

void CGroundBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + (BRICK_BBOX_WIDTH *95);
	b = y + BRICK_BBOX_HEIGHT;
}
