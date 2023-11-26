#include "PlantShootRed.h"
#include "Game.h"
#include "PlayScene.h"
#include "GameObject.h"
#include "bullet_plant.h"



CPlantShootRed::CPlantShootRed(float x, float y):CGameObject(x, y)
{
	DebugOut(L">>> BAN DAU CAY DI LEN >>> \n");
	startY = y;
	loacationX = x;
	minY = startY - PLANT_BBOX_HEIGHT;
	SetState(PLANT_STATE_UP);
	IsActive = true;
	
	
}

void CPlantShootRed::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if ((distanceMario_PlantEnemies() < 50))
	{
		DebugOut(L">>> CAY O DUOI CONG MARIO KHONG BI DUNG >>>endl>>CAY KHONG TROI LEN VI MARIO DUNG KE BEN>>> \n");
		return;
	}
	else {

		l = x - PLANT_BBOX_WIDTH / 2;
		t = y - PLANT_BBOX_HEIGHT / 2;
		r = l + PLANT_BBOX_WIDTH;
		b = t + PLANT_BBOX_HEIGHT;
	}

}

void CPlantShootRed::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (isUpping) /*&& (distanceMario_PlantEnemies() > 50) && (distanceMario_PlantEnemies() < DISTANCE_PLANT_ENEMIS_SHOW_UP))*/ {
		if (y >minY)
		{
			vy = -SPEED;
		}
		else {
			
			vy = 0;
			y = minY;
			time_shoot = GetTickCount64();
			if (GetTickCount64() - time_out_pipe > TIME_OUT_PIPE)
			{
				DebugOut(L">>> CAY SE DI XUONG >>> \n");
				
				SetState(PLANT_STATE_DOWN);

			}
			else {
					if (!isShoot) {
						
						//if (GetTickCount64() - time_shoot < TIME_CONDITION_TO_SHOOT) 
						//{

								isShoot = true;
								bool theoX = true, theoY = true;
							


								DebugOut(L">>> SINH RA VIEN DAN>>> \n");

								if (mario->GetX() < x && mario->GetY() < y)
								{
									CbulletPlant* bullet = new CbulletPlant(x, y, !theoY, !theoX);
									scene->AddObject(bullet);
								}
								else
									if (mario->GetX() < x && mario->GetY() > y)
									{
										CbulletPlant* bullet = new CbulletPlant(x + 2, y - PLANT_BBOX_HEIGHT / 2, theoY, !theoX);
										scene->AddObject(bullet);
									}

								if (mario->GetX() > x && mario->GetY() > y)
								{
									CbulletPlant* bullet = new CbulletPlant(x, y, theoY, theoX);
									scene->AddObject(bullet);
								}
								else
									if (mario->GetX() > x && mario->GetY() < y)
									{
										CbulletPlant* bullet = new CbulletPlant(x, y, !theoY, theoX);
										scene->AddObject(bullet);
									}
							
						
						//}
					}
			}
		}
	}
	else if (isDowning) {
		
		if(y < startY +2)
		{
			vy = SPEED;
		}
		else {
			vy = 0;
			y = startY + 2;
			if (GetTickCount64() - time_down_pipe > TIME_IN_PIPE) {
				
				if ((distanceMario_PlantEnemies() > 50))
				{
					DebugOut(L">>> CAY SE TROI LEN >>> \n");
					SetState(PLANT_STATE_UP);
				}
				
				//else IsActive = true;
			}
		}
	}
	else {
		if (y < startY + 2 )
		{
			vy = SPEED;
		}
		else {
			vy = 0;
			y = startY + 2;
			if (GetTickCount64() - time_down_pipe > TIME_IN_PIPE) {
				SetState(PLANT_STATE_UP);
			}


		}
	}
	//TEST CAY KHONG VA CHAM VOI MARIO
		/*if (state != PLANT_STATE_UP && state != PLANT_STATE_DOWN)
		{
			DebugOut(L">>> CAY KHONG LAM MARIO CHET KHI O DUOI ONG >>> \n");
			SetState(PLANT_STATE_NOT_TOUNCH);
		}*/
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPlantShootRed::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

float CPlantShootRed::distanceMario_PlantEnemies() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	return abs(mario->GetX() - x);

}

int CPlantShootRed::LeftORightMario() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetX() < GetX()) //Mario ben trai cai cay
	{
		return 1;
	}
	else return - 1;
}

int CPlantShootRed::TopOrBottomYMario()
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetY() < GetY()) //Mario o phia tren cai cay 
	{
		return 1;
	}
	else return -1;
}

void CPlantShootRed::Render()
{

	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	
		if (LeftORightMario() == 1 && TopOrBottomYMario() == -1)
			if (!isShoot) aniId = ID_ANI_PLANT_LEFT_UNDER_NOT_SHOOT;
			else 
				aniId = ID_ANI_PLANT_LEFT_UNDER_SHOOT;
		else if (LeftORightMario() == 1 && TopOrBottomYMario() == 1)
			if (!isShoot) aniId = ID_ANI_PLANT_LEFT_TOP_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_LEFT_TOP_SHOOT;
		else if (LeftORightMario() == -1 && TopOrBottomYMario() == 1)
			if (!isShoot) aniId = ID_ANI_PLANT_RIGHT_TOP_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_RIGHT_TOP_SHOOT;
		else  {
			if (!isShoot) aniId = ID_ANI_PLANT_RIGHT_UNDER_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_RIGHT_UNDER_SHOOT;
			 }
		
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CPlantShootRed::SetState(int state)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (state)
	{
	case PLANT_STATE_UP:

		if (distanceMario_PlantEnemies() < DISTANCE_PLANT_ENEMIS_SHOW_UP)
		{
			isUpping = true;

		}
		else
		{
			isUpping = false;
		}
		isDowning = false;
		isShoot = false;
		time_out_pipe = GetTickCount64();
		time_down_pipe = 0;
		break;

	case PLANT_STATE_DOWN:
		isShoot = false;
		isUpping = false;
		isDowning = true;
		time_down_pipe = GetTickCount64();
		time_out_pipe = 0;
		break;
	case PLANT_STATE_NOT_TOUNCH:
		isDeleted = true;
		break;
	}
	CGameObject::SetState(state);

}



