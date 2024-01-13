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
#include "Green_Plant.h"

#include "GameEffects.h"

#include "Green_Koopa.h"

#include "Red_Koopa.h"

#include "Para_Goomba.h"
#include "BrickQuestion.h"
#include"MushRoom.h"
#include "leaf.h"
#include "Coin.h"

CTailWhipping::CTailWhipping(float x, float y):CGameObject(x,y){
	//this->vx = vx;
	SetState(WHIP_STATE_DELETE);
	attack = false;
	
	
}

void CTailWhipping::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	/*if (mario->GetVx() != 0)
	{
		l = x - 1;
		t = y - BBOX_HEIGHT / 2;
		r = l + 1;
		b = t + BBOX_HEIGHT;

	}*/
	 //else
		
	//{
		 l = x - BBOX_WIDTH / 2;
		 t = y - BBOX_HEIGHT / 2;
		 r = l + BBOX_WIDTH;
		 b = t + BBOX_HEIGHT;
	//}
	
}

void CTailWhipping::Render() {

	int aniId;
	if (attack) {
		

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
	//if (dynamic_cast<CRed_Koopa*>(e->obj)) return;
	if (dynamic_cast<CCheckFall*>(e->obj)) return;
	

	//CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	//if (e->ny != 0)
	//{
	//	//vy = vy;
	//}
	if (e->nx != 0)
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

	else if (dynamic_cast<CGreen_Plant*>(e->obj))
		OnCollisionWithGreenPlant(e);

	else if (dynamic_cast<CGreen_Koopa*>(e->obj))
		OnCollisionWithGreen_Koopa(e);

	else if (dynamic_cast<CRed_Koopa*>(e->obj))
		OnCollisionWithRed_Koopa(e);

	else if (dynamic_cast<CPara_Goomba*>(e->obj))
		OnCollisionWithPara_Goomba(e);

	else if (dynamic_cast<CBrickQuestion*>(e->obj))
		OnCollisionWithBrickQuestion(e);
}

void CTailWhipping::OnCollisionWithBrickQuestion(LPCOLLISIONEVENT e) {
	CBrickQuestion* questionBrick = dynamic_cast<CBrickQuestion*>(e->obj);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	BOOLEAN isUnBox, isEmpty;
	isUnBox = questionBrick->GetIsUnbox();
	isEmpty = questionBrick->GetIsEmpty();

	float xTemp, yTemp, minY;
	xTemp = questionBrick->GetX();
	yTemp = questionBrick->GetY();
	minY = questionBrick->GetMinY();

	if (isUnBox) return;

	if (questionBrick->GetModel() == QUESTION_BRICK_COIN)
	{

		mario->SetCoin(mario->GetCoin() + 1);
		CCoin* coin = new CCoin(xTemp, yTemp);
		coin->SetState(COIN_SUMMON_STATE);
		scene->AddObject(coin);
		questionBrick->SetState(BRICK_Q_STATE_EMPTY);
		//questionBrick->SetState(BRICK_Q_STATE_UP);
		questionBrick->SetIsEmpty(true);
		questionBrick->SetIsUnbox(true);
		coin++;
		mario->SetPoint(5);

	}

	else if (questionBrick->GetModel() == QUESTION_BRICK_NOT_COIN) {

		if (mario->GetLevel() == MARIO_LEVEL_SMALL)
		{
			CMushRoom* mushroom = new CMushRoom(xTemp, yTemp - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN), 1);
			scene->AddObject(mushroom);
			questionBrick->SetState(BRICK_Q_STATE_EMPTY);
			//questionBrick->SetState(BRICK_Q_STATE_UP);
			questionBrick->SetIsEmpty(true);
			questionBrick->SetIsUnbox(true);
		}
		else if (mario->GetLevel() == MARIO_LEVEL_BIG) {
			CLeaf* leaf = new CLeaf(xTemp, yTemp - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN));
			scene->AddObject(leaf);
			leaf->SetState(LEAF_SUMMON_STATE);
			questionBrick->SetState(BRICK_Q_STATE_EMPTY);
			//questionBrick->SetState(BRICK_Q_STATE_UP);
			questionBrick->SetIsEmpty(true);
			questionBrick->SetIsUnbox(true);

		}
		else if (mario->GetLevel() == MARIO_LEVEL_RACOON)
		{
			CMushRoom* mushroomgreen = new CMushRoom(xTemp, yTemp - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN), MODE_GREEN);
			scene->AddObject(mushroomgreen);
			questionBrick->SetState(BRICK_Q_STATE_EMPTY);
			//questionBrick->SetState(BRICK_Q_STATE_UP);
			questionBrick->SetIsEmpty(true);
			questionBrick->SetIsUnbox(true);
		}
	}
}

