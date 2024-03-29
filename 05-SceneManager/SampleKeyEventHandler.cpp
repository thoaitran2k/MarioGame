#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario_WorldMap.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	

	switch (KeyCode)
	{
	if (mario->GetGoEndMap()) break;
	case DIK_DOWN:
		if (!mario->GetIsStandOnPipi())
			mario->SetState(MARIO_STATE_SIT);
		else { 
			if(mario->GetLevel() > 1)
			mario->SetState(MARIO_STATE_DOWN_PIPE);
			//mario->SetEnterPipe(true);
			//mario->SetY(mario->GetY() + 1); 
			//mario->SetVy(0.0005f);
		}
		break;

	/*case DIK_UP:
		if (!mario->GetIsStandOnPipi()) return;
		else {
			mario->SetState(MARIO_STATE_UP_PIPE);
		}
		break;*/
	case DIK_S:

		//if (mario->GetIsOnPlatform()) {
		//	mario->SetState(MARIO_STATE_JUMP);
		//}
		//else{
		//	if (mario->GetLevel() == 3)
		//	{
		//		mario->SetState(RACOON_STATE_FLY);
		//		//mario->SetTimeFlyHigh(GetTickCount64());
		//	}
		//}

		if (mario->GetContactDoor())
			//mario->SetEnterMap(true);
			CGame::GetInstance()->InitiateSwitchScene(5);
		else {


			if (mario->GetMarkFly () >= 6 && mario->GetLevel() == 3) {

				if(!mario->GetIsOnPlatform())
				mario->SetState(RACOON_STATE_FLY);
				else {
					if (mario->GetState() != RACOON_STATE_FLY)
						mario->SetState(RACOON_STATE_START_FLY);
					//else mario->SetState(RACOON_STATE_END_FLY);
					
				}

				//mario->SetVy(-0.312f);
				//else mario->SetVy(0);
			}
			else {
				mario->SetState(MARIO_STATE_JUMP);
				//mario->SetTimeFlyHigh(GetTickCount64());
				//mario->SetState(RACOON_STATE_FLY_DOWN_RELEASE);
			}
		}

		//if (mario->GetState() == MARIO_STATE_RELEASE_JUMP)
		

		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_4:
		mario->SetPositionPlayer(100, 320);//Pos Start Map 1
		break;
	case DIK_7:
		mario->SetPositionPlayer(3048, 540); // XUONG MAP AN
		break;
	case DIK_8:
		mario->SetPositionPlayer(2273, 90); // XUONG MAP AN
		break;
	case DIK_9:
		mario->SetPositionPlayer(1420, 130);// XUONG MAP AN
		break;
	case DIK_5:
		mario->SetPositionPlayer(800, 380);
		break;
	case DIK_6:
		mario->SetPositionPlayer(150, 380);
		break;
	case DIK_A:
		//if (mario->GetIsHolding()) mario->SetHolding(false);
		//if(mario->GetIsHolding()) mario->SetHolding(false);
		//if (koopa_red->GetIsTurtleShell())
		//{
			
				//mario->SetIsHold(true);

		//}

		//if (mario->GetIsHold())
		mario->SetIsHold(true);

		//if(mario->GetLevel())
		mario->SetState(MARIO_STATE_ATTACK);


		
		//else mario->SetHolding(false);
		break;

	case DIK_D:
		
		//if (mario->GetGoEndMap()) mario->SetUnControl(false);
		
		DebugOut(L">>> NHAN DDDDDDDDDDDDDDDDDD >>> \n");
		break;
		//else mario->SetHolding(false);
		//break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	if (mario->GetGoEndMap()) break;
	case DIK_S:

		//if (mario->GetLevel() != 3) {
			/*mario->SetState(MARIO_STATE_RELEASE_JUMP);

			if (mario->GetState() == MARIO_STATE_RELEASE_JUMP) {

				if (mario->GetVx() != 0) {
					if (mario->GetNx() > 0) mario->SetVx(0.1f);
					else  mario->SetVx(-0.1f);
				}
				else mario->SetVx(0);
			}*/

			//if (mario->GetMarkFly() <= 6) break;
			mario->SetState(MARIO_STATE_RELEASE_JUMP);

			
			/*mario->SETay(-0.02f);
			if (mario->GetLevel() == 3) {

				if (mario->GetState() == RACOON_STATE_FLY_DOWN_RELEASE)
				{
					mario->SetVy(-0.0f);
					if (mario->GetVx() != 0) {

						if (mario->GetNx() > 0) mario->SetVx(0.03f);
						else mario->SetVx(-0.03f);
					}
					else if(mario->GetVx() == 0) mario->SetVx(0);
				}
			}

			else return;*/

		//}
		//else {
			//if (mario->GetFly()) {
				//	
				//mario->SetState(RACOON_STATE_FLY_DOWN_RELEASE);
			//	mario->SETay(0);
				//mario->SetVy(-0.12);
			//}
		//	//mario->SetState(RACOON_STATE_FLY_DOWN_RELEASE);
		//	//mario->SetVy(-0.2f);
		//}
		
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		//mario->SetHolding(true);
		if (mario->GetIsHolding()) mario->SetHolding(false);

		/*if(mario->GetIsHold())*/  mario->SetIsHold(false);
		//if (mario->GetState() == MARIO_STATE_ATTACK) mario->SetState(MARIO_STATE_IDLE);
		//mario->ResetTail();
		//mario->SetHolding(true);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->GetGoEndMap()) return;

	if (game->IsKeyDown(DIK_UP))
	{
		if (mario->GetUpPipe())
		{
			if(game->IsKeyDown(DIK_S))
			
				mario->SetState(MARIO_STATE_UP_PIPE);
			
		}
			
	}

	/*if (mario->GetMarkFly() == 7)
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{
			if (!game->IsKeyDown(DIK_S))
				mario->SetFlyTF(false);
		}
	}*/
	//if (game->IsKeyDown(DIK_A)) mario->SetState(MARIO_STATE_HOLDING);
	if (!mario->GetIsHolding())
	{
		

		if (game->IsKeyDown(DIK_RIGHT))
		{


			if (game->IsKeyDown(DIK_A) && !mario->GetFly())
				//if (!mario->GetFly()) {
					mario->SetState(MARIO_STATE_RUNNING_RIGHT);
				//}
				else mario->SetState(MARIO_STATE_WALKING_RIGHT);
			/*else {
					mario->SetState(MARIO_STATE_WALKING_RIGHT);
	
			}*/
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (game->IsKeyDown(DIK_A) && !mario->GetFly())
				mario->SetState(MARIO_STATE_RUNNING_LEFT);
			else

				mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_IDLE);
	}
	else if (mario->GetState() == MARIO_STATE_ATTACK)
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{
			
			//if (game->IsKeyDown(DIK_A))
			//mario->SetState(MARIO_STATE_ATTACK_RIGHT);
			//else
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT)) {
			//if (game->IsKeyDown(DIK_A))
			//mario->SetState(MARIO_STATE_ATTACK_LEFT);
				//else
				mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_IDLE);
	}
	else 
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{


			if (game->IsKeyDown(DIK_A)) {

				mario->SetState(MARIO_STATE_HOLDING_RIGHT);
				mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			}
			else
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (game->IsKeyDown(DIK_A)) {
				mario->SetState(MARIO_STATE_HOLDING_LEFT);
				mario->SetState(MARIO_STATE_RUNNING_LEFT);
			}
			else

				mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_IDLE);
	}
}