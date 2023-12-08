#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "BrickQuestion.h"

#include "Collision.h"
#include "GameObject.h"
#include "PlayScene.h"
#include "MushRoom.h"
#include "bullet_plant.h"
#include "PlantShootRed.h"
#include "Green_Koopa.h"
#include "Red_Koopa.h"
#include "leaf.h"
#include "Para_Goomba.h"
#include "PipePlantShoot.h"





void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CPara_Goomba*>(e->obj))
		OnCollisionWithPara_Goomba(e);
	else if (dynamic_cast<CGreen_Koopa*>(e->obj))
		OnCollisionWithKoopa_Green_notWing(e);
	else if (dynamic_cast<CRed_Koopa*>(e->obj))
		OnCollisionWithRed_Koopa(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CBrickQuestion*>(e->obj))
		OnCollisionWithBrickQuestion(e);
	else if (dynamic_cast<CMushRoom*>(e->obj))
		OnCollisionWithMushRoom(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CbulletPlant*>(e->obj))
		OnCollisionWithFire_Bullet(e);
	else if (dynamic_cast<CPlantShootRed*>(e->obj))
		OnCollisionWithPlantShootRed(e);
	else if (dynamic_cast<CPipePlantShoot*>(e->obj))
		OnCollisionWithPipe(e);
}

void CMario::OnCollisionWithPipe(LPCOLLISIONEVENT e) {

}