void CTailWhipping::OnCollisionWithPara_Goomba(LPCOLLISIONEVENT e) {
	attack = true;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CPara_Goomba* pr_goomba = dynamic_cast<CPara_Goomba*>(e->obj);

	//pr_goomba->SetIsFly(false);
	//if (pr_goomba->GetState() == PARA_GOOMBA_STATE_FLY or pr_goomba->GetState() == PARA_GOOMBA_STATE_WALKING) {
	if (pr_goomba->GetState() == GOOMBA_RED_STATE_FALL)
	{
		pr_goomba->SetState(GOOMBA_RED_STATE_BE_WHIPED);
		//pr_goomba->SetVy(-0.035f);
		CGameEffects* plusscore100 = new CGameEffects(x, y - 4, 1);
		scene->AddObject(plusscore100);
		mario->SetPoint(1);
	}
	else {
		pr_goomba->SetState(PARA_STATE_BE_WHIPED);
		CGameEffects* plusscore100 = new CGameEffects(x, y - 4, 1);
		scene->AddObject(plusscore100);
		mario->SetPoint(1);
	}
		//mario->CreatEffectMario(1);
	//}
	
}

void CTailWhipping::OnCollisionWithRed_Koopa(LPCOLLISIONEVENT e) {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CRed_Koopa* rkpa = dynamic_cast<CRed_Koopa*>(e->obj);
	if (e->nx != 0)
	{
		if (rkpa->GetIsTurtleShell())
		{
			if (!rkpa->GETwasKicked()) {


				rkpa->SetState(KOOPA_RED_STATE_TURTLESHELL_UPSIDE_TAIL_ATTACK);
				//gkpa->SetCombackTimes(-1);
				rkpa->SetVy(-0.47f);
				//gkpa->SetX(mario->GetX()+15);

			}
			else return;
		}
		else {

			rkpa->SetState(KOOPA_RED_STATE_TURTLESHELL_UPSIDE_TAIL_ATTACK);
			rkpa->SetVy(-0.47f);
			//gkpa->SetX(mario->GetX() + 15);
			//gkpa->SetX(gkpa->GetX() + 5);
			//gkpa->SetVx(0.1f * gkpa->LeftOrRightMarrio());

		}
	}

}


void CTailWhipping::OnCollisionWithGreen_Koopa(LPCOLLISIONEVENT e) {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGreen_Koopa* gkpa = dynamic_cast<CGreen_Koopa*>(e->obj);
	if (e->nx != 0)
	{
		if (gkpa->GetIsTurtleShell())
		{
			if (!gkpa->GETwasKicked()) {
				
				
				gkpa->SetState(KOOPA_GREEN_STATE_BE_WHIPED);
				//gkpa->SetCombackTimes(-1);
				gkpa->SetVy(-0.22f);
				//gkpa->SetX(mario->GetX()+15);
				
			}
		}
		else {
			
			gkpa->SetState(KOOPA_GREEN_STATE_BE_WHIPED);
			gkpa->SetVy(-0.22f);
			//gkpa->SetX(mario->GetX() + 15);
			//gkpa->SetX(gkpa->GetX() + 5);
			//gkpa->SetVx(0.1f * gkpa->LeftOrRightMarrio());

		}
	}

}

void CTailWhipping::OnCollisionWithGreenPlant(LPCOLLISIONEVENT e) {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	CGreen_Plant* g_plant = dynamic_cast<CGreen_Plant*>(e->obj);

	if (g_plant->GetType() == 2) {
		attack = true;
		e->obj->Delete();
		CGameEffects* plusscore100 = new CGameEffects(x, y - 4, 1);
		scene->AddObject(plusscore100);
		mario->SetPoint(1);
	}
	else return;
	
}

