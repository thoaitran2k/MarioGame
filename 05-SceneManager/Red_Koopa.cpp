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




CRed_Koopa::CRed_Koopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_RED_GRAVITY;
	count_start =GetTickCount64();
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
	time_rs = -1;
	CreateGoomba();
	
}



void CRed_Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == KOOPA_RED_STATE_WALKING )
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
	else if(state == KOOPA_RED_STATE_ISTURTLESHELL)
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

	
		CGameObject* goomba = scene->CreateObjectAndReturn(OBJECT_TYPE_GOOMBA_UNDER_KOOPA, startX, startY + 20, 0, 0);
		AddGoomba(goomba);
		DebugOut(L">>> TAO RA GOOMBA >>> \n");
		goomba_under_koopa->SetState(GOOMBA_STATE_WALKING);
	
	
}

void CRed_Koopa::CreateNewKoopa() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (isDead /*&& GetTickCount64() - time_rs > 4000*/) {
		CGameObject* new_koopa = scene->CreateObjectAndReturn(OBJECT_TYPE_RED_KOOPA_WALKING, startX, startY, 0, 0);
			Addnew_koopa(new_koopa);
			DebugOut(L">>> koopa duoc rs >>> \n");
			SetState(KOOPA_RED_STATE_WALKING);
	}
	
}

void CRed_Koopa::CreateCheckfall() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

		if (vx<0)
		{
			CGameObject* add_object_left = scene->CreateObjectAndReturn(OBJECT_TYPE_CHECKFALL_KOOPA, GetX()- KOOPA_RED_BBOX_WIDTH, y, 0, 0);
				AddCheck(add_object_left);
				DebugOut(L">>> check tao obj left >>> \n");
				checkfall->SetState(STATE_LEFT_KOOPA);
			
			
		}
		else if(vx>=0)
		{
			CGameObject* add_object_right = scene->CreateObjectAndReturn(OBJECT_TYPE_CHECKFALL_KOOPA, GetX()+ KOOPA_RED_BBOX_WIDTH, y,0/* KOOPA_RED_WALKING_SPEED*/, 0);
			
			AddCheck(add_object_right);
			DebugOut(L">>> check tao obj right >>> \n");
			checkfall->SetState(STATE_RIGHT_KOOPA);
			
		}

}

void CRed_Koopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};


void CRed_Koopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CRed_Koopa*>(e->obj)) return;
	if (dynamic_cast<CbulletPlant*>(e->obj)) return;

	
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

	if (dynamic_cast<CBackground*>(e->obj))
		this->OnCollisionWithPlatForm(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CBrickQuestion*>(e->obj))
		OnCollisionWithBrick_Question(e);
	else if (dynamic_cast<CBox*>(e->obj))
		OnCollisionWithOntheBox(e);
}

void CRed_Koopa::OnCollisionWithOntheBox(LPCOLLISIONEVENT e) {

	if (e->ny < 0)
		isOntheBox = true;

}

void CRed_Koopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (x > goomba->GetX())
	{
		vx = -vx;
		x = x - GOOMBA_BBOX_HEIGHT/2;
	}
	else { 
		vx = -vx;
		x = x + GOOMBA_BBOX_HEIGHT/2;
	}


	if (wasKicked) {
		if (goomba->GetState() == GOOMBA_STATE_THROWN_BY_KOOPA) return;
			
		else
		if (goomba->GetState() != GOOMBA_STATE_THROWN_BY_KOOPA)
		{
			goomba->SetState(GOOMBA_STATE_THROWN_BY_KOOPA);
			//goomba->SetVy(-0.02f);
			//goomba->SetVx(-0.01f);
			//goomba->SetY(y + 2);
			//x += KOOPA_RED_BBOX_WIDTH / 2;
		}
	}
	
}

