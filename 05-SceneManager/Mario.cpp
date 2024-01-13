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
#include "Green_Plant.h"
#include "glassBrick.h"
#include "ButtonP.h"
#include "GameEffects.h"
#include "Platform.h"
#include "Background.h"
#include "Card.h"





void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//ay = 0.0007f;
	//Enter_map = false;
	//contact_door = false;
	//if (Enter_map) {
	//	CGame::GetInstance()->InitiateSwitchScene(5);
	//}

	//CGame::GetInstance()->InitiateSwitchScene(5);

	vy += ay * dt;
	vx += ax * dt;

	//if (state == MARIO_STATE_DIE) UP_M = 1;

	/*if ((state == RACOON_STATE_FLY_DOWN_RELEASE || state == RACOON_STATE_FLY) && !isOnPlatform) {
		ay = 0.0014f;
	}
	else ay = MARIO_GRAVITY;*/

	/*if (state == MARIO_STATE_RELEASE_JUMP && !isOnPlatform)
	{
		if (level == 3)
			if (vy > 0) ay = 0.00001f;
			else ay = MARIO_GRAVITY;
	}
	*/

	if (abs(vx) > abs(maxVx)) vx = maxVx;



	if(state != MARIO_STATE_DIE) CountDownTimes();
	//CountDownTimeGame();

	if (goEndMap && isOnPlatform)
	{
		if (x < POSITION_END_MAP_1)
			SetState(MARIO_STATE_WALKING_RIGHT);
		else { 
			SetState(MARIO_STATE_IDLE);
			if (GetTickCount64() - time_uncontrol > 4000) {
				SetPositionPlayer(30, 320);
				goEndMap = false;
				level = 1;
			}

		}

		/*if (x > 2800)
			goEndMap = false;*/
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if ((!Run) || abs(vx) < 0.0007 || state == MARIO_STATE_IDLE  /* || (FlyHigh&&!isOnPlatform)*/)
	{
		if (GetTickCount64() - stop_speed > 250) {
			if (markFly > 0 && GetTickCount64() - time_fly_start >3000 && !Fly && GetTickCount64() - time_fly_max >7000) markFly--;
			stop_speed = GetTickCount64();
		}

		start_prepare = GetTickCount64();

	}
	else {
		if (GetTickCount64() - start_prepare > 400) {
			if (GetTickCount64() - start_speed > 150) {
				if (markFly < 9) markFly++;

				start_speed = GetTickCount64();
			}
		}

	}

	if (time_maintain_fly_low != -1) {
		if (GetTickCount64() - time_maintain_fly_low > 100) {
			ay = MARIO_GRAVITY;
			time_maintain_fly_low = -1;
		}
	}
	//if (FlyHigh) ay = 0;
	//else ay = MARIO_GRAVITY;

	if (Fly) {

		
		//Run = false;
		if (state == RACOON_STATE_START_FLY)
			ay = 0;

		if (GetTickCount64() - time_fly_max < 200)
			ay = -0.0f;

		if (GetTickCount64() - time_fly_max > 7000)
		{
			SetState(RACOON_STATE_END_FLY);
		}

		else if (GetTickCount64() - time_maintain_fly_high > 50)
		{
			SetState(RACOON_STATE_RELEASE_FLY_HIGH);
		}

		if (isOnPlatform) {
			time_fly_start = GetTickCount64();
			Fly = false;
			//vy = -0.27f;
			ay = MARIO_GRAVITY;
		}
	}
	



	
	

	if (state == RACOON_STATE_START_FLY) {
		if (GetTickCount64() - time_fly_max < 2500) Fly = true;
		else Fly = false;
	}

	if (flyLowDown) {
		ay = 0.0f;
		vy = -0.0f;
		/*if (nx != 0) {
			if (nx > 0) vx = 0.13;
			else vx = -0.13;
		} */
		
	}
	else if(!Fly) {
		ay = MARIO_GRAVITY;
	}

	

	//if (state == RACOON_STATE_START_FLY) {
	//	if (GetTickCount64() - time_fly_max > 500) vy = -0.0f;
	//	
	//}
	if (waitDownPipe && GetTickCount64() - timedownupPipe >2500) {
		SetPositionPlayer(3048, 450);
	}

	if (abs(y - rangeEnterPipe) < 30) {
		ay = 0.0001;
		//LoadRenderDownPipe = true;
	}
	else rangeEnterPipe = -1;


	//UP_PIPE
	if (waitUpPipe && GetTickCount64() - time_wait_up_pipe > 2500) {
		SetPositionPlayer(2336, 372);
	}

	if (abs(y - rangeUpPipe) < 30) {
		//ay = 0;
		vy = -0.035f;

	}
	else rangeUpPipe = -1;
	//else ay = MARIO_GRAVITY;

	//if (StandOnPipe) ay = 0.0f;
		

	//if (Fly && isOnPlatform) { GetRenderFly = true; }
	LoadRenderDownPipe = false;
	FlyHigh = false;
	HitHeadPipe = false;
	StandOnPipe = false;
	EnterPipe = false;
	isOnPlatform = false;
	flyLowDown = false;
	waitDownPipe = false;
	waitUpPipe = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

//void CMario::CountDownTimeGame() {
//	if (clocktime > 4) {
//		if (GetTickCount64() - count_seconds > 10) {
//			clocktime -= 4;
//			//score += 50 * TIME_DOWN_END_SCENE;
//			count_seconds = GetTickCount64();
//		}
//	}
//	else {
//		//score += clock * 50;
//		clocktime = 0;
//		//isEndScene = true;
//		//isClockVeryFast = false;
//		//SetState(MARIO_STATE_CHANGE_WORLD_MAP);
//	}
//}

void CMario::CountDownTimes() 
{
	if (clocktime > 0) {
		if (GetTickCount64() - count_seconds > 1000) {
			clocktime --;
			count_seconds = GetTickCount64();
		}
	}
	else { 
		clocktime = 0; 
		SetState(MARIO_STATE_DIE);
	}

}

void CMario::CreatEffectMario(int effect) {

	
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	switch (effect)
	{
	case 9: // RACOON with GREEN_MUSHROOM
	{
		//CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		CGameEffects* up_1 = new CGameEffects(x, y - 4, 9);
		scene->AddObject(up_1);
		SetPoint(GetPoint() + 1000);
		break;
	}

	case 1:
	{
		CGameEffects* plusscore100 = new CGameEffects(x, y - 4, 1);
		scene->AddObject(plusscore100);
		SetPoint(GetPoint()+ 100);
		break;
	}
	case 2:
	{
		CGameEffects* plusscore200 = new CGameEffects(x, y - 4, 2);
		scene->AddObject(plusscore200);
		SetPoint(GetPoint() + 200);
		break;
	}
	case 5: {
		CGameEffects* plusscore1000 = new CGameEffects(x, y - 4, 5);
		scene->AddObject(plusscore1000);
		SetPoint(GetPoint() + 1000);
		break;

	}
		
	}

}

void CMario::CreateWhippingofTail() {

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	//CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (nx < 0) {
		CTailWhipping* tail1 = new CTailWhipping(x, y+5);

		if (state == MARIO_STATE_IDLE)
		
			scene->AddObject(tail1);
			//tail->SetState(WHIP_STATE_LEFT_MARIO);
		
		//CTailWhipping* tail5 = new CTailWhipping(x - 10, y + 5);
		CTailWhipping* tail2 = new CTailWhipping(x -5, y + 5);
		if (vx != 0)
			scene->AddObject(tail2);

		//else scene->AddObject(tail2);
		
			
		//ax = 0;

		

		//CGame::GetInstance()->GetCurrentScene()->CreateObjectAndReturn(OBJECT_TYPE_TAIL, x - BBOX_WIDTH / 2, y + MARIO_BIG_BBOX_HEIGHT / 2 - TAIL_BBOX_HEIGHT, -1);
		/*CGameObject* whipping = scene->CreateObjectAndReturn(OBJECT_TYPE_WHIPPING, x - BBOX_WIDTH, y, 0, 0);
		AddTail(whipping);
		tail->SetState(WHIP_STATE_LEFT_MARIO);*/
		//if(tail->GetDelete())
		//ResetTail();

	}
	else
	{
		CTailWhipping* tail3 = new CTailWhipping(x, y + 5);

		if (state == MARIO_STATE_IDLE)
		
			scene->AddObject(tail3);
			//tail->SetState(WHIP_STATE_RIGHT_MARIO);
		
	

		CTailWhipping* tail4 = new CTailWhipping(x +5, y + 5);
			if (vx != 0)
			scene->AddObject(tail4);
		//ax = 0;
		//CGame::GetInstance()->GetCurrentScene()->CreateObjectAndReturn(OBJECT_TYPE_TAIL, x + TAIL_BBOX_WIDTH / 2, y + MARIO_BIG_BBOX_HEIGHT / 2 - TAIL_BBOX_HEIGHT, 1);
		/*CGameObject* whipping = scene->CreateObjectAndReturn(OBJECT_TYPE_WHIPPING, x + BBOX_WIDTH, y, 0, 0);
		AddTail(whipping);
		tail->SetState(WHIP_STATE_RIGHT_MARIO);*/
		//if (tail->GetDelete())
		//ResetTail();
	}
}

