#include "Red_Koopa.h"
#include "Platform.h"

CRed_Koopa::CRed_Koopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_RED_GRAVITY;
	die_start = -1;
	SetState(KOOPA_RED_STATE_WALKING);
}

void CRed_Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{


	left = x - KOOPA_RED_BBOX_WIDTH / 2;
	top = y - KOOPA_RED_BBOX_HEIGHT / 2;
	right = left + KOOPA_RED_BBOX_WIDTH;
	bottom = top + KOOPA_RED_BBOX_HEIGHT;

}

void CRed_Koopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CRed_Koopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CRed_Koopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CRed_Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_RED_STATE_ISDEFEND) && (GetTickCount64() - die_start > KOOPA_RED_DIE_TIMEOUT))
	{
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CRed_Koopa::Render()
{
	int aniId;
	if (vx > 0)
	{
		aniId = ID_ANI_KOOPA_RED_WALKING_RIGHT;
	}
	else if (vx < 0) {
		aniId = ID_ANI_KOOPA_RED_WALKING_LEFT;
	}
	else
		aniId = ID_ANI_KOOPA_RED_DEFEND;


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CRed_Koopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_RED_STATE_ISDEFEND:
		vx = 0;


		break;
	case KOOPA_RED_STATE_WALKING:
		vx = -KOOPA_RED_WALKING_SPEED;
		break;
	}
}
