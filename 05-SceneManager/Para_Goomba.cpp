#include "Para_Goomba.h"
#include "Platform.h"
#include "Mario.h"
#include "PlayScene.h"
#include "GameObject.h"

CPara_Goomba::CPara_Goomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = PARA_GOOMBA_GRAVITY;
	isFly = true;
	

	SetState(GOOMBA_RED_STATE_WALKING);
}

void CPara_Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	
		left = x - PARA_GOOMBA_BBOX_WIDTH / 2;
		top = y - PARA_GOOMBA_BBOX_HEIGHT / 2;
		right = left + PARA_GOOMBA_BBOX_WIDTH;
		bottom = top + PARA_GOOMBA_BBOX_HEIGHT/2;
	
}

void CPara_Goomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPara_Goomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CPara_Goomba*>(e->obj)) return;
	if (!e->obj->IsBlocking() && !e->obj->IsPlatform()) return;
	if (e->ny < 0)
	{
		isOnPlatForm = true;
		vy = 0;
	}
	/*if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPara_Goomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}*/
	if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatForm(e);
}

void CPara_Goomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx -= ax * dt;
	//if (!isFly)
	//{
	//	if (GetTickCount64() - walking_time > TIME_WALKING)
	//		{
	//			SetState(PARA_GOOMBA_STATE_FLY);
	//		}
	//}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPara_Goomba::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	if (e->ny < 0) {
		isOnPlatForm = true;
		SetY(platform->GetY() - GOOMBA_BBOX_HEIGHT + 1);
	}
}

void CPara_Goomba::Render()
{
	int aniId;
	if (isOnPlatForm)
	{
		aniId = ID_ANI_GOOMBA_RED_FLY_WALKING;
	} else 
			aniId = ID_ANI_GOOMBA_RED_FLY_JUMP;

	
		
		

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPara_Goomba::SetState(int state)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGameObject::SetState(state);
	switch (state)
	{
	case PARA_GOOMBA_STATE_FLY:
		vy = 0.04f;
		vx = -PARA_GOOMBA_WALKING_SPEED;
		isFly = true;
		isOnPlatForm = false;
		break;

	case GOOMBA_RED_STATE_WALKING:
		isFly = false;
		isOnPlatForm = true;
		vx = -PARA_GOOMBA_WALKING_SPEED;
		vy = 0;
		walking_time = GetTickCount64();

		break;		
	}
}