void CMario::SetRacoonFlying() {

	
	//vy = 0.09f;
	//ay = 0.0f;
	//Fly = true;

	

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
		if (!Fly)
			vy = 0;
		else vy = -MARIO_GRAVITY;
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
		OnCollisionWithKoopa_Green(e);
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
	else if (dynamic_cast<CGreen_Plant*>(e->obj))
		OnCollisionWithGreenPlant(e);
	else if (dynamic_cast<CglassBrick*>(e->obj))
		OnCollisionWithGlassBrick(e);
	else if (dynamic_cast<CButtonP*>(e->obj))
		OnCollisionWithButtonP(e);
	else if (dynamic_cast<CPipePlantShoot*>(e->obj))
		OnCollisionWithPipe(e);
	else if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatform(e);
	else if (dynamic_cast<CCard*>(e->obj))
		OnCollisionWithCard(e);

	
}

void CMario::OnCollisionWithCard(LPCOLLISIONEVENT e) {
	CCard* card = dynamic_cast<CCard*>(e->obj);

	bool collect;
	//int id_card = this->id_card;

	SetState(MARIO_STATE_UNCONTROL);

	collect = card->GetCollect();

	if (e->ny > 0) {
		if (!collect) {
			card->SetState(STATE_CARD_IS_COLLECTED);

			if (card->GetCard() == 1) id_card = 1;
			else if (card->GetCard() == 2) id_card = 2;
			else if (card->GetCard() == 3) id_card = 3;

			//vx = 0.23f;
		}
	}
}

