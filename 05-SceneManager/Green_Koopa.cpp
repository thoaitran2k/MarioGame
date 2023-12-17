#include "Green_Koopa.h"
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




CGreen_Koopa::CGreen_Koopa(float x, float y) :CGameObject(x, y)
{
	//timeFly = -1;
	//count_Fly = 0;
	//vy = -0.9f;
	isActive = false;
	this->ax = 0;
	this->ay = KOOPA_GREEN_GRAVITY;
	vx = -0.045f;
	count_start = -1;
	SetState(KOOPA_GREEN_STATE_JUMP);
	isTurtleShell = false;
	startX = x;
	startY = y;
	isOnPlatform = false;
	checkfall = NULL;
	isKicked = false;
	HaveOrNotCheckFall = true;
	isComback = false;
	wasKicked = false;
	isDead = false;
	wasHeld = false;
	time_rs = -1;
	Jump = true;
	//isheld_time = -1;
	//collis = 1;
	//CreateGoomba();

}



void CGreen_Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == KOOPA_GREEN_STATE_WALKING)
	{
		left = x - KOOPA_GREEN_BBOX_WIDTH / 2;
		top = y - KOOPA_GREEN_BBOX_HEIGHT / 2;
		right = left + KOOPA_GREEN_BBOX_WIDTH;
		bottom = top + KOOPA_GREEN_BBOX_HEIGHT + 1;
	}
	else if (state == KOOPA_GREEN_STATE_JUMP)
	{
		left = x - 8;
		top = y - KOOPA_GREEN_BBOX_HEIGHT / 3;
		right = left + KOOPA_GREEN_BBOX_WIDTH;
		bottom = top + KOOPA_GREEN_BBOX_HEIGHT + 1;
	}
	else if (/*state == KOOPA_GREEN_STATE_ISDEFEND || */state == KOOPA_GREEN_WALKING_STATE_TURN)
	{
		left = x - KOOPA_GREEN_BBOX_WIDTH / 2;
		top = y - KOOPA_GREEN_BBOX_HEIGHT / 2;
		right = left + KOOPA_GREEN_BBOX_WIDTH;
		bottom = top + KOOPA_GREEN_BBOX_HEIGHT - 6;
	}
	else if (state == KOOPA_GREEN_STATE_ISTURTLESHELL)
	{
		left = x - KOOPA_GREEN_BBOX_WIDTH / 2;
		top = y - KOOPA_GREEN_BBOX_HEIGHT / 2;
		right = left + KOOPA_GREEN_BBOX_WIDTH;
		bottom = top + KOOPA_GREEN_BBOX_HEIGHT-6;
	}
	else
	{
		left = x - KOOPA_GREEN_BBOX_WIDTH / 2;
		top = y - KOOPA_GREEN_BBOX_HEIGHT / 2;
		right = left + KOOPA_GREEN_BBOX_WIDTH;
		bottom = top + KOOPA_GREEN_BBOX_HEIGHT - 7;
	}

}



void CGreen_Koopa::CreateNewKoopa() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (isDead /*&& GetTickCount64() - time_rs > 4000*/) {
		CGameObject* new_koopa1 = scene->CreateObjectAndReturn(OBJECT_TYPE_GREEN_KOOPA_WALKING, startX, startY, 0, 0);
		//CGameObject* new_koopa2 = scene->CreateObjectAndReturn(OBJECT_TYPE_GREEN_KOOPA_WALKING, startX+35, startY, 0, 0);
		Addnew_koopa(new_koopa1);
		//Addnew_koopa(new_koopa2);
		DebugOut(L">>> koopa duoc rs >>> \n");
		SetState(KOOPA_GREEN_STATE_JUMP);
	}

}

