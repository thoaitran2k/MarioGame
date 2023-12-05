#include "Para_Goomba.h"
#include "Platform.h"
#include "Mario.h"
#include "PlayScene.h"
#include "GameObject.h"





CPara_Goomba::CPara_Goomba(float x, float y) :CGameObject(x, y)
{

		
		startX = x;
		startY = y;
		this->ax = 0;
		this->ay = PARA_GOOMBA_GRAVITY;
		die_start_red_goomba = -1;
		isFly = true;
		vx = -PARA_GOOMBA_WALKING_SPEED;
		SetState(PARA_GOOMBA_STATE_WALKING);
		DebugOut(L">>> PARA xuat hien >>> \n");
		isActive = false;
		

	
}

void CPara_Goomba::Para_Goomba_Appear() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (abs(mario->GetX() - x) < 150) {
		CGameObject* para_goomba = scene->CreateObjectAndReturn(OBJECT_TYPE_PARA_GOOMBA, startX, startY, 0, 0);
		AddPara_Goomba(para_goomba);
		DebugOut(L">>> koopa duoc rs >>> \n");
		this->ax = 0;
		this->ay = PARA_GOOMBA_GRAVITY;
		isFly = true;
		vx = -PARA_GOOMBA_WALKING_SPEED;
		SetState(PARA_GOOMBA_STATE_WALKING);
	}
}


void CPara_Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isFly)
	{
		left = x - PARA_GOOMBA_BBOX_WIDTH / 2;
		top = y - PARA_GOOMBA_BBOX_HEIGHT / 2;
		right = left + PARA_GOOMBA_BBOX_WIDTH;
		bottom = top + PARA_GOOMBA_BBOX_HEIGHT;
	}

	else if(state == GOOMBA_RED_STATE_DIE)
	{
		left = x - PARA_GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_RED_BBOX_HEIGHT_DIE / 2;
		right = left + PARA_GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_RED_BBOX_HEIGHT_DIE;
	}
	else {
		left = x - PARA_GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_RED_BBOX_HEIGHT / 2;
		right = left + PARA_GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_RED_BBOX_HEIGHT;
	}
}

void CPara_Goomba::OnNoCollision(DWORD dt)
{
	Para_Goomba_Active();
	if (isActive)
	{
		x += vx * dt;
		y += vy * dt;
	}
};

void CPara_Goomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking() && !e->obj->IsPlatform()) return;
	if (dynamic_cast<CPara_Goomba*>(e->obj)) return;
	
	if (e->ny < 0)
	{
		isOnPlatForm = true;
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
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
	Para_Goomba_Active();

	if (isActive)
	{
	vy += ay * dt;
	vx += ax * dt;


	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	
	/*if (abs(mario->GetX() - x) < 100)
		Para_Goomba_Appear();*/
	
		if (state == PARA_GOOMBA_STATE_WALKING && GetTickCount64() - count_start > PARA_GOOMBA_WALKING_TIME)
		{
			SetState(PARA_GOOMBA_STATE_FLY);
		}
		else if (state == PARA_GOOMBA_STATE_FLY && isOnPlatForm)
		{
			SetState(PARA_GOOMBA_STATE_WALKING);
		}

		if ((state == GOOMBA_RED_STATE_DIE) && (GetTickCount64() - die_start_red_goomba > GOOMBA_RED_DIE_TIMEOUT))
		{
			isDeleted = true;
			return;
		}
	}
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
	if (!isFly)
	{
		aniId = ID_ANI_GOOMBA_RED;
		if (state == GOOMBA_RED_STATE_DIE) aniId = ID_ANI_GOOMBA_RED_DIE;
	}
	else if (isOnPlatForm)
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
		if(mario->GetX() > x)
			vx = PARA_GOOMBA_WALKING_SPEED;
		else vx = -PARA_GOOMBA_WALKING_SPEED;
		vy = -SPEED_PARA_GOOMBA_FLY;
		
		isOnPlatForm = false;
		break;
	case GOOMBA_RED_STATE_FALL:
		//vx = SPEED_GOOMBA_RED_WALKING;
		vy = PARA_GOOMBA_GRAVITY;
		isFly = false;
		break;
	case PARA_GOOMBA_STATE_WALKING:
		if (mario->GetX() > x)
			vx = PARA_GOOMBA_WALKING_SPEED;
		else vx = -PARA_GOOMBA_WALKING_SPEED;
		isOnPlatForm = true;
		vy = 0;
		count_start = GetTickCount64();
		break;		
	case GOOMBA_RED_STATE_DIE:
		y += (GOOMBA_RED_BBOX_HEIGHT - GOOMBA_RED_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		die_start_red_goomba = GetTickCount64();
		break;
	}
}
