#include "Brick.h"

void CBrick::Render(Camera * camera)
{
	if (active != true)
		return;
	RenderBoundingBox(camera);
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	
	l = x;
	t = y;
	b = y + BRICK_BBOX_HEIGHT;
    r = x + (BRICK_BBOX_WIDTH *multwidth);
}
