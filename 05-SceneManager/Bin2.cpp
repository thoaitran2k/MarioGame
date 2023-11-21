#include "Bin2.h"


void CBin2::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BIN2)->Render(x, y);
	//RenderBoundingBox();
}

void CBin2::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BIN2_BBOX_WIDTH / 2;
	t = y - BIN2_BBOX_HEIGHT / 2;
	r = l + BIN2_BBOX_WIDTH;
	b = t + BIN2_BBOX_HEIGHT;
}