void CRed_Koopa::OnCollisionWithBrick_Question(LPCOLLISIONEVENT e) {

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

			if (questionBrick->GetModel() == QUESTION_BRICK_LEAF)
			{
				CLeaf* leaf = new CLeaf(xTemp, yTemp);
				leaf->SetState(LEAF_SUMMON_STATE);
				scene->AddObject(leaf);
				questionBrick->SetState(BRICK_Q_STATE_EMPTY);
				questionBrick->SetIsEmpty(true);
				questionBrick->SetIsUnbox(true);
			}
		}
	}
}

void CRed_Koopa::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	CBackground* platform = dynamic_cast<CBackground*>(e->obj);
	if (e->ny < 0) {
		isOnPlatform = true;
	}

	if (isOnPlatform && state != KOOPA_RED_STATE_WALKING)
	{
		isTurtleShell = true;

	}
}

void CRed_Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (!isDead) {
		if (isOntheBox)
		{
			if (!isTurtleShell && HaveOrNotCheckFall) {
				//count_start = GetTickCount64();

				if (checkfall == NULL)
				{
					CreateCheckfall();
					DebugOut(L">>> CHECK TAO OBJ >>> \n");
				}
				else 
					if (checkfall->GetIsOnPlatform())
				{
					SetState(KOOPA_RED_WALKING_STATE_TURN);
					DebugOut(L">>> MOVING >>> \n");

				}
			}
			else //isTurtleshell and Not Checkfall
				if(!wasKicked)
				{
						if (!wasHeld && !isTurn && GetTickCount64() - count_start > TURTLE_SHELL_TOTURN_KOOPA)
						{
							SetState(KOOPA_RED_STATE_TO_RETURN);
							DebugOut(L">>> RETURN >>> \n");

						}
					    if (!wasHeld && isTurn && GetTickCount64() - comback_time > TIME_COMBACK_KOOPA)
					    {

							SetState(KOOPA_RED_STATE_WALKING);
							vx = KOOPA_RED_WALKING_SPEED;
							y = y - KOOPA_RED_BBOX_HEIGHT / 2;
							DebugOut(L">>> HOI SINH TU MAI RUA >>> \n");
						}
				}
		}

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
	
			CreateNewKoopa();
			DebugOut(L">>> BBBBBBBBBBB >>> \n");	
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
			aniId = ID_ANI_KOOPA_RED_TURTLESHELL;
			break;


		case KOOPA_RED_STATE_TO_RETURN:
			aniId = ID_ANI_RED_KOOPA_COMBACK;
			break;
		default: if (vx > 0)
			aniId = ID_ANI_KOOPA_RED_ISKICKED_LEFT_TO_RIGHT;
			   else if (vx < 0) aniId = ID_ANI_KOOPA_RED_ISKICKED_RIGHT_TO_LEFT;

			break;
		}
	}
	else if (vx < 0) aniId = ID_ANI_KOOPA_RED_WALKING_LEFT;


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
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
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
		break;
		
	case KOOPA_RED_STATE_ISKICKED:
		time_delete = GetTickCount64();
		DebugOut(L">>> KICKING >>> \n");
		wasHeld = false;
		wasKicked = true;
		isTurtleShell = true;
		HaveOrNotCheckFall = false;
		isDead = false;
		vx = SPEED_KOOPA_RED_TURTLESHELL_IS_KICKED * LeftOrRightMarrio();
		
		break;
	case KOOPA_RED_STATE_WALKING:
		vx = KOOPA_RED_WALKING_SPEED;
		isTurtleShell = false;
		isDead = false;
		HaveOrNotCheckFall = true;
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

	case KOOPA_RED_STATE_WAIT_RESET:
		count_start = GetTickCount64();
		//time_rs = GetTickCount64();
		isDead = true;
		break;

	case KOOPA_RED_STATE_BE_HELD:
		//vx = mario->GetVx();
		//vy = mario->GetVy();
		y = y - 30;
		wasHeld = true;
		isKicked = false;
		wasKicked = false;
		break;

	}
}
