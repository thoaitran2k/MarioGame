#include "BrickQuestion.h"
#include "MushRoom.h"
#include "Mario.h"



CMario* coin;

void CBrickQuestion::Render()
{
	

	CAnimations* animations = CAnimations::GetInstance();

	int aniID;
	aniID = ID_ANI_BRICK_Q;
		
	animations->Get(aniID)->Render(x, y);

	//RenderBoundingBox();
}

void CBrickQuestion::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_Q_BBOX_WIDTH / 2;
	t = y - BRICK_Q_BBOX_HEIGHT / 2;
	r = l + BRICK_Q_BBOX_WIDTH;
	b = t + BRICK_Q_BBOX_HEIGHT;
}

void CBrickQuestion::OnNoCollision(DWORD dt)
{
	//x += vx * dt;
	//y += vy * dt;
	x = 0;
	y = 0;

};

void CBrickQuestion::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CBrickQuestion*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = 0;
	}
}
void CBrickQuestion::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTION_BRICK_STATE_UP:
		vy = -QUESTION_BRICK_SPEED_UP;
		break;

	}
}
