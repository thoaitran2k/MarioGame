#include "BrickEmpty.h"

void CBrickEmpty::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK_EMPTY)->Render(x, y);
	//RenderBoundingBox();
}

void CBrickEmpty::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_EMPTY_BBOX_WIDTH / 2;
	t = y - BRICK_EMPTY_BBOX_HEIGHT / 2;
	r = l + BRICK_EMPTY_BBOX_WIDTH;
	b = t + BRICK_EMPTY_BBOX_HEIGHT;
}