void CMario::OnCollisionWithPlatform(LPCOLLISIONEVENT e) {

	if (e->ny < 0) {
		//if (/*state == MARIO_STATE_DOWN_PIPE &&*/ //!EnterPipe /*&& GetTickCount64() - timedownupPipe > 1000*/) {
			//ay = 0.0015f;
			//if (vy == 0) {
				//if (abs(y - rangeEnterPipe) > 0)
					//SetPositionPlayer(3048, 450);
			//}

		//}
		waitDownPipe = true;
	}
	else if (e->ny > 0) {
		waitUpPipe = true;
	}
}

void CMario::OnCollisionWithPipe(LPCOLLISIONEVENT e) {
	CPipePlantShoot* pipe = dynamic_cast<CPipePlantShoot*>(e->obj);
	if (e->ny != 0) {
		if (e->ny<0) {
			if (pipe->GetModel() == MODEL_EMPTY_PORTAL_PIPE)
				StandOnPipe = true;
				//SetPositionPlayer(2336, 372);
		}
		else if (e->ny > 0)
		{
			if (pipe->GetModel() == 7)
				HitHeadPipe = true;
				//SetPositionPlayer(2336, 372);
		}
	}
	

}

void CMario::OnCollisionWithButtonP(LPCOLLISIONEVENT e) {
	CButtonP* P = dynamic_cast<CButtonP*>(e->obj);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	

	//e->obj->Delete();
	

	P->SetState(BUTTON_STATE_BE_COLLIDABLED);
	scene->GlassBrickChangeToCoin();
	//P->ChangeToCoin();
	//P->BrickToCoin();

}

void CMario::OnCollisionWithGlassBrick(LPCOLLISIONEVENT e) {
	CglassBrick* glBrick = dynamic_cast<CglassBrick*>(e->obj);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	if (!glBrick->GetEmpty() && !glBrick->GetUnBox() && glBrick->GetModel() == GLASS_BRICK_MODEL_CONTAIN_BUTTON && glBrick->GetState() != GLASS_BRICK_STATE_ISTOUCHED) {
		if (e->ny > 0) {


			glBrick->SetCollision(true);
			glBrick->SetState(GLASS_BRICK_STATE_ISTOUCHED);
			CButtonP* P = new CButtonP(glBrick->GetX(), glBrick->GetY() - 16);
			scene->AddObject(P);






			//glBrick->SetUnBox(true);
			//glBrick->SetEmpty(true);

		}
	}
		else 
	{
		if (glBrick->GetState() == GLASS_BRICK_STATE_CHANGE_TO_COIN)
		{
			coin++;
			SetPoint(5);
			e->obj->Delete();
		}
		}
	

	
		
	
			

			//glBrick->SetButtonP(NULL);

			//glBrick->CreateButtonP();
			


		
	
}

