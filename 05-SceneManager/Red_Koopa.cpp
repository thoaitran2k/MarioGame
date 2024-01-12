#include "Red_Koopa.h"
#include "Platform.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
#include "Background.h"
#include "MushRoom.h"
#include "CheckKoopaFall.h"
#include "BrickQuestion.h"
#include "Goomba.h"
#include "Leaf.h"
#include "bullet_plant.h"
#include "Box.h"
#include "glassBrick.h"
#include "GameEffects.h"
#include"Para_Goomba.h"




CRed_Koopa::CRed_Koopa(float x, float y,int typeKoopa) :CGameObject(x, y)
{
	this->typeKoopa = typeKoopa;
	this->ax = 0;
	this->ay = KOOPA_RED_GRAVITY;
	count_start =-1;
	SetState(KOOPA_RED_STATE_WALKING);
	isTurtleShell = false;
	startX = x;
	startY = y;
	isOnPlatform = false;
	goomba_under_koopa = NULL;
	checkfall = NULL;
	isKicked = false;
	HaveOrNotCheckFall = true;
	isComback = false;
	wasKicked = false;
	isDead = false;
	wasHeld = false;
	TailAttack = false;
	time_rs = -1;
	timeWhiped = -1;
	
	newkoopa = NULL;
	
	//CreateKoopaOnGlassBrick();
	
	//KoopaOnGlassActive = false;
	/*if (type != 1) {
		Koopa_onGlassBrick_Active();
	}*/
	//koopa_brick = NULL;
	//isheld_time = -1;
	//collis = 1;
	
	
	
	
	//CreateNewKoopaOnGlassBrick();
	//CreateNewKoopa();
}



void CRed_Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == KOOPA_RED_STATE_WALKING || state == KOOPA_RED_STATE_WALKING_ON_GLASS)
	{
		left = x - KOOPA_RED_BBOX_WIDTH / 2;
		top = y - KOOPA_RED_BBOX_HEIGHT / 2;
		right = left + KOOPA_RED_BBOX_WIDTH;
		bottom = top + KOOPA_RED_BBOX_HEIGHT+4;
	}
	else if(/*state == KOOPA_RED_STATE_ISDEFEND || */state == KOOPA_RED_WALKING_STATE_TURN)
	{
		left = x - KOOPA_RED_BBOX_WIDTH / 2;
		top = y - KOOPA_RED_BBOX_HEIGHT / 2;
		right = left + KOOPA_RED_BBOX_WIDTH;
		bottom = top + KOOPA_RED_BBOX_HEIGHT + 4;
	}
	else if(state == KOOPA_RED_STATE_ISTURTLESHELL or state == KOOPA_RED_STATE_RESET_AFTER_KICKED or state == KOOPA_RED_STATE_TURTLESHELL_UPSIDE_TAIL_ATTACK)
	{
		left = x - KOOPA_RED_BBOX_WIDTH / 2;
		top = y - KOOPA_RED_BBOX_HEIGHT / 2;
		right = left + KOOPA_RED_BBOX_WIDTH;
		bottom = top + KOOPA_RED_BBOX_HEIGHT-1;
	}
	else
	{
		left = x - KOOPA_RED_BBOX_WIDTH / 2;
		top = y - KOOPA_RED_BBOX_HEIGHT / 2;
		right = left + KOOPA_RED_BBOX_WIDTH;
		bottom = top + KOOPA_RED_BBOX_HEIGHT - 1;
	}

}

void CRed_Koopa::CreateGoomba() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	
		CGameObject* goomba = scene->CreateObjectAndReturn(OBJECT_TYPE_GOOMBA_UNDER_KOOPA, startX-30, startY + 25, 0, 0);
		AddGoomba(goomba);
		DebugOut(L">>> TAO RA GOOMBA >>> \n");
		goomba_under_koopa->SetState(GOOMBA_STATE_WALKING);
	
	
}

//void CRed_Koopa::CreateNewKoopaOnGlassBrick() {
//	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
//	CGameObject* new_koopa_on_glBrick = scene->CreateObjectAndReturn(OBJECT_TYPE_NEW_RED_KOOPA_ON_GLASS_BRICK, 2002, 352, 0, 0);
//	Addnew_koopa_ontheglassbrick(new_koopa_on_glBrick);
//	//CreateCheckfallSmall();
//	SetState(KOOPA_RED_STATE_WALKING);
//}

