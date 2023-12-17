#include "TailWhipping.h"

#include "debug.h"

#include "Mario.h"

CTailWhipping::CTailWhipping(float x, float y):CGameObject(x,y){
	//this->vx = vx;
	SetState(WHIP_STATE_DELETE);
	attack = false;
}

void CTailWhipping::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BBOX_WIDTH/2;
	t = y - BBOX_HEIGHT / 2;
	r = l + BBOX_WIDTH;
	b = t + BBOX_HEIGHT;
}

void CTailWhipping::Render() {

	if (attack) {
		int aniId;

		aniId = ID_ANI_TAIL_WHIPPING;



		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	}
	else RenderBoundingBox();
	
}

void CTailWhipping::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CTailWhipping::OnCollisionWith(LPCOLLISIONEVENT e) {

	if (e->ny != 0)
	{
		vy = vy;
	}
	else if (e->nx != 0)
	{
		vx = vx;
	}


	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);




}


void CTailWhipping::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {

	attack = true;
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	
	if (goomba->GetState() != GOOMBA_STATE_DIE)
		goomba->SetState(GOOMBA_STATE_DIE_UPSIDE);
	

}

void CTailWhipping::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetX() < x)
		SetState(WHIP_STATE_RIGHT_MARIO);
	else SetState(WHIP_STATE_LEFT_MARIO);

	if (attack) mario->SetVx(0);


	if (GetTickCount64() - timming > 150)
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
		vx = -SPEED_WHIP_LEFT;
		break;
		


	case WHIP_STATE_RIGHT_MARIO:
		vx = SPEED_WHIP;
		break;


	}
}