void CGreen_Koopa::CreateCheckfall() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (vx < 0)
	{
		CGameObject* add_object_left = scene->CreateObjectAndReturn(OBJECT_TYPE_CHECKFALL_KOOPA, GetX() - KOOPA_GREEN_BBOX_WIDTH, y + 2, 0, 0);
		AddCheck(add_object_left);
		DebugOut(L">>> check tao obj left >>> \n");
		checkfall->SetState(STATE_LEFT_KOOPA);
		checkfall->SETay(0.009f);


	}
	else if (vx >= 0)
	{
		CGameObject* add_object_right = scene->CreateObjectAndReturn(OBJECT_TYPE_CHECKFALL_KOOPA, GetX() + KOOPA_GREEN_BBOX_WIDTH, y + 2, 0/* KOOPA_GREEN_WALKING_SPEED*/, 0);

		AddCheck(add_object_right);
		DebugOut(L">>> check tao obj right >>> \n");
		checkfall->SetState(STATE_RIGHT_KOOPA);
		checkfall->SETay(0.009f);

	}

}

void CGreen_Koopa::OnNoCollision(DWORD dt)
{
	Green_Koopa_Active();
	if (isActive) {
		x += vx * dt;
		y += vy * dt;
	}
};


void CGreen_Koopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGreen_Koopa*>(e->obj)) return;
	if (dynamic_cast<CbulletPlant*>(e->obj)) return;
	//if (state == KOOPA_GREEN_STATE_BE_HELD) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		if (isOnPlatform) {
			ResetCheck();
		}
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

void CGreen_Koopa::OnCollisionWithOntheBox(LPCOLLISIONEVENT e) {



	if (e->ny < 0)
	{
		isOnPlatform = true;
		if (Jump) Fall = false;
		//rangeFly += 25;
	}

}

void CGreen_Koopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e) {
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (x > goomba->GetX())
	{
		vx = -vx;
		x = x - GOOMBA_BBOX_HEIGHT / 2 - 2;
	}
	else {
		vx = -vx;
		x = x + GOOMBA_BBOX_HEIGHT / 2 + 2;
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
				//x += KOOPA_GREEN_BBOX_WIDTH / 2;
			}
	}

}

void CGreen_Koopa::OnCollisionWithBrick_Question(LPCOLLISIONEVENT e) {

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

void CGreen_Koopa::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	CBackground* platform = dynamic_cast<CBackground*>(e->obj);
	if (e->ny < 0) {
		isOnPlatform = true;
		if(Jump) Fall = false;
		
		//if (state != KOOPA_GREEN_STATE_WALKING) Jump = true;
	}

	//if (y > (platform->GetY()+50)) isDeleted = true;



	if (isOnPlatform && state != KOOPA_GREEN_STATE_WALKING)
	{
		//isTurtleShell = true;

	}
}

