#include "Koopa_Green_Not_Wing.h"

CKoopa_Green_Not_Wing::CKoopa_Green_Not_Wing(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GREEN_NOT_WING_GRAVITY;
	die_start = -1;
	SetState(KOOPA_GREEN_NOT_WING_STATE_WALKING);
}

void CKoopa_Green_Not_Wing::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	
		left = x - KOOPA_GREEN_NOT_WING_BBOX_WIDTH / 2;
		top = y - KOOPA_GREEN_NOT_WING_BBOX_HEIGHT / 2;
		right = left + KOOPA_GREEN_NOT_WING_BBOX_WIDTH;
		bottom = top + KOOPA_GREEN_NOT_WING_BBOX_HEIGHT;
	
}

void CKoopa_Green_Not_Wing::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa_Green_Not_Wing::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopa_Green_Not_Wing*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopa_Green_Not_Wing::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == KOOPA_GREEN_NOT_WING_STATE_ISDEFEND) && (GetTickCount64() - die_start > KOOPA_GREEN_NOT_WING_DIE_TIMEOUT))
	{
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa_Green_Not_Wing::Render()
{
	int aniId;
	if (vx>0) 
	{
		 aniId = ID_ANI_KOOPA_GREEN_NOT_WING_WALKING_RIGHT;
	} 
	else aniId = ID_ANI_KOOPA_GREEN_NOT_WING_WALKING_LEFT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopa_Green_Not_Wing::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_GREEN_NOT_WING_STATE_WALKING:
		vx = -KOOPA_GREEN_NOT_WING_WALKING_SPEED;
		break;
	}
}