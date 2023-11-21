#include "BrickQuestion.h"
#include "MushRoom.h"
#include "Mario.h"



CBrickQuestion::CBrickQuestion(float x, float y, int model) :CGameObject(x, y)
{
	this->model = model;
	this->ay = 0;
	this->minY = y - BRICK_Q_BBOX_HEIGHT + ADJUST_UP_DOWN;
	this->startY = y;
	this->startX = x;
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
	//x = 0; Chi xet brick question di chuyen theo phuong y
	y += vy * dt;

};


/*
void CBrickQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (x != startX) {
		x = startX;
	}
	if (!isEmpty) {
		if (y != startY) y = startY;
		if (x != startX) x = startX;
	}
	if (isUnbox) {
		vy = 0;
		ay = 0;
		vx = 0;
		y = startY;
		x = startX;
	}
	else {
		vy += ay * dt;
		if (y <= minY)
		{
			vy = BRICK_Q_SPEED_DOWN;
		}
		if (y > startY + BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN)
		{
			y = startY;
			vy = 0;
			isEmpty = true;
			isUnbox = true;
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	/*
	if (x != startX) { x = startX; }
	else {
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
		*/
	



/*void CBrickQuestion::OnCollisionWith(LPCOLLISIONEVENT e)
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
*/

void CBrickQuestion::Render()
{

	int aniId;
	if (model == QUESTION_BRICK_COIN || QUESTION_BRICK_MUSHROOM) {
		aniId = ID_ANI_BRICK_Q;
	}
	if (state == BRICK_Q_STATE_EMPTY)
	{
		aniId = ID_ANI_BRICK_EMPTY;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();

	//RenderBoundingBox();
}

void CBrickQuestion::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_Q_STATE_EMPTY:
		vy = 0;
		isEmpty = true;
		isUnbox = true;
		break;
	}
}