void CMario::OnCollisionWithKoopa_Green_notWing(LPCOLLISIONEVENT e)
{
	CGreen_Koopa* koopa = dynamic_cast<CGreen_Koopa*>(e->obj);


	if (e->ny < 0)
	{
		if (koopa->GetState() != KOOPA_GREEN_NOT_WING_STATE_ISTURTLESHELL)
		{
			koopa->SetState(KOOPA_GREEN_NOT_WING_STATE_ISTURTLESHELL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by koopa not wing walking
	{
		if (untouchable == 0)
		{
			if (koopa->GetState() != KOOPA_GREEN_NOT_WING_STATE_ISTURTLESHELL)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithPlantShootRed(LPCOLLISIONEVENT e)
{
	CPlantShootRed* pshootred = dynamic_cast<CPlantShootRed*>(e->obj);

	

	if (pshootred->StateActive()) {

		if (untouchable == 0) {
			if (pshootred->GetState() != PLANT_STATE_NOT_TOUCH) {
				if (level > MARIO_LEVEL_SMALL)
				{
					
					if (level > MARIO_LEVEL_BIG)
					{
						level = MARIO_LEVEL_BIG;
						StartUntouchable();
					}
					else
					{
						level = MARIO_LEVEL_SMALL;


						StartUntouchable();
					}
				}
				else
				{
					DebugOut(L">>> Mario DIE by Plant Enemies >>> \n");
					SetState(MARIO_STATE_DIE);
					//isDeleted = true; sai
				}
			}
		}
	}
	else return;
}

void CMario::OnCollisionWithFire_Bullet(LPCOLLISIONEVENT e)
{
		CbulletPlant* fire_bullet = dynamic_cast<CbulletPlant*>(e->obj);
		if (untouchable == 0) {
			if (level > MARIO_LEVEL_SMALL)
			{
				if (level > MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else
				{
					level = MARIO_LEVEL_SMALL;


					StartUntouchable();
				}
			}
			else
			{
				DebugOut(L">>> Mario DIE by Fire_Bullet >>> \n");
				SetState(MARIO_STATE_DIE);
			}
			e->obj->Delete();
		}

}

void CMario::OnCollisionWithPara_Goomba(LPCOLLISIONEVENT e)
{
	CPara_Goomba* pr_goomba = dynamic_cast<CPara_Goomba*>(e->obj);
	float xTemp, yTemp;
	xTemp = pr_goomba->GetX();
	yTemp = pr_goomba->GetY();

	
	if (e->ny < 0)
	{
		if (pr_goomba->IsFly()) {
			pr_goomba->SetState(GOOMBA_RED_STATE_FALL);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			if (x - pr_goomba->GetX() < 0) pr_goomba->SetVx(-SPEED_GOOMBA_RED_WALKING);
			else if (x - pr_goomba->GetX() > 0) pr_goomba->SetVx(SPEED_GOOMBA_RED_WALKING);
			
		}
		else
		{
			pr_goomba->SetState(GOOMBA_RED_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}


	}
	else // hit by koopa not wing walking
	{
		if (untouchable == 0)
		{
				if (level > MARIO_LEVEL_SMALL)
				{
					if (level > MARIO_LEVEL_BIG)

						level = MARIO_LEVEL_BIG;

					else level = MARIO_LEVEL_SMALL;
					
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
		}
	}
	
}




//#######-06/12/2023////// bug mario hold turtleshell  
void CMario::OnCollisionWithRed_Koopa(LPCOLLISIONEVENT e)
{
	CRed_Koopa* koopared = dynamic_cast<CRed_Koopa*>(e->obj);
		/*if (koopared->GetState() == KOOPA_RED_STATE_WALKING) {
		koopared->SetState(KOOPA_RED_STATE_ISTURTLESHELL);
		}*/
	ULONGLONG red_koopa_comback;
	red_koopa_comback = koopared->GetTimeComback();
	bool wasKicked;
	wasKicked = koopared->GETwasKicked();


	if (koopared->GetIsTurtleShell())
	{
		// K nhan A isHold = false , nhan phim A isHold = true; isHold = true -> holding;
		if (!koopared->GETwasKicked())
		{
			if (e->ny < 0) {
				if (koopared->GetIsKick()) {
					//SetState(MARIO_STATE_KICK);
					koopared->SetState(KOOPA_RED_STATE_ISKICKED);
					//isHold = false;
				}
			}
			else
				if (e->nx != 0){
						//if(abs(x-koopared->GetX())<100)
					if (!Holding)
					{
						
							if (koopared->GetIsKick())
							{
								SetState(MARIO_STATE_KICK);
								koopared->SetState(KOOPA_RED_STATE_ISKICKED);
								//isHold = false;
							}
						
					}
					else{
						koopared->SetState(KOOPA_RED_STATE_BE_HELD);
							

						
							//koopared->SetState(KOOPA_RED_STATE_ISKICKED);
							//koopared->SetIsKick(false);
							//koopared->SetShell(true);
							/*koopared->SetY(y-20);
							koopared->SetVx(0);
							koopared->SETay(0);
							koopared->SetVy(0);*/
							
						}
				}

		}
		else {
			if (untouchable == 0)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					if (level > MARIO_LEVEL_BIG)

						level = MARIO_LEVEL_BIG;

					else level = MARIO_LEVEL_SMALL;
					StartUntouchable();
					DebugOut(L">>> Mario biến nhỏ >>> \n");
				}
				else
				{
					DebugOut(L">>> Mario DIE by TurtleShell move or  by KOOPA WALKING >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}

		}

		/*if (koopared->GetState() == KOOPA_RED_STATE_BE_HELD)
		{
			if (!koopared->GETwasKicked() && !isHold)
				koopared->SetState(KOOPA_RED_STATE_ISKICKED);
		}*/


	}
	else
	{
		if (e->ny < 0)
		{
			
			bool isCombackRedKoopa;
			isCombackRedKoopa = koopared->GetIsComback();

			if (koopared->GetState() != KOOPA_RED_STATE_ISTURTLESHELL && koopared->GetState() != KOOPA_RED_STATE_ISKICKED && koopared->GetState() != KOOPA_RED_STATE_TO_RETURN) //STATE_WALKING
			{
				
				koopared->SetState(KOOPA_RED_STATE_ISTURTLESHELL);
				isHold = true;
				vy = -MARIO_JUMP_DEFLECT_SPEED;
				DebugOut(L">>> KOOPA -> TURTLESHELL by MARIO -> KOOPA IN STATE WALKING >>> \n");


			}
		}
		else
		{// hit by red koopa (walking or turtleshell is kicked)
			if (untouchable == 0)
			{
				
				if (koopared->GetState() != KOOPA_RED_STATE_ISTURTLESHELL && koopared->GetState() != KOOPA_RED_STATE_TO_RETURN)
				{
					if (level > MARIO_LEVEL_SMALL)
					{
						if (level > MARIO_LEVEL_BIG)

							level = MARIO_LEVEL_BIG;

						else level = MARIO_LEVEL_SMALL;
						StartUntouchable();
						DebugOut(L">>> Mario biến nhỏ >>> \n");
					}
					else
					{
						DebugOut(L">>> Mario DIE by TurtleShell move or  by KOOPA WALKING >>> \n");
						SetState(MARIO_STATE_DIE);
					}
				}
			}
		}
	}

}


void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					if (level > MARIO_LEVEL_BIG)

						level = MARIO_LEVEL_BIG;

					else level = MARIO_LEVEL_SMALL;

					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	

	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithBrickQuestion(LPCOLLISIONEVENT e)
{

	

	CBrickQuestion* questionBrick = dynamic_cast<CBrickQuestion*>(e->obj);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	BOOLEAN isUnBox, isEmpty;
	isUnBox = questionBrick->GetIsUnbox();
	isEmpty = questionBrick->GetIsEmpty();

	float xTemp, yTemp, minY;
	xTemp = questionBrick->GetX();
	yTemp = questionBrick->GetY();
	minY = questionBrick->GetMinY();

	if (isUnBox) return;

	if (e->ny > 0 && !isUnBox && !isEmpty) {

		

		if (questionBrick->GetModel() == QUESTION_BRICK_MUSHROOM)
		{
				CMushRoom* mushroom = new CMushRoom(xTemp, yTemp - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN));

				//CbulletPlant* bullet = new CbulletPlant(xTemp + 50, yTemp);
				//CBrick* newbullet = new CBrick(367, 320);


				scene->AddObject(mushroom);
				//scene->AddObject(bullet);

				//scene->AddObject(newbullet);
				questionBrick->SetState(BRICK_Q_STATE_EMPTY);
				questionBrick->SetState(BRICK_Q_STATE_UP);
				questionBrick->SetIsEmpty(true);
				questionBrick->SetIsUnbox(true);

			
		}
		  else if (questionBrick->GetModel() == QUESTION_BRICK_COIN)
		{

			SetCoin(GetCoin() + 1);
			CCoin* coin = new CCoin(xTemp, yTemp);
			coin->SetState(COIN_SUMMON_STATE);
			scene->AddObject(coin);
			questionBrick->SetState(BRICK_Q_STATE_EMPTY);
			questionBrick->SetState(BRICK_Q_STATE_UP);
			questionBrick->SetIsEmpty(true);
			questionBrick->SetIsUnbox(true);
			coin++;

		}
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}


void CMario::OnCollisionWithMushRoom(LPCOLLISIONEVENT e)
{
	CMushRoom* mr = dynamic_cast<CMushRoom*>(e->obj);
	if (!mr->IsDeleted())
	{
		if (level == MARIO_LEVEL_SMALL)
		{
			SetLevel (MARIO_LEVEL_BIG);
			y = y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT);
		}
	}
	mr->Delete();
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	if (level > MARIO_LEVEL_SMALL)
	{
		if (level > MARIO_LEVEL_BIG)
		{
			leaf->Delete();
			return;
		}

		else SetLevel(MARIO_LEVEL_RACOON);
		y = y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT);
	}
	else
		
		SetLevel(MARIO_LEVEL_BIG);
	leaf->Delete();
}
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (Kicking)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
			}
			else if (Holding)
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT;
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else 
			if (Kicking)
		{
			if (nx > 0) aniId = ID_ANI_MARIO_KICK_RIGHT;
			else aniId = ID_ANI_MARIO_KICK_LEFT;
		}
			else if (Holding)
				if (nx > 0) aniId = ID_ANI_MARIO_BIG_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_BIG_HOLD_IDLE_LEFT;
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}


// Get animdation ID for Racoon

int CMario::GetAniIdRacoon(){
	
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_RACOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_RACOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_RACOON_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_RACOON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_RACOON_SIT_RIGHT;
			else
				aniId = ID_ANI_RACOON_SIT_LEFT;
		}
		else
			if (Kicking)
			{
				if (nx > 0) aniId = ID_ANI_RACOON_KICK_RIGHT;
				else aniId = ID_ANI_RACOON_KICK_LEFT;
			}
			else if (Holding)
				if (nx > 0) aniId = ID_ANI_RACOON_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_RACOON_HOLD_IDLE_LEFT;
			else
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_RACOON_IDLE_RIGHT;
					else aniId = ID_ANI_RACOON_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (ax < 0)
						aniId = ID_ANI_RACOON_BRACE_RIGHT;
					else if (ax == MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_RACOON_RUNNING_RIGHT;
					else if (ax == MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_RACOON_WALKING_RIGHT;
				}
				else // vx < 0
				{
					if (ax > 0)
						aniId = ID_ANI_RACOON_BRACE_LEFT;
					else if (ax == -MARIO_ACCEL_RUN_X)
						aniId = ID_ANI_RACOON_RUNNING_LEFT;
					else if (ax == -MARIO_ACCEL_WALK_X)
						aniId = ID_ANI_RACOON_WALKING_LEFT;
				}

	if (aniId == -1) aniId = ID_ANI_RACOON_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	if (Kicking && GetTickCount64() - timing > 200)
	{
		Kicking = false;
	}

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		//if (Holding) break;
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		//if (Holding) break;
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_KICK:
		timing = GetTickCount64();
		Kicking = true;
		break;

	case MARIO_STATE_HOLDING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		//Holding = true;
		break;

	case MARIO_STATE_HOLDING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		//Holding = true;
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level != MARIO_LEVEL_SMALL)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	

	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;

		//y -= 9;
	}
	//if (this->level == MARIO_LEVEL_RACOON)
	//{
	//	y = y - 9;
	//	//isOnPlatform = true;
	//}
	level = l;
}