//void CRed_Koopa::CreateKoopaOnGlassBrick() {
//	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
//	//CGameObject* new_koopa1 = scene->CreateObjectAndReturn(OBJECT_TYPE_RED_KOOPA_WALKING, startX+1559, startY, 0, 0);
//	CGameObject* new_koopa1 = scene->CreateObjectAndReturn(OBJECT_TYPE_RED_KOOPA_WALKING, startX + 45, startY, 0, 0);
//	Addnew_koopa(new_koopa1);
//	SetState(KOOPA_RED_STATE_WALKING);
//}

void CRed_Koopa::CreateNewKoopa2() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (isDead /*&& GetTickCount64() - time_rs > 4000*/) {

		CGameObject* new_koopa2 = scene->CreateObjectAndReturn(OBJECT_TYPE_NEW_RED_KOOPA, startX, startY, 0, 0);
		Addnew_koopa(new_koopa2);
		DebugOut(L">>> koopa duoc rs >>> \n");
		SetState(KOOPA_RED_STATE_WALKING);
		CreateCheckfallSmall();
	}

}

void CRed_Koopa::CreateNewKoopa() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (isDead /*&& GetTickCount64() - time_rs > 4000*/) {
		
		CGameObject* new_koopa = scene->CreateObjectAndReturn(OBJECT_TYPE_RED_KOOPA_WALKING, startX, startY, 0, 0);
			Addnew_koopa(new_koopa);
			DebugOut(L">>> koopa duoc rs >>> \n");
			SetState(KOOPA_RED_STATE_WALKING);

			if (typeKoopa == 2) CreateCheckfallSmall();
	}
	
}

void CRed_Koopa::CreateCheckfallSmall() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	

		if (vx < 0)
		{
			CGameObject* add_object_left1 = scene->CreateObjectAndReturn(OBJECT_TYPE_CHECKFALL_KOOPA_ON_GLASS_BRICK, GetX() - 1, y + 6, 0, 0);
			AddCheck(add_object_left1);
			DebugOut(L">>> check tao obj left >>> \n");
			checkfall->SetState(SMALL_STATE_LEFT_KOOPA);
			//checkfall->SETay(0.0009f);


		}
		else if (vx >= 0)
		{
			CGameObject* add_object_right1 = scene->CreateObjectAndReturn(OBJECT_TYPE_CHECKFALL_KOOPA_ON_GLASS_BRICK, GetX() + 1, y + 6, 0/* KOOPA_RED_WALKING_SPEED*/, 0);

			AddCheck(add_object_right1);
			DebugOut(L">>> check tao obj right >>> \n");
			checkfall->SetState(SMALL_STATE_RIGHT_KOOPA);
			//checkfall->SETay(0.0009f);

		}
	



}

void CRed_Koopa::CreateCheckfall() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

		if (vx<0)
		{
			CGameObject* add_object_left = scene->CreateObjectAndReturn(OBJECT_TYPE_CHECKFALL_KOOPA, GetX()- KOOPA_RED_BBOX_WIDTH, y+1, 0, 0);
				AddCheck(add_object_left);
				DebugOut(L">>> check tao obj left >>> \n");
				checkfall->SetState(STATE_LEFT_KOOPA);
				checkfall->SETay(0.00009f);
			
			
		}
		else 
		{
			CGameObject* add_object_right = scene->CreateObjectAndReturn(OBJECT_TYPE_CHECKFALL_KOOPA, GetX()+ KOOPA_RED_BBOX_WIDTH, y+1,0/* KOOPA_RED_WALKING_SPEED*/, 0);
			
			AddCheck(add_object_right);
			DebugOut(L">>> check tao obj right >>> \n");
			checkfall->SetState(STATE_RIGHT_KOOPA);
			checkfall->SETay(0.00009f);
			
		}

}

void CRed_Koopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};