void CMario::OnCollisionWithGreenPlant(LPCOLLISIONEVENT e) {
	CGreen_Plant* green_plant = dynamic_cast<CGreen_Plant*>(e->obj);



	if (green_plant->StateActive()) {

		if (untouchable == 0) {
			if (green_plant->GetState() != PLANT_STATE_NOT_TOUCH) {
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

void CMario::OnCollisionWithKoopa_Green(LPCOLLISIONEVENT e)
{
	CGreen_Koopa* gkoopa = dynamic_cast<CGreen_Koopa*>(e->obj);

	ULONGLONG red_koopa_comback;
	red_koopa_comback = gkoopa->GetTimeComback();
	bool wasKicked;
	wasKicked = gkoopa->GETwasKicked();

	

	

	if (gkoopa->GetIsTurtleShell())
	{
		// K nhan A isHold = false , nhan phim A isHold = true; isHold = true -> holding;
		if (!gkoopa->GETwasKicked())
		{
			if (e->ny < 0) {
				if (gkoopa->GetIsKick()) {
					//SetState(MARIO_STATE_KICK);
					gkoopa->SetState(KOOPA_GREEN_STATE_ISKICKED);
					CreatEffectMario(1);
					SetPoint(1);
					//isHold = false;
				}
			}
			else
				if (e->nx != 0) {

					//koopared->SetTimeHold(GetTickCount64());
						//if(abs(x-koopared->GetX())<100)
					if (!isHold)
					{

						if (gkoopa->GetIsKick())
						{
							SetState(MARIO_STATE_KICK);
							gkoopa->SetState(KOOPA_GREEN_STATE_ISKICKED);
							CreatEffectMario(1);
							SetPoint(1);
							//CreatEffectMario(2);
							//(2);
							//isHold = false;
						}

					}
					else {

						Holding = true;
						gkoopa->SetState(KOOPA_GREEN_STATE_BE_HELD);


						//if (GetTickCount64() - koopared->GetTimeHold() > 3000)
							//koopared->SetState(KOOPA_RED_STATE_WALKING);


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

		//if (koopared->GetState() == KOOPA_RED_STATE_BE_HELD) {
			//if (GetTickCount64() - koopared->GetTimeHold() > 2000)
				//koopared->SetState(KOOPA_RED_STATE_WALKING);
		//}


	}
	else
	{
		if (gkoopa->GetIsJump()) {
			if (e->ny < 0) {
				if (gkoopa->GetState() == KOOPA_GREEN_STATE_JUMP)
				{
					gkoopa->SetJump(false);
					//untouchable = 1;
					gkoopa->SetState(KOOPA_GREEN_STATE_WALKING);
					gkoopa->SETay(0.9f);
					CreatEffectMario(1);
					SetPoint(1);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
			}
			else
			{
				if(untouchable==0)
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
		else
		{
			if (e->ny < 0)
			{
				if (gkoopa->GetState() != KOOPA_GREEN_STATE_ISTURTLESHELL && gkoopa->GetState() != KOOPA_GREEN_STATE_ISKICKED && gkoopa->GetState() != KOOPA_GREEN_STATE_TO_RETURN) //STATE_WALKING || //STATE_JUMP
				{
					gkoopa->SetCount_Start(GetTickCount64());
					gkoopa->SetState(KOOPA_GREEN_STATE_ISTURTLESHELL);
					gkoopa->SetY(gkoopa->GetY() - 6);
					//isHold = true;
					vy = -MARIO_JUMP_DEFLECT_SPEED;
					CreatEffectMario(2);
					SetPoint(2);
					DebugOut(L">>> KOOPA -> TURTLESHELL by MARIO -> KOOPA IN STATE WALKING >>> \n");
				}
			}
			else
			{// hit by green koopa (walking or turtleshell is kicked)
				if (untouchable == 0)
				{
					if (gkoopa->GetState() != KOOPA_GREEN_STATE_ISTURTLESHELL && gkoopa->GetState() != KOOPA_GREEN_STATE_TO_RETURN)
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
			CreatEffectMario(1);
			SetPoint(1);
			
		}
		else
		{
			pr_goomba->SetState(GOOMBA_RED_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
			CreatEffectMario(1);
			SetPoint(1);
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
					CreatEffectMario(1);
					SetPoint(1);
					//isHold = false;
				}
			}
			else
				if (e->nx != 0){

					//koopared->SetTimeHold(GetTickCount64());
						//if(abs(x-koopared->GetX())<100)
					if (!isHold)
					{
						
							if (koopared->GetIsKick())
							{
								SetState(MARIO_STATE_KICK);
								koopared->SetState(KOOPA_RED_STATE_ISKICKED);
								CreatEffectMario(1);
								SetPoint(1);
								//isHold = false;
							}
						
					}
					else{
						
						Holding = true;
						koopared->SetState(KOOPA_RED_STATE_BE_HELD);

						
						//if (GetTickCount64() - koopared->GetTimeHold() > 3000)
							//koopared->SetState(KOOPA_RED_STATE_WALKING);

						
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
		else
		{
			if (e->ny < 0) {
				koopared->SetState(KOOPA_RED_STATE_RESET_AFTER_KICKED);
				koopared->SetVx(0);
				koopared->SetVy(0);
				vy = -0.65f;

			}

			else {
			//koopared->SetX(+3);
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
			//else koopared->SetVx(koopared->GetVx());

		}

		/*if (koopared->GetState() == KOOPA_RED_STATE_BE_HELD)
		{
			if (!koopared->GETwasKicked() && !isHold)
				koopared->SetState(KOOPA_RED_STATE_ISKICKED);
		}*/

		//if (koopared->GetState() == KOOPA_RED_STATE_BE_HELD) {
			//if (GetTickCount64() - koopared->GetTimeHold() > 2000)
				//koopared->SetState(KOOPA_RED_STATE_WALKING);
		//}


	}
	else
	{
		if (e->ny < 0)
		{
			
			bool isCombackRedKoopa;
			isCombackRedKoopa = koopared->GetIsComback();

			if (koopared->GetState() != KOOPA_RED_STATE_ISTURTLESHELL && koopared->GetState() != KOOPA_RED_STATE_ISKICKED && koopared->GetState() != KOOPA_RED_STATE_TO_RETURN) //STATE_WALKING
			{
				koopared->SetCount_Start(GetTickCount64());
				koopared->SetState(KOOPA_RED_STATE_ISTURTLESHELL);
				CreatEffectMario(1);
				SetPoint(1);
				//isHold = true;
				vy = -MARIO_JUMP_SPEED_Y;
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
			//CreatEffectMario(1);
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
	SetPoint(5);
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

		if (questionBrick->GetModel() == QUESTION_BRICK_COIN)
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
			SetPoint(5);

		}
		
		else if(questionBrick->GetModel() == QUESTION_BRICK_NOT_COIN){

			if (level == MARIO_LEVEL_SMALL) 
			{
				CMushRoom* mushroom = new CMushRoom(xTemp, yTemp - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN), 1);
				scene->AddObject(mushroom);
				questionBrick->SetState(BRICK_Q_STATE_EMPTY);
				questionBrick->SetState(BRICK_Q_STATE_UP);
				questionBrick->SetIsEmpty(true);
				questionBrick->SetIsUnbox(true);
			}
			else if (level == MARIO_LEVEL_BIG) {
				CLeaf* leaf = new CLeaf(xTemp, yTemp - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN));
				scene->AddObject(leaf);
				leaf->SetState(LEAF_SUMMON_STATE);
				questionBrick->SetState(BRICK_Q_STATE_EMPTY);
				questionBrick->SetState(BRICK_Q_STATE_UP);
				questionBrick->SetIsEmpty(true);
				questionBrick->SetIsUnbox(true);

			}
			else if (level == MARIO_LEVEL_RACOON)
			{
				CMushRoom* mushroomgreen = new CMushRoom(xTemp, yTemp - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN), MODE_GREEN);
				scene->AddObject(mushroomgreen);
				questionBrick->SetState(BRICK_Q_STATE_EMPTY);
				questionBrick->SetState(BRICK_Q_STATE_UP);
				questionBrick->SetIsEmpty(true);
				questionBrick->SetIsUnbox(true);
			}
		}

		

		

		//if (questionBrick->GetModel() == QUESTION_BRICK_MUSHROOM)
		//{
		//		CMushRoom* mushroom = new CMushRoom(xTemp, yTemp - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN),1);

		//		//CbulletPlant* bullet = new CbulletPlant(xTemp + 50, yTemp);
		//		//CBrick* newbullet = new CBrick(367, 320);


		//		scene->AddObject(mushroom);
		//		//scene->AddObject(bullet);

		//		//scene->AddObject(newbullet);
		//		questionBrick->SetState(BRICK_Q_STATE_EMPTY);
		//		questionBrick->SetState(BRICK_Q_STATE_UP);
		//		questionBrick->SetIsEmpty(true);
		//		questionBrick->SetIsUnbox(true);

		//	
		//}
		//  
		//  else if (questionBrick->GetModel() == QUESTION_BRICK_LEAF)
		//{
		//	CLeaf* leaf = new CLeaf(xTemp, yTemp - (BRICK_Q_BBOX_HEIGHT - ADJUST_UP_DOWN));


		//	scene->AddObject(leaf);
		//	leaf->SetState(LEAF_SUMMON_STATE);
		//	questionBrick->SetState(BRICK_Q_STATE_EMPTY);
		//	questionBrick->SetState(BRICK_Q_STATE_UP);
		//	questionBrick->SetIsEmpty(true);
		//	questionBrick->SetIsUnbox(true);

		//}
		  /*else*/ 
	}
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	
		contact_door = true;
	

	/*if (Enter_map) {
		CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
	}*/
}


void CMario::OnCollisionWithMushRoom(LPCOLLISIONEVENT e)
{
	
	
	CMushRoom* mr = dynamic_cast<CMushRoom*>(e->obj);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (mr->GetMod() == 1) {
		if (!mr->IsDeleted())
		{
			if (level == MARIO_LEVEL_SMALL)
			{
				SetLevel(MARIO_LEVEL_BIG);
				CreatEffectMario(1);
				SetPoint(1);
				y = y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT);
			}
		}
		mr->Delete();
	}
	else if (mr->GetMod() == 2) //GREEN_MUSHROOM
	{
		if (!mr->IsDeleted())
		{
			//CreatEffectMario(5);
			if (level > MARIO_LEVEL_SMALL)
			{
				//effect = 9;
				CreatEffectMario(9);
				SetPoint(10);
				SetPoint(99);
				
				//SetEffect(9);
				
				//CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
				/*if (effect == 9) {
					CGameEffects* up_1 = new CGameEffects(x, y - 4, 9);
					scene->AddObject(up_1);
					SetCoin(GetCoin() + 1000);
				}*/
				//coin++;
				//SetLevel(MARIO_LEVEL_BIG);
				//y = y - (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT);
			}
		}
		mr->Delete();
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	if (level > MARIO_LEVEL_SMALL)
	{
		CreatEffectMario(5);
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

int CMario::GetAniIdRacoon() {

	int aniId = -1;

	if (!Fly) {

		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_RACOON_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_RACOON_JUMP_RUN_LEFT;
			}
			else {
				if (markFly < 6) {
					if (nx > 0) aniId = ID_ANI_RACOON_FLY_DOWN_RIGHT;
					else aniId = ID_ANI_RACOON_FLY_DOWN_LEFT;
				}
				else {
					if (nx > 0) aniId = ID_ANI_RACOON_FLY_RIGHT;
					else aniId = ID_ANI_RACOON_FLY_LEFT;
				}
			}
			/*else
			{
				if (!flyLowDown && vy < 0) {
					if (nx >= 0)
						aniId = ID_ANI_RACOON_JUMP_WALK_RIGHT;
					else
						aniId = ID_ANI_RACOON_JUMP_WALK_LEFT;
				}
			}*/
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
				else
					if (Holding) {
						if (vx != 0) {
							if (nx > 0) aniId = ID_ANI_RACOON_HOLD_GO_RIGHT;
							else aniId = ID_ANI_RACOON_HOLD_GO_LEFT;
						}
						else
						{
							if (nx > 0) aniId = ID_ANI_RACOON_HOLD_IDLE_RIGHT;
							else aniId = ID_ANI_RACOON_HOLD_IDLE_LEFT;
						}
					}
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
							else if (ax == MARIO_ACCEL_RUN_X) {
								if (markFly >= 7)
									aniId = ID_ANI_RACOON_RUNNING_RIGHT;
								else aniId = ID_ANI_RACOON_WALKING_RIGHT;
							}
							else if (ax == MARIO_ACCEL_WALK_X)
								aniId = ID_ANI_RACOON_WALKING_RIGHT;
						}
						else // vx < 0
						{
							if (ax > 0)
								aniId = ID_ANI_RACOON_BRACE_LEFT;
							else if (ax == -MARIO_ACCEL_RUN_X) {
								if (markFly >= 7)
									aniId = ID_ANI_RACOON_RUNNING_LEFT;
								else aniId = ID_ANI_RACOON_WALKING_LEFT;
							}
							else if (ax == -MARIO_ACCEL_WALK_X)
								aniId = ID_ANI_RACOON_WALKING_LEFT;
						}
	}
	else {
		if (!isOnPlatform)
		{
			if (nx > 0) aniId = ID_ANI_RACOON_FLY_RIGHT;
			else aniId = ID_ANI_RACOON_FLY_LEFT;


			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_RACOON_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_RACOON_JUMP_RUN_LEFT;
			}

			if (Holding)
			{
				if (nx > 0) aniId = ID_ANI_RACOON_FLY_HOLD_RIGHT;
				else aniId = ID_ANI_RACOON_FLY_HOLD_LEFT;
			}
		}
		else {
			if (nx < 0) {
				if (markFly >= 6) aniId = ID_ANI_RACOON_RUNNING_LEFT;
				else aniId = ID_ANI_RACOON_WALKING_LEFT;
			}

			else {
				if (markFly >= 6) aniId = ID_ANI_RACOON_RUNNING_RIGHT;
				else aniId = ID_ANI_RACOON_WALKING_RIGHT;
			}

		}

		/*else 
		{
			if (Holding) {
				if (nx > 0) aniId = ID_ANI_RACOON_HOLD_IDLE_RIGHT;
				else aniId = ID_ANI_RACOON_HOLD_IDLE_LEFT;
			} else 
				if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_RACOON_IDLE_RIGHT;
				else aniId = ID_ANI_RACOON_IDLE_LEFT;
			}

		}*/

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
	else if (state == MARIO_STATE_ATTACK)
	{
		if (nx > 0)
			aniId = ID_ANI_RACOON_ATTACK_RIGHT;
		else
			aniId = ID_ANI_RACOON_ATTACK_LEFT;
	}
	else if (state == MARIO_STATE_DOWN_PIPE or state == MARIO_STATE_UP_PIPE && level != 1)
	{
		if (level == 3)
			aniId = ID_ANI_DOWN_UP_PIPE;
		else if (level == 2)
			aniId = ID_ANI_BIG_MARIO_DOWN_UP;
	}
	
	/*else if (state == RACOON_STATE_FLY_DOWN_RELEASE)
	{
		if (nx >= 0)
			aniId = ID_ANI_RACOON_FLY_DOWN_RIGHT;
		else
			aniId = ID_ANI_RACOON_FLY_DOWN_LEFT;
	}*/

	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
	
	DebugOutTitle(L"MARKFLy: %d", markFly);
	//DebugOutTitle(L"Toa do x =: %d",x );
}

void CMario::SetState(int state)
{
	
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	else if (this->state == MARIO_STATE_ATTACK && (GetTickCount64() - timing < 250)) return;

	else if ((this->state == MARIO_STATE_DOWN_PIPE) && (GetTickCount64() - timedownupPipe < 1250)) return;

	else if ((this->state == MARIO_STATE_UP_PIPE) && (GetTickCount64() - time_wait_up_pipe < 1250)) return;

	//else if ((this->state == RACOON_STATE_START_FLY) && (GetTickCount64() - time_fly_max < 2000)) return;

	//else if (this->state == RACOON_STATE_FLY_DOWN_RELEASE && (GetTickCount64() - timing < 200)) return;

	//else if (this->state == RACOON_STATE_FLY) return;

	//else if (state == RACOON_STATE_START_FLY && GetTickCount64() - time_fly_max > 850) return;
	

	if (Kicking && GetTickCount64() - timing > 200)
	{
		Kicking = false;
	}

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (Fly) break;
		if (isSitting) break;
		if (level != 3) {
			maxVx = MARIO_RUNNING_SPEED;
			ax = MARIO_ACCEL_RUN_X;
			nx = 1;
		}
		else {
			//if (markFly >= 7 && !isOnPlatform && state != MARIO_STATE_ATTACK) SetState(RACOON_STATE_START_FLY);
			Run = true;
			maxVx = MARIO_RUNNING_SPEED + markFly*0.002;
			ax = MARIO_ACCEL_RUN_X;
			nx = 1;
		}
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (Fly) break;
		if (isSitting) break;
		if (level != 3) {
			maxVx = -MARIO_RUNNING_SPEED;
			ax = -MARIO_ACCEL_RUN_X;
			nx = -1;
		}
		else {
			//if (markFly >= 7 && !isOnPlatform && state!= MARIO_STATE_ATTACK) SetState(RACOON_STATE_START_FLY);
			Run = true;
			maxVx = -MARIO_RUNNING_SPEED - markFly*0.002;
			ax = -MARIO_ACCEL_RUN_X;
			nx = -1;
		}
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		Run = false;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		Run = false;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		//if (Fly) break;
		if (isSitting) break;
		Run = false;
		if (isOnPlatform)
		{
			if (level != 3) {
				//Fly = false;
				if (abs(this->vx) == MARIO_RUNNING_SPEED)
					vy = -MARIO_JUMP_RUN_SPEED_Y;
				else
					vy = -MARIO_JUMP_SPEED_Y;
			}
			else {
				if (abs(this->vx) == MARIO_RUNNING_SPEED)
					vy = -0.6;
				else
					vy = -0.55;
			}
		}
		else if(level == 3) {
			if (GetTickCount64() - time_maintain_fly_low > 300) break;
			if (vy > 0)
			{
				ay = 0.0f;
				vy = 0.02f;
			}
		}
		break;

	case RACOON_STATE_FLY:
		if (level != 3) break;
		//if (!isOnPlatform)
		//if (isOnPlatform) Fly = false;
		//else 
		Fly = true;
		//else Fly = false;
		//Run = false;
		ay = 0;
		time_maintain_fly_high = GetTickCount64();
		vy = -0.17f;
		//time_relase_fly_high = GetTickCount64();
		//isOnPlatform = false;
		
		
		//y += 6;
		//ay = 0.00001f;
		//vy = -0.3f;
		break;

	case RACOON_STATE_END_FLY:
		//if (level != 3) break;
		ay = MARIO_GRAVITY;
		Fly = false;
		break;

	case RACOON_STATE_START_FLY:
		//if (level != 3) break;
		rangFlyStart = y;
		if(isOnPlatform) vy = -0.55f;
		vx = nx * 0.08f;
		//vy = 0;
		//if (isOnPlatform)
			//Fly = false;
		//else 
		Fly = true;
		//Run = false;
		time_fly_max = GetTickCount64();
		ay = -0.0001f;
		break;

	case RACOON_STATE_RELEASE_FLY_HIGH:
		//Run = false;
		ay = 0.00035f;
		break;

	case MARIO_STATE_RELEASE_JUMP:

		if (level == 3 && !isOnPlatform) flyLowDown = true;
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		
		break;

	case RACOON_STATE_FLY_DOWN_RELEASE:
		if (level != 3) return;
		else flyLowDown = true;
		
		//if(!isOnPlatform)
		//ay = 0.00002f;
		//ay = 0;
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
		//Run = false;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		//Holding = true;
		break;

	case MARIO_STATE_HOLDING_LEFT:
		if (isSitting) break;
		//Run = false;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		//Holding = true;
		break;

	case MARIO_STATE_ATTACK:
		timing = GetTickCount64();
		if (level != MARIO_LEVEL_RACOON || isSitting) return;
		CreateWhippingofTail();
		//if (nx > 0)
			//ax = -0.0003;
		//else ax = 0.0003;
		//ax = 0;
		//if (abs(vx) == maxVx) vx = maxVx;
		//nx = 0;
		//vx = 0;
		//nx = 0;
		ax = 0;
		break;

	case MARIO_STATE_ATTACK_LEFT:
		if (level != MARIO_LEVEL_RACOON || isSitting) return;
		maxVx = -0.05;
		ax = -0.00015;
		
		//vx = 0;
		nx = -1;
		break;
	case MARIO_STATE_ATTACK_RIGHT:
		if (level != MARIO_LEVEL_RACOON || isSitting) return;
		maxVx = 0.05;
		ax = 0.00015;
		//vx = 0;
		nx = 1;
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DOWN_PIPE:
		if (level == 1) break;
		EnterPipe = true;
		timedownupPipe = GetTickCount64();
		vx = 0;
		ay = 0;
		rangeEnterPipe = y;
		vy = 0.00002f;
		y = y +1;
		break;

	case MARIO_STATE_UP_PIPE:
		if (level == 1) break;
		//SetPositionPlayer(2336, 372);
		vx = 0;
		ay = 0;
		//rangeEnterPipe = y;
		rangeUpPipe = y;
		time_wait_up_pipe = GetTickCount64();
		vy = -0.00002f;
		y = y - 4;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;

	case MARIO_STATE_UNCONTROL:
		time_uncontrol = GetTickCount64();
		goEndMap = true;
		vx = 0;
		vy = 0;
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

void CMario::SetPoint(int point)
{
	switch (point)
	{
	case 1:  //+100
	{
		score = score + 100;
		break;
	}
	case 20:
	{
		score += 20;
		break;
	}
	case 2: //+200
	{
		score += 200;
		break;
	}
	case 10://+1000
	{
		score = score + 1000;
		break;
	}


	case 5: // +50
	{
		score = score + 50;
		break;
	}

	case 99:
	{
		//if (state != MARIO_STATE_DIE)
			UP_M += 1;
		//else UP_M -= 1;
		break;
	}

	}// ket thuc switch;

	
}

