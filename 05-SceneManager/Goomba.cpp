#include "Goomba.h"
#include "Mario.h"
#include "Game.h"
#include "PlayScene.h"
#include "TailWhipping.h"



CGoomba::CGoomba(float x, float y, int model):CGameObject(x, y)
{
	//range = y - 20;
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	die_upside_start = -1;
	this->model = model;
	upside = false;
	Active = false;

	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::Goomba_Active() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (abs(mario->GetX() - x) < 170)
		Active = true;
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (state == GOOMBA_STATE_THROWN_BY_KOOPA) return;

	else if (state == GOOMBA_STATE_DIE_UPSIDE) return;

	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	Goomba_Active();
	if(Active)
	{
		x += vx * dt;
		y += vy * dt;
	}
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (dynamic_cast<CTailWhipping*>(e->obj)) return;
	//if (dynamic_cast<CGameEffects*>(e->obj)) return;
	
	if (!e->obj->IsBlocking()) return; 

	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	ay = GOOMBA_GRAVITY;

	if (Active) {
	vy += ay * dt;
	vx += ax * dt;

	/*if (upside) { 
		vx = 0;
		vy = 0.35f;
	}*/
	

		if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
		{
			isDeleted = true;
			//return;
		}

		/*else if ((state == GOOMBA_STATE_THROWN_BY_KOOPA) && GetTickCount64() - die_start > 300)
		{
			isDeleted = true;
			return;
		}*/

		else if (state == GOOMBA_STATE_DIE_UPSIDE && GetTickCount64() - die_upside_start > 1200)
		{

			isDeleted = true;
			return;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;

	if (state == GOOMBA_STATE_DIE && model == GOOMBA_BASIC) 
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else if (state == GOOMBA_STATE_DIE && model == GOOMBA_RED)
	{
		aniId = ID_ANI_GOOMBA_RED_DIE;
	}
	else if (model == GOOMBA_RED) {
		aniId = ID_ANI_GOOMBA_RED;
	}
	else if (state == GOOMBA_STATE_THROWN_BY_KOOPA)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else if (state == GOOMBA_STATE_DIE_UPSIDE)
	{
		if (vy<0) aniId = ID_ANI_GOOMBA_DIE_UPSIDE;
		else aniId = ID_ANI_GOOMBA_UPSIDE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;

		//case GOOMBA_STATE_THROWN_BY_KOOPA:
		//	die_start = GetTickCount64();
		//	//y -= 5;
		//	//vx = -0.004f;
		//	//vy = -0.0015f;
		//	//ay = 0.01f;
		//	break;

		case GOOMBA_STATE_WALKING:
			vx = -GOOMBA_WALKING_SPEED;
			break;

		/*case GOOMBA_RED:
			model = GOOMBA_RED;
			vx = -GOOMBA_WALKING_SPEED;
			break;*/

		case GOOMBA_STATE_DIE_UPSIDE:
			vx = 0.07f;
			vy = -0.148f;
			ay = 0.0009f;
			break;
	}
}