void CRed_Koopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (typeKoopa == 2) {
		if (!e->obj->IsBlocking()) return;
	}

	if (dynamic_cast<CRed_Koopa*>(e->obj)) return;
	if (dynamic_cast<CbulletPlant*>(e->obj)) return;
	//if (state == KOOPA_RED_STATE_BE_HELD) return;
	
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		
		  vx = -vx;
		if (isOnPlatform) {
			ResetCheck();
		}
		
	}

	if (dynamic_cast<CBackground*>(e->obj))
		this->OnCollisionWithPlatForm(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CBrickQuestion*>(e->obj))
		OnCollisionWithBrick_Question(e);
	else if (dynamic_cast<CBox*>(e->obj))
		OnCollisionWithOntheBox(e);
	else if (dynamic_cast<CglassBrick*>(e->obj))
		OnCollisionWithGlassBrick(e);
	else if (dynamic_cast<CPara_Goomba*>(e->obj))
		OnCollisionWithParaGoomba(e);
}

void CRed_Koopa::OnCollisionWithParaGoomba(LPCOLLISIONEVENT e) {
	CPara_Goomba* para_goomba = dynamic_cast<CPara_Goomba*>(e->obj);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (x > para_goomba->GetX())
	{
		vx = -vx;
		x = x - PARA_GOOMBA_BBOX_HEIGHT / 2 - 2;
	}
	else {
		vx = -vx;
		x = x + PARA_GOOMBA_BBOX_HEIGHT / 2 + 2;
	}
	

	if (wasKicked) {
		if (para_goomba->GetActive()) {
			if (para_goomba->GetState() != GOOMBA_RED_STATE_DIE && para_goomba->GetState() != GOOMBA_RED_STATE_BE_WHIPED) {
				para_goomba->SetState(GOOMBA_RED_STATE_BE_WHIPED);
				CGameEffects* plusscore100 = new CGameEffects(x, y - 4, 1);
				scene->AddObject(plusscore100);
				mario->SetPoint(1);
				//mario->CreatEffectMario(1);
			}
		}
		else return;
	}
}

void CRed_Koopa::OnCollisionWithGlassBrick(LPCOLLISIONEVENT e) {
	CglassBrick* glBrick = dynamic_cast<CglassBrick*>(e->obj);

	if (e->ny < 0)
	{
		OntheGlassBrick = true;
		typeKoopa = 2;

	}
	else if (e->nx != 0)
	{
		if (isTurtleShell) {
			if (wasKicked) {
				if (glBrick->GetModel() == GLASS_BRICK_MODEL_NORMAL && glBrick->GetState() != GLASS_BRICK_STATE_CHANGE_TO_COIN)
				{
					e->obj->Delete();
					//glBrick->SetState(GLASS_BRICK_STATE_BREAK);
					glBrick->CreateAniFragGlass1();
					glBrick->CreateAniFragGlass2();
					//ay = 0.0004f;
					//vx = 0.19f;


				}
				else if (glBrick->GetState() == GLASS_BRICK_STATE_CHANGE_TO_COIN)
				{
					glBrick->SetNotCoin(0);
					return;
				}
			}

		}
	}
	

}

void CRed_Koopa::OnCollisionWithOntheBox(LPCOLLISIONEVENT e) {


	
	if (e->ny < 0) {
		isOntheBox = true;
		//CreateGoomba();
	}
		
	

}

void CRed_Koopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (x > goomba->GetX())
	{
		vx = -vx;
		x = x - GOOMBA_BBOX_HEIGHT/2 - 2;
	}
	else { 
		vx = -vx;
		x = x + GOOMBA_BBOX_HEIGHT/2 +2;
	}


	if (wasKicked) {
		if (goomba->GetState() == GOOMBA_STATE_DIE_UPSIDE) return;
			
		else
		{
			if (goomba->GetActive()) {
				if (goomba->GetState() != GOOMBA_STATE_DIE_UPSIDE)
				{

					goomba->SetState(GOOMBA_STATE_DIE_UPSIDE);
					CGameEffects* plusscore100 = new CGameEffects(x, y - 4, 1);
					scene->AddObject(plusscore100);

					//goomba->SetVy(-0.02f);
					//goomba->SetVx(-0.01f);
					//goomba->SetY(y + 2);
					//x += KOOPA_RED_BBOX_WIDTH / 2;
				}
			}
			else return;
		}
	}
	
}

