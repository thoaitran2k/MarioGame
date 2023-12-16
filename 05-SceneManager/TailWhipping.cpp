#include "TailWhipping.h"

#include "debug.h"

CTailWhipping::CTailWhipping(float x, float y):CGameObject(x,y){
	this->vx = vx;
	SetState(WHIP_STATE_DELETE);
}

void CTailWhipping::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BBOX_WIDTH / 2;
	t = y - BBOX_HEIGHT / 2;
	r = l + BBOX_WIDTH;
	b = t + BBOX_HEIGHT;
}

void CTailWhipping::Render() {
	RenderBoundingBox();
}

void CTailWhipping::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CTailWhipping::OnCollisionWith(LPCOLLISIONEVENT e) {

}

void CTailWhipping::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - timming > 250)
	{
		
		timming = -1;
		isDeleted = true;
		return;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CTailWhipping::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WHIP_STATE_DELETE:
		timming = GetTickCount64();
		break;


	case WHIP_STATE_LEFT_MARIO:
		vx = -SPEED_WHIP;
		break;


	case WHIP_STATE_RIGHT_MARIO:
		vx = SPEED_WHIP;
		break;


	}
}
