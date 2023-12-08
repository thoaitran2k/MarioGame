#include "Green_Koopa.h"
#include "Platform.h"

CGreen_Koopa::CGreen_Koopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GREEN_NOT_WING_GRAVITY;
	die_start = -1;
	SetState(KOOPA_GREEN_NOT_WING_STATE_WALKING);
}

void CGreen_Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	
		left = x - KOOPA_GREEN_NOT_WING_BBOX_WIDTH / 2;
		top = y - KOOPA_GREEN_NOT_WING_BBOX_HEIGHT / 2;
		right = left + KOOPA_GREEN_NOT_WING_BBOX_WIDTH;
		bottom = top + KOOPA_GREEN_NOT_WING_BBOX_HEIGHT;
	
}

void CGreen_Koopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGreen_Koopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGreen_Koopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGreen_Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_GREEN_NOT_WING_STATE_ISTURTLESHELL) && (GetTickCount64() - die_start > KOOPA_GREEN_NOT_WING_DIE_TIMEOUT))
	{
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGreen_Koopa::Render()
{
	int aniId;
	if (vx>0) 
	{
		 aniId = ID_ANI_KOOPA_GREEN_NOT_WING_WALKING_RIGHT;
	} 
	else if (vx < 0) {
		aniId = ID_ANI_KOOPA_GREEN_NOT_WING_WALKING_LEFT;
	}
	else
		aniId = ID_ANI_KOOPA_GREEN_NOT_WING_TURTLESHELL;


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGreen_Koopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_GREEN_NOT_WING_STATE_ISTURTLESHELL:
		vx = 0;

		
		break;
	case KOOPA_GREEN_NOT_WING_STATE_WALKING:
		vx = -KOOPA_GREEN_NOT_WING_WALKING_SPEED;
		break;
	}
}