void CRed_Koopa::OnCollisionWithBrick_Question(LPCOLLISIONEVENT e) {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (wasKicked) {
		CBrickQuestion* questionBrick = dynamic_cast<CBrickQuestion*>(e->obj);
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		BOOLEAN isUnBox, isEmpty;
		isUnBox = questionBrick->GetIsUnbox();
		isEmpty = questionBrick->GetIsEmpty();
		float xTemp, yTemp, minY;
		xTemp = questionBrick->GetX();
		yTemp = questionBrick->GetY();

		if (e->nx != 0 && !isUnBox && !isEmpty) {

			if (questionBrick->GetModel() == QUESTION_BRICK_NOT_COIN)
			{
				if (mario->GetLevel() == MARIO_LEVEL_SMALL) {
					CMushRoom* mushroom = new CMushRoom(xTemp, yTemp - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN), 1);
					scene->AddObject(mushroom);
					questionBrick->SetState(BRICK_Q_STATE_EMPTY);
					questionBrick->SetState(BRICK_Q_STATE_UP);
					questionBrick->SetIsEmpty(true);
					questionBrick->SetIsUnbox(true);

				}
				else if(mario->GetLevel() == MARIO_LEVEL_BIG)
				{
					CLeaf* leaf = new CLeaf(xTemp, yTemp);
					leaf->SetState(LEAF_SUMMON_STATE);
					scene->AddObject(leaf);
					questionBrick->SetState(BRICK_Q_STATE_EMPTY);
					questionBrick->SetIsEmpty(true);
					questionBrick->SetIsUnbox(true);
				}
				else if (mario->GetLevel() == MARIO_LEVEL_RACOON)
				{
					CMushRoom* mushroomgreen = new CMushRoom(xTemp, yTemp - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN), 2);
					scene->AddObject(mushroomgreen);
					questionBrick->SetState(BRICK_Q_STATE_EMPTY);
					questionBrick->SetState(BRICK_Q_STATE_UP);
					questionBrick->SetIsEmpty(true);
					questionBrick->SetIsUnbox(true);
				}
			}
		}
	}
}

void CRed_Koopa::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	CBackground* platform = dynamic_cast<CBackground*>(e->obj);
	if (e->ny < 0) {
		isOnPlatform = true;
		//typeKoopa = 1;
		//if (state == KOOPA_RED_STATE_WALKING)
			//vx = 0.015f;
		
	}

	

	

	if (isOnPlatform && state != KOOPA_RED_STATE_WALKING )
	{
		//isTurtleShell = true;
		
	}
}

