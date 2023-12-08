#include "Brick.h"

void CBrick::Render()
{

	int aniId;

	if (model == 1) { aniId = ID_ANI_BRICK; }

	if(model == 2) { aniId = ID_ANI_BRICK_2; }

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}