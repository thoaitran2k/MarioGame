#include "Bin1.h"

void CBin1::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BIN1)->Render(x, y);
	//RenderBoundingBox();
}

void CBin1::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BIN1_BBOX_WIDTH / 2;
	t = y - BIN1_BBOX_HEIGHT / 2;
	r = l + BIN1_BBOX_WIDTH;
	b = t + BIN1_BBOX_HEIGHT;
}
