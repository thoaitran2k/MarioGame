#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:

		if (mario->GetLevel() == 3)
		{
			if(!mario->GetFly())
			mario->SetState(RACOON_STATE_FLY);
		}
		//if (mario->GetLevel() != 3) {
		else mario->SetState(MARIO_STATE_JUMP);
		//}
		//else {
		//	//if(mario->GetState() != MARIO_STATE_RELEASE_JUMP)
		//	mario->SetState(MARIO_STATE_JUMP);

		//	if (mario->GetState() != MARIO_STATE_RELEASE_JUMP)
		//	{
		//		mario->SetState(RACOON_STATE_FLY_DOWN_RELEASE);
		//		
		//	}
			//mario->SetVy(-0.3f);
				//mario->SetState(RACOON_STATE_FLY_DOWN_RELEASE);
				//mario->SetVy(-0.3f);		
		//}
			//if (mario->GetState() == MARIO_STATE_JUMP)
			//{
				//mario->SetY(mario->GetY() - 2);
				//mario->SetVy(0);
			//}
			//mario->SetState(MARIO_STATE_JUMP);
			//mario->SetVy(-0.03f);
		//}

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
	case DIK_A:
		//if (mario->GetIsHolding()) mario->SetHolding(false);
		//if(mario->GetIsHolding()) mario->SetHolding(false);
		//if (koopa_red->GetIsTurtleShell())
		//{
			
				//mario->SetIsHold(true);

		//}

		//if (mario->GetIsHold())
		mario->SetIsHold(true);

		mario->SetState(MARIO_STATE_ATTACK);

		
		//else mario->SetHolding(false);
		break;

	case DIK_D:
		
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
	case DIK_S:

		if (mario->GetLevel() != 3) {
			mario->SetState(MARIO_STATE_RELEASE_JUMP);
		}
		else {
			
				mario->SetState(RACOON_STATE_FLY_DOWN_RELEASE);
			//mario->SetState(RACOON_STATE_FLY_DOWN_RELEASE);
			//mario->SetVy(-0.2f);
		}
		
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

	//if (game->IsKeyDown(DIK_A)) mario->SetState(MARIO_STATE_HOLDING);
	if (!mario->GetIsHolding() || mario->GetFly() )
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{


			if (game->IsKeyDown(DIK_A))

				mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			else
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (game->IsKeyDown(DIK_A))
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
			
			if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_ATTACK_RIGHT);
			else
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT)) {
			if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_ATTACK_LEFT);
				else
				mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_IDLE);
	}

	else 
	{
		if (game->IsKeyDown(DIK_RIGHT))
		{


			if (game->IsKeyDown(DIK_A))

				mario->SetState(MARIO_STATE_HOLDING_RIGHT);
			else
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else if (game->IsKeyDown(DIK_LEFT))
		{
			if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_HOLDING_LEFT);
			else

				mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_IDLE);
	}
}