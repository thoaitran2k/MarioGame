#include "Brick_Question.h"




CBrickQuestion::CBrickQuestion(float x, float y) :CGameObject(x, y)
{
	this->ay = 0;
	this->minY = y - BRICK_Q_BBOX_HEIGHT + ADJUST_UP_DOWN;
	this->startY = y;
	this->startX = x;
}

void CBrickQuestion::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CBrickQuestion*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = -vy;
	}
}

void CBrickQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vy += ay * dt;
	if (y <= minY)
	{
		vy = BRICK_Q_SPEED_DOWN;
	}
	if (y > startY + BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN)
	{
		y = startY;
		vy = 0;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrickQuestion::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK_Q)->Render(x, y);
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
	y += vy * dt;
};

void CBrickQuestion::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_Q_STATE_UP:
		vy = -BRICK_Q_SPEED_UP;
		break;

	}
}