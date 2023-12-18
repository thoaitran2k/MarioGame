#include "TailWhipping.h"

#include "debug.h"

#include "Mario.h"
#include"Red_Koopa.h"

#include"CheckKoopaFall.h"

#include"glassBrick.h"
#include"FragGlass.h"

#include "Game.h"
#include "PlayScene.h"
#include "ButtonP.h"

CTailWhipping::CTailWhipping(float x, float y):CGameObject(x,y){
	//this->vx = vx;
	SetState(WHIP_STATE_DELETE);
	attack = false;
	
	
}

void CTailWhipping::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
	if (attackBrick)
	{
		l = x - 7 / 2;
		t = y - BBOX_HEIGHT / 2;
		r = l + 7;
		b = t + BBOX_HEIGHT;

	}
	 else
	{
		 l = x - BBOX_WIDTH / 2;
		 t = y - BBOX_HEIGHT / 2;
		 r = l + BBOX_WIDTH;
		 b = t + BBOX_HEIGHT;
	}
	
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
	//y += vy * dt;
};

void CTailWhipping::OnCollisionWith(LPCOLLISIONEVENT e) {

	//if (dynamic_cast<CMario*>(e->obj)) return;
	//if (e->obj->IsBlocking()) return;
	if (dynamic_cast<CRed_Koopa*>(e->obj)) return;
	if (dynamic_cast<CCheckFall*>(e->obj)) return;
	

	//CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (e->ny != 0)
	{
		//vy = vy;
	}
	else if (e->nx != 0)
	{
		//if (mario->GetState() != MARIO_STATE_ATTACK) vx = 0;
		//else 
		vx = vx;
	}


	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CglassBrick*>(e->obj))
	{
		attackBrick = true;
		OnCollisionWithGlassBrick(e);
	}
		
		
	




}


void CTailWhipping::OnCollisionWithGlassBrick(LPCOLLISIONEVENT e)
{
	CglassBrick* break_brick = dynamic_cast<CglassBrick*>(e->obj);
	//CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	//CFragGlass* frag = new CFragGlass(x+50, y - 80, 0, 0);
	//scene->AddObject(frag);
	//attackBrick = true;

	if (e->nx != 0)
	{
		//attack = true;
		if (break_brick->GetModel() == GLASS_BRICK_MODEL_NORMAL && break_brick->GetState() != GLASS_BRICK_STATE_CHANGE_TO_COIN)
		{

			break_brick->SetState(GLASS_BRICK_STATE_BREAK);

			if (break_brick->GetState() == GLASS_BRICK_STATE_BREAK)
			{
				attackBrick = true;


			}
		}
		else if (break_brick->GetModel() == GLASS_BRICK_MODEL_CONTAIN_BUTTON && break_brick->GetState() != GLASS_BRICK_STATE_CHANGE_TO_COIN)
		{
			CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
			if (!break_brick->GetUnBox() && !break_brick->GetEmpty() && break_brick->GetState() != GLASS_BRICK_STATE_ISTOUCHED)
			{
				break_brick->SetCollision(true);
				break_brick->SetState(GLASS_BRICK_STATE_ISTOUCHED);
				CButtonP* P = new CButtonP(break_brick->GetX(), break_brick->GetY() - 16);
				scene->AddObject(P);
			}
		}
		
		else if (break_brick->GetState() == GLASS_BRICK_STATE_CHANGE_TO_COIN) 
		{
			return;
		}


	}

	
		
}

void CTailWhipping::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {

	attack = true;
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	
	if (goomba->GetState() != GOOMBA_STATE_DIE)
		goomba->SetState(GOOMBA_STATE_DIE_UPSIDE);
	

}

void CTailWhipping::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	attackBrick = false;
	//attackBrick = false;
	//attack = false;

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