void CRed_Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	//if (type == 2) {
	//	
	//	if (!KoopaOnGlassActive) {
	//		vx = 0;
	//		nx = -1;
	//	}
	//	else SetState(KOOPA_RED_STATE_WALKING_ON_GLASS);
	//}


	

	if (!isDead) {
		//if (isOntheBox)
		//{
			if (!isTurtleShell && HaveOrNotCheckFall) {
				//count_start = GetTickCount64();

				if (checkfall == NULL)
				{
					/*if (OntheGlassBrick) {
						CreateCheckfallSmall();
					}*/
					if (typeKoopa == 1) {
						CreateCheckfall();
					}
					
					else if (typeKoopa == 2) CreateCheckfallSmall();
					DebugOut(L">>> CHECK TAO OBJ >>> \n");
				}
				else 
					if (!checkfall->GetIsOnPlatform() && (checkfall->GetModel() == 1 || checkfall->GetModel() == 2) && (isOntheBox || OntheGlassBrick|| isOnPlatform))
				{
						SetState(KOOPA_RED_WALKING_STATE_TURN);
						//DebugOut(L">>> MOVING >>> \n");

				}
			}
			else //isTurtleshell and Not Checkfall
				if(!wasKicked && state != KOOPA_RED_STATE_BE_HELD)
				{
					if (state == KOOPA_RED_STATE_RESET_AFTER_KICKED) {
						SetState(KOOPA_RED_STATE_ISTURTLESHELL);
						y = y - 8;
					}
					else
					if (state == KOOPA_RED_STATE_TURTLESHELL_UPSIDE_TAIL_ATTACK)
					{
						vx = 0.06f * LeftOrRightMarrio();
						if (GetTickCount64() - timeWhiped > 450) {
							SetState(KOOPA_RED_STATE_ISTURTLESHELL);
							y = y - 8;
						}
					}
					else {
						if (!mario->GetIsHolding() && !wasHeld && !isTurn && GetTickCount64() - count_start > TURTLE_SHELL_TOTURN_KOOPA)
						{
							//count_start = GetTickCount64();
							SetState(KOOPA_RED_STATE_TO_RETURN);
							DebugOut(L">>> RETURN >>> \n");

						}
						if (!mario->GetIsHolding() && !wasHeld && isTurn && GetTickCount64() - comback_time > TIME_COMBACK_KOOPA)
						{


							//count_start = GetTickCount64();
							SetState(KOOPA_RED_STATE_WALKING);

							count_start = GetTickCount64();
							if (typeKoopa == 1)
								vx = KOOPA_RED_WALKING_SPEED;

							else if (typeKoopa == 2)
								vx = 0.011f;
							y = y - KOOPA_RED_BBOX_HEIGHT / 2;
							DebugOut(L">>> HOI SINH TU MAI RUA >>> \n");
						}
					}
				}

			if (state == KOOPA_RED_STATE_BE_HELD)
			{
				//isheld_time = GetTickCount64();
				vx = mario->GetVx();
				vy = mario->GetVy();
				this->x = mario->GetX() + mario->GetNx() * (MARIO_BIG_BBOX_WIDTH - 3);
				this->y = mario->GetY() - 3;
				
				if (!mario->GetIsHold())
				{
					SetState(KOOPA_RED_STATE_ISKICKED);
					flagHeldKick = false;
					//wasHeld = false;
				}
				else 
					if(GetTickCount64() - isheld_time > 6000)
				{
					//if (!mario->GetIsHolding())
					//{
						
						this->y = mario->GetY();
						//SetState(KOOPA_RED_STATE_TO_RETURN);
						if (mario->GetIsHolding()) 
						{

							SetState(KOOPA_RED_STATE_TO_RETURN);
							if(GetTickCount64() - comback_time > 500)
							{
								
									//count_start = GetTickCount64();
									SetState(KOOPA_RED_STATE_WALKING);

								DebugOut(L">>> RETURN >>> \n");

							}
						}
						else {
							SetState(KOOPA_RED_STATE_ISKICKED);
						}
						
					//}
				}
			}
			
		//}

		//if (isOnPlatform) {
		//	if (!isTurtleShell && HaveOrNotCheckFall) {
		//		//count_start = GetTickCount64();

		//		if (checkfall == NULL)
		//		{
		//			CreateCheckfall();
		//			DebugOut(L">>> CHECK TAO OBJ >>> \n");
		//			//ResetCheck();
		//			
		//		}
		//		else if (!checkfall->GetIsOnPlatform()) {
		//			vx = -vx;
		//			ResetCheck();
		//		}

		//		
		//	}
		//	else //isTurtleshell and Not Checkfall
		//		if (!wasKicked)
		//		{
		//			if (!wasHeld && !isTurn && GetTickCount64() - count_start > TURTLE_SHELL_TOTURN_KOOPA)
		//			{
		//				SetState(KOOPA_RED_STATE_TO_RETURN);
		//				DebugOut(L">>> RETURN >>> \n");

		//			}
		//			if (!wasHeld && isTurn && GetTickCount64() - comback_time > TIME_COMBACK_KOOPA)
		//			{

		//				SetState(KOOPA_RED_STATE_WALKING);
		//				vx = KOOPA_RED_WALKING_SPEED;
		//				y = y - KOOPA_RED_BBOX_HEIGHT / 2;
		//				DebugOut(L">>> HOI SINH TU MAI RUA >>> \n");
		//			}
		//		}
		//	if (state == KOOPA_RED_STATE_BE_HELD)
		//	{
		//		vx = mario->GetVx();
		//		vy = mario->GetVy();
		//		this->x = mario->GetX() + mario->GetNx() * (MARIO_BIG_BBOX_WIDTH - 3);
		//		this->y = mario->GetY() - 3;

		//		if (!mario->GetIsHold())
		//		{
		//			SetState(KOOPA_RED_STATE_ISKICKED);
		//		}

		//		//else
		//			 //if (GetTickCount64() - isheld_time > 3000)
		//			//SetState(KOOPA_RED_STATE_WALKING);
		//	}
		//}


		//////////////////////////////////////////////
		if (state == KOOPA_RED_STATE_ISKICKED)
		{
			if (DistanceTurtleShellisKickedWithMario() > DISTANCE_MIN_SHELL_EXIST && GetTickCount64() - time_delete > TURTLE_SHELL_TIMEOUT)
				isDeleted = true;

			if (isDeleted)
			{
				SetState(KOOPA_RED_STATE_WAIT_RESET);
				DebugOut(L">>> WAIT RESET >>> \n");
			}

		}
	}

	if(state == KOOPA_RED_STATE_WAIT_RESET)
	{
	
			
		//if (typeKoopa == 1)
			///CreateNewKoopa();
		//else if (typeKoopa == 2) CreateNewKoopa2();
			//DebugOut(L">>> BBBBBBBBBBB >>> \n");	
			//CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

			//CRed_Koopa* rs_koopa = new CRed_Koopa(startX, startY);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

int CRed_Koopa::LeftOrRightMarrio() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetX() < GetX()) return 1;
	else return -1;
}