void CGreen_Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//if (isOnPlatform) timeFly = GetTickCount64();
	
	//if (GetY() > startY) rangeFly + 80;
	Green_Koopa_Active();
	if (isActive)
	{


		vy += ay * dt;
		vx += ax * dt;


		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();


		if (!isDead) {

			if (Jump)
			{
				SetState(KOOPA_GREEN_STATE_JUMP);
				vx = -KOOPA_GREEN_WALKING_SPEED;
				y = y - 2.5;

				if (y > 650) isDeleted = true;

				if (isDeleted)
				{
					SetState(KOOPA_GREEN_STATE_WAIT_RESET);
					DebugOut(L">>> WAIT RESET >>> \n");
				}


				//vy = 0.0004f;
				//ay = 0.005f;

				// vy = 0.06f;
			}
			else
			{



				if (!isTurtleShell && HaveOrNotCheckFall) {

					if (checkfall == NULL)
					{
						//CreateCheckfall();
						//DebugOut(L">>> CHECK TAO OBJ >>> \n");
						ResetCheck();
					}
					else
						if (!checkfall->GetIsOnPlatform())
						{
							SetState(KOOPA_GREEN_WALKING_STATE_TURN);
							DebugOut(L">>> MOVING >>> \n");

						}
				}
				else //isTurtleshell and Not Checkfall
					if (!wasKicked && state != KOOPA_GREEN_STATE_BE_HELD)
					{
						if (!mario->GetIsHolding() && !wasHeld && !isTurn && GetTickCount64() - count_start > TURTLE_SHELL_TOTURN_KOOPA)
						{
							//count_start = GetTickCount64();
							y = y - KOOPA_GREEN_BBOX_HEIGHT / 2;
							SetState(KOOPA_GREEN_STATE_TO_RETURN);
							DebugOut(L">>> RETURN >>> \n");

						}
						if (!mario->GetIsHolding() && !wasHeld && isTurn && GetTickCount64() - comback_time > TIME_COMBACK_KOOPA)
						{

							SetState(KOOPA_GREEN_STATE_WALKING);
							count_start = GetTickCount64();
							vx = -KOOPA_GREEN_WALKING_SPEED;
							y = y - KOOPA_GREEN_BBOX_HEIGHT / 2;
							DebugOut(L">>> HOI SINH TU MAI RUA >>> \n");
						}
					}

				if (state == KOOPA_GREEN_STATE_BE_HELD)
				{
					//isheld_time = GetTickCount64();
					vx = mario->GetVx();
					vy = mario->GetVy();
					this->x = mario->GetX() + mario->GetNx() * (MARIO_BIG_BBOX_WIDTH - 3);
					this->y = mario->GetY() - 3;

					if (!mario->GetIsHold())
					{
						SetState(KOOPA_GREEN_STATE_ISKICKED);
						flagHeldKick = false;
						//wasHeld = false;
					}
					else
						if (GetTickCount64() - isheld_time > 6000)
						{
							//if (!mario->GetIsHolding())
							//{

							this->y = mario->GetY();
							//SetState(KOOPA_GREEN_STATE_TO_RETURN);
							if (mario->GetIsHolding())
							{
								SetState(KOOPA_GREEN_STATE_TO_RETURN);
								if (GetTickCount64() - comback_time > 500)
								{

									//count_start = GetTickCount64();
									SetState(KOOPA_GREEN_STATE_WALKING);
									DebugOut(L">>> RETURN >>> \n");

								}
							}
							else
								SetState(KOOPA_GREEN_STATE_ISKICKED);

							//}
						}
				}
				if (state == KOOPA_GREEN_STATE_ISKICKED)
				{
					if ((DistanceTurtleShellisKickedWithMario() > DISTANCE_MIN_SHELL_EXIST && GetTickCount64() - time_delete > TURTLE_SHELL_TIMEOUT) )
						isDeleted = true;

					if (isDeleted)
					{
						SetState(KOOPA_GREEN_STATE_WAIT_RESET);
						DebugOut(L">>> WAIT RESET >>> \n");
					}

				}

			}
		}




		if (state == KOOPA_GREEN_STATE_WAIT_RESET)
		{
			
				CreateNewKoopa();
				DebugOut(L">>> BBBBBBBBBBB >>> \n");
				//CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
			
			//CGreen_Koopa* rs_koopa = new CGreen_Koopa(startX, startY);
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

int CGreen_Koopa::LeftOrRightMarrio() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetX() < GetX()) return 1;
	else return -1;
}

int CGreen_Koopa::DistanceTurtleShellisKickedWithMario() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	return abs(mario->GetX() - GetX());
}