void CTailWhipping::OnCollisionWithGlassBrick(LPCOLLISIONEVENT e)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CglassBrick* break_brick = dynamic_cast<CglassBrick*>(e->obj);
	//CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	//CFragGlass* frag = new CFragGlass(x+50, y - 80, 0, 0);
	//scene->AddObject(frag);
	//attackBrick = true;

	attackBrick = true;

	if (e->nx != 0)
	{
		//attack = true;
		if (break_brick->GetModel() == GLASS_BRICK_MODEL_NORMAL && break_brick->GetState() != GLASS_BRICK_STATE_CHANGE_TO_COIN)
		{

			break_brick->SetState(GLASS_BRICK_STATE_BREAK);

			
			mario->SetPoint(20);
			break_brick->CreateAniFragGlass1();
			break_brick->CreateAniFragGlass2();

			
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
		else if (break_brick->GetModel() == GLASS_BRICK_ITEM && break_brick->GetState() != GLASS_BRICK_STATE_CHANGE_TO_COIN)
		{
			CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
			if (!break_brick->GetUnBox() && !break_brick->GetEmpty() && break_brick->GetState() != GLASS_BRICK_STATE_ISTOUCHED)
			{
				if (mario->GetLevel() == MARIO_LEVEL_SMALL)
				{
					CMushRoom* mushroom = new CMushRoom(break_brick->GetX(), break_brick->GetY() - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN), 1);
					scene->AddObject(mushroom);
					break_brick->SetState(GLASS_BRICK_STATE_ISTOUCHED);
					//questionBrick->SetState(BRICK_Q_STATE_UP);
					//questionBrick->SetIsEmpty(true);
					//questionBrick->SetIsUnbox(true);
				}
				else if (mario->GetLevel() == MARIO_LEVEL_BIG) {
					CLeaf* leaf = new CLeaf(break_brick->GetX(), break_brick->GetY() - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN));
					scene->AddObject(leaf);
					leaf->SetState(LEAF_SUMMON_STATE);
					break_brick->SetState(GLASS_BRICK_STATE_ISTOUCHED);
					//questionBrick->SetState(BRICK_Q_STATE_UP);
					//questionBrick->SetIsEmpty(true);
					//questionBrick->SetIsUnbox(true);

				}
				else if (mario->GetLevel() == MARIO_LEVEL_RACOON)
				{
					CMushRoom* mushroomgreen = new CMushRoom(break_brick->GetX(), break_brick->GetY() - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN), MODE_GREEN);
					scene->AddObject(mushroomgreen);
					break_brick->SetState(GLASS_BRICK_STATE_ISTOUCHED);
					//break_brick->SetState(BRICK_Q_STATE_EMPTY);
					//questionBrick->SetState(BRICK_Q_STATE_UP);
					//break_brick->SetIsEmpty(true);
					//questionBrick->SetIsUnbox(true);
				}

				/*break_brick->SetCollision(true);
				break_brick->SetState(GLASS_BRICK_STATE_ISTOUCHED);
				CButtonP* P = new CButtonP(break_brick->GetX(), break_brick->GetY() - 16);
				scene->AddObject(P);*/
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
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	//CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CGoomba* goomba_1 = dynamic_cast<CGoomba*>(e->obj);

	//if (e->nx != 0) {
		//
		//if (!goomba_1->GetWhiped())
			
		//goomba_1->SetWhip(true);
	if (goomba_1->GetState() != GOOMBA_STATE_DIE){
		goomba_1->SetState(GOOMBA_STATE_DIE_UPSIDE);
		
		mario->CreatEffectMario(1);
		mario->SetPoint(1);
	}

}

void CTailWhipping::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	attackBrick = false;
	//attackBrick = false;
	//attack = false;

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetNx()>0)
		SetState(WHIP_STATE_RIGHT_MARIO);
	else SetState(WHIP_STATE_LEFT_MARIO);

	if (attack) mario->SetVx(0);


	if (GetTickCount64() - timming > 200)
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
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	
	CGameObject::SetState(state);
	switch (state)
	{
	case WHIP_STATE_DELETE:
		timming = GetTickCount64();
		break;


	case WHIP_STATE_LEFT_MARIO:
		if (mario->GetVx() < 0)
			vx = -0.11f;
		 else vx = -SPEED_WHIP_LEFT;
		break;
		


	case WHIP_STATE_RIGHT_MARIO:
		if (mario->GetVx() > 0)
			vx = 0.11f;
		else vx = SPEED_WHIP;
		break;


	/*case WHIP_STATE_BREAK_BRICK:
		timming = GetTickCount64();
		break;*/


	}
}