int CRed_Koopa::DistanceTurtleShellisKickedWithMario() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	return abs(mario->GetX() - GetX());
}

void CRed_Koopa::Render()
{
	
	
	

		int aniId = ID_ANI_KOOPA_RED_WALKING_RIGHT;
		if (isTurtleShell) {
			switch (state)
			{
			case KOOPA_RED_STATE_ISTURTLESHELL:
				if (TailAttack) aniId = ID_ANI_RED_KOOPA_TURTLESHELL_UPSIDE;
				else aniId = ID_ANI_KOOPA_RED_TURTLESHELL;
				break;

			case KOOPA_RED_STATE_BE_HELD:
				if (TailAttack) aniId = ID_ANI_RED_KOOPA_TURTLESHELL_UPSIDE;
				else 
				aniId = ID_ANI_KOOPA_RED_TURTLESHELL;
				break;

			case KOOPA_RED_STATE_TO_RETURN:
				if (TailAttack) aniId = ID_ANI_RED_KOOPA_COMBACK_UPSIDE;
				else aniId = ID_ANI_RED_KOOPA_COMBACK;
				break;
			default: 
				if (TailAttack) aniId = ID_ANI_RED_KOOPA_KICKED_UPSIDE;
				else {
					if (vx > 0)
						aniId = ID_ANI_KOOPA_RED_ISKICKED_LEFT_TO_RIGHT;
					else if (vx < 0) aniId = ID_ANI_KOOPA_RED_ISKICKED_RIGHT_TO_LEFT;
				}
				break;
			}
			}
		else if (vx < 0) aniId = ID_ANI_KOOPA_RED_WALKING_LEFT;
		
	
	
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	/*
	if(state == KOOPA_RED_STATE_WALKING){
		if (vx > 0)
		{
			aniId = ID_ANI_KOOPA_RED_WALKING_RIGHT;
		}
		else {
			aniId = ID_ANI_KOOPA_RED_WALKING_LEFT;
		}
	}*/


	/*else
	 if (isTurtleShell && isKicked && !wasKicked)
	{
		
		 if (!isComback)
			 aniId = ID_ANI_KOOPA_RED_TURTLESHELL;

		 else aniId = ID_ANI_RED_KOOPA_COMBACK;

		DebugOut(L">>> Rua dang bien thanh mai >>> \n");
	}
	 else if(isTurtleShell && wasKicked)
	 {
		 if (vx > 0)
			 aniId = ID_ANI_KOOPA_RED_ISKICKED_LEFT_TO_RIGHT;
		 else if (vx < 0) aniId = ID_ANI_KOOPA_RED_ISKICKED_RIGHT_TO_LEFT;
		 DebugOut(L">>> Rua bi da va dang chay >>> \n");
	 }*/
	
	RenderBoundingBox();
}

void CRed_Koopa::SetState(int state)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_RED_STATE_ISTURTLESHELL:
		
		ResetKP();
		count_start = GetTickCount64();
		ResetCheck();
		isTurn = false;
		isKicked = true;
		wasKicked = false;
		isTurtleShell = true;
		HaveOrNotCheckFall = false;
		isComback = true;
		isDead = false;
		y += (KOOPA_RED_BBOX_HEIGHT - KOOPA_RED_BBOX_HEIGHT_TURTLESHELL) / 2;
		vx = 0;
		vy = 0;
		//ay = 0;
		break;

	case KOOPA_RED_STATE_TURTLESHELL_UPSIDE_TAIL_ATTACK:
		TailAttack = true;
		ResetKP();
		timeWhiped = GetTickCount64();
		ResetCheck();
		isTurn = false;
		isKicked = true;
		//wasKicked = false;
		isTurtleShell = true;
		HaveOrNotCheckFall = false;
		isComback = true;
		isDead = false;
		y += (KOOPA_RED_BBOX_HEIGHT - KOOPA_RED_BBOX_HEIGHT_TURTLESHELL) / 2;
		//vx = 0;
		//vy = 0;
		break;

	case KOOPA_RED_STATE_TO_RETURN:

		comback_time = GetTickCount64();
		isKicked = true;
		isDead = false;
		wasKicked = false;
		isTurtleShell = true;
		HaveOrNotCheckFall = false;
		isTurn = true;
		vx = 0;
		vy = 0;
		ay = KOOPA_RED_GRAVITY;
		break;
		
	case KOOPA_RED_STATE_ISKICKED:
		time_delete = GetTickCount64();
		DebugOut(L">>> KICKING >>> \n");
		wasHeld = false;
		wasKicked = true;
		isTurtleShell = true;
		HaveOrNotCheckFall = false;
		isDead = false;

		if(typeKoopa == 1 )
		vx = SPEED_KOOPA_RED_TURTLESHELL_IS_KICKED * LeftOrRightMarrio();
		else if(typeKoopa == 2)
			vx = 0.141f * LeftOrRightMarrio();
		ay = KOOPA_RED_GRAVITY;
		
		break;
	case KOOPA_RED_STATE_WALKING:
		TailAttack = false;
		if (typeKoopa == 1)
			vx = KOOPA_RED_WALKING_SPEED;
		else if (typeKoopa == 2)
		{	
			/*if (isOnPlatform) vx = 0.132f;
			else*/
			vx = 0.0107f;
		}
		isTurtleShell = false;
		isDead = false;
		HaveOrNotCheckFall = true;
		break;

	case KOOPA_RED_STATE_WALKING_ON_GLASS:
		vx = -0.009f;
		isTurtleShell = false;
		isDead = false;
		HaveOrNotCheckFall = true;
		break;



		ay = KOOPA_RED_GRAVITY;
		//vx = 0;
		break;

	case KOOPA_RED_WALKING_STATE_TURN:
		ResetCheck();
		isDead = false;
		isTurtleShell = false;
		HaveOrNotCheckFall = true;
		vx = -vx;
		DebugOut(L">>> chi xet con rua di bo >>> \n");
		break;

	case KOOPA_RED_WALKING_STATE_TURN_ON_GLASS:
		ResetCheck();
		isDead = false;
		isTurtleShell = false;
		HaveOrNotCheckFall = true;
		vx = -vx;
		DebugOut(L">>> chi xet con rua di bo >>> \n");
		break;

	case KOOPA_RED_STATE_WAIT_RESET:
		count_start = GetTickCount64();
		//time_rs = GetTickCount64();
		isDead = true;
		break;

	case KOOPA_RED_STATE_BE_HELD:
		//vx = mario->GetVx();
		//vy = mario->GetVy();
		isheld_time = GetTickCount64();
		flagHeldKick = true;
		y = mario->GetY()-3;
		
		/*if (nx > 0)
			x = mario->GetX() + 14;
		else x = GetX() - 32;*/

		//count_start = GetTickCount64();
		//collis = 0;
		//wasHeld = true;
		//isKicked = true;
		wasKicked = false;
		//isComback = false;
		ay = 0;
		break;

	case KOOPA_RED_STATE_RESET_AFTER_KICKED:
		isDead = false;
		isTurtleShell = true;
		wasKicked = false;
		isTurn = true;
		HaveOrNotCheckFall = false;
		break;

	}
}