void CGreen_Koopa::Render()
{
	int aniId;
	if (!Jump) {
		aniId = ID_ANI_KOOPA_GREEN_WALKING_RIGHT;
		 
		if (isTurtleShell) {
			switch (state)
			{
			case KOOPA_GREEN_STATE_ISTURTLESHELL:
				aniId = ID_ANI_KOOPA_GREEN_TURTLESHELL;
				break;

			case KOOPA_GREEN_STATE_BE_HELD:
				aniId = ID_ANI_KOOPA_GREEN_TURTLESHELL;
				break;

			case KOOPA_GREEN_STATE_TO_RETURN:
				aniId = ID_ANI_GREEN_KOOPA_COMBACK;
				break;
			default: if (vx > 0)
				aniId = ID_ANI_KOOPA_GREEN_ISKICKED_LEFT_TO_RIGHT;
				   else if (vx < 0) aniId = ID_ANI_KOOPA_GREEN_ISKICKED_RIGHT_TO_LEFT;

				break;
			}
		}
		else {
			

				if (vx < 0) aniId = ID_ANI_KOOPA_GREEN_WALKING_LEFT;
				 
			
		}
	}
	else {
		if (vx > 0) aniId = ID_ANI_GREEN_WING_RIGHT;
		else aniId = ID_ANI_GREEN_WING_LEFT;
	}

	/*
	if(state == KOOPA_GREEN_STATE_WALKING){
		if (vx > 0)
		{
			aniId = ID_ANI_KOOPA_GREEN_WALKING_RIGHT;
		}
		else {
			aniId = ID_ANI_KOOPA_GREEN_WALKING_LEFT;
		}
	}*/


	/*else
	 if (isTurtleShell && isKicked && !wasKicked)
	{

		 if (!isComback)
			 aniId = ID_ANI_KOOPA_GREEN_TURTLESHELL;

		 else aniId = ID_ANI_GREEN_KOOPA_COMBACK;

		DebugOut(L">>> Rua dang bien thanh mai >>> \n");
	}
	 else if(isTurtleShell && wasKicked)
	 {
		 if (vx > 0)
			 aniId = ID_ANI_KOOPA_GREEN_ISKICKED_LEFT_TO_RIGHT;
		 else if (vx < 0) aniId = ID_ANI_KOOPA_GREEN_ISKICKED_RIGHT_TO_LEFT;
		 DebugOut(L">>> Rua bi da va dang chay >>> \n");
	 }*/
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGreen_Koopa::SetState(int state)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_GREEN_STATE_ISTURTLESHELL:
		Jump = false;
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
		y += (KOOPA_GREEN_BBOX_HEIGHT - KOOPA_GREEN_BBOX_HEIGHT_TURTLESHELL) / 2;
		vx = 0;
		vy = 0;
		//ay = 0;
		break;

	case KOOPA_GREEN_STATE_TO_RETURN:
		Jump = false;
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

	case KOOPA_GREEN_STATE_ISKICKED:
		Jump = false;
		time_delete = GetTickCount64();
		DebugOut(L">>> KICKING >>> \n");
		wasHeld = false;
		wasKicked = true;
		isTurtleShell = true;
		HaveOrNotCheckFall = false;
		isDead = false;
		vx = SPEED_KOOPA_GREEN_TURTLESHELL_IS_KICKED * LeftOrRightMarrio();
		ay = KOOPA_GREEN_GRAVITY;

		break;
	case KOOPA_GREEN_STATE_WALKING:
		Jump = false;
		vx = -KOOPA_GREEN_WALKING_SPEED;
		isTurtleShell = false;
		isDead = false;
		HaveOrNotCheckFall = true;
		ay = KOOPA_GREEN_GRAVITY;
		//vx = 0;
		break;

	case KOOPA_GREEN_WALKING_STATE_TURN:
		Jump = false;
		ResetCheck();
		Jump = false;
		isDead = false;
		isTurtleShell = false;
		HaveOrNotCheckFall = true;
		vx = -vx;
		DebugOut(L">>> chi xet con rua di bo >>> \n");
		break;

	case KOOPA_GREEN_STATE_WAIT_RESET:
		count_start = GetTickCount64();
		//time_rs = GetTickCount64();
		isDead = true;
		break;

	case KOOPA_GREEN_STATE_BE_HELD:
		Jump = false;
		//vx = mario->GetVx();
		//vy = mario->GetVy();
		isheld_time = GetTickCount64();
		flagHeldKick = true;
		y = mario->GetY() - 3;

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

	case KOOPA_GREEN_STATE_JUMP:
		wasKicked = false;
		//timeFly = GetTickCount64();
		isTurtleShell = false;
		//ay = KOOPA_GREEN_GRAVITY;
		//if (mario->GetX() < x)
			//vx = -0.02f;
		//else vx = 0.02f;

		isDead = false;
		//if(y>rangeFly)
		//{
		//	Fall = true;
		//	//vy = 0.04f;
		//}
		//vy = -0.2f;
		//vx = -0.03f;
		//vy = 0.04f;
		Jump = true;
		break;

	case KOOPA_GREEN_STATE_FALL:
		isDead = false;
		vy = 0.04f;
			//vy = 0.06f;
			//Fall = false;
		
		//ay = 0.4f;
		break;

	}
}