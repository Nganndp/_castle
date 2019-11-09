#include "Brick.h"

void CBrick::Render()
{
	if (active != true)
		return;
	if (type == BRICK_TYPE_NORMAL)
	{
		animations[0]->Render(x, y, 255);
	}
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	b = y + BRICK_BBOX_HEIGHT;
    r = x + (BRICK_BBOX_WIDTH *multwidth);
}
