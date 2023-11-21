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
void CBin1::OnNoCollision(DWORD dt)
{
	//x += vx * dt;
	//y += vy * dt;
	x = 0;
	y = 0;

};
void CBin1::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CBin1*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = 0;
	}
}

