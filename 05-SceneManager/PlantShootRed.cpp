#include "PlantShootRed.h"
#include "Game.h"
#include "PlayScene.h"
#include "GameObject.h"
#include "bullet_plant.h"



CPlantShootRed::CPlantShootRed(float x, float y):CGameObject(x, y)
{
	startY = y;
	loacationX = x;
	minY = startY - PLANT_BBOX_HEIGHT;
	SetState(PLANT_STATE_UP);
	
}

void CPlantShootRed::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PLANT_BBOX_WIDTH / 2;
	t = y - PLANT_BBOX_HEIGHT / 2 ;
	r = l + PLANT_BBOX_WIDTH;
	b = t + PLANT_BBOX_HEIGHT;
	
}

void CPlantShootRed::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (isUpping) {
		if (y >minY)
		{
			vy = -SPEED_GROW_UP;
		}
		else {
			time_shoot = GetTickCount64();
			vy = 0;
			y = minY;
			if (GetTickCount64() - time_out_pipe > TIME_OUT_PIPE)
			{
				
				SetState(PLANT_STATE_DOWN);
			}
			else {
					if (!isShoot) {
						if (GetTickCount64() - time_shoot < TIME_SHOOT) {
							isShoot = true;
							bool theoX = true, theoY = true;
							//CbulletPlant* bullet = new CbulletPlant(x - 5, y,theoY , theoX);
							//scene->AddObject(bullet);

						/*	if (PosWithXMario() == 1)
							{
								theoX = true;
								
							}
							if (PosWithYMario() == 1)
							{
								
								theoY = true;
							}*/
							DebugOut(L">>> SINH RA VIEN DAN>>> \n");

							if (mario->GetX() <x && mario->GetY() < y)
							{
								CbulletPlant* bullet = new CbulletPlant(x,y-5, !theoY, !theoX);
									scene->AddObject(bullet);
							}
							else 
								if(mario->GetX() < x && mario->GetY() > y)
							{
								CbulletPlant* bullet = new CbulletPlant(x, y - 5, theoY, !theoX);
								scene->AddObject(bullet);
							}
							
							if (mario->GetX() > x && mario->GetY() > y)
							{
								CbulletPlant* bullet = new CbulletPlant(x, y - 5, theoY, theoX);
								scene->AddObject(bullet);
							}
							else
								if(mario->GetX() > x && mario->GetY() < y)
							{
								CbulletPlant* bullet = new CbulletPlant(x, y - 5, !theoY, theoX);
								scene->AddObject(bullet);
							}

							/*if (mario->GetX() > x && mario->GetY() < y)
							{
								
								CbulletPlant* bullet = new CbulletPlant(x, y-5, theoY, theoX);
								scene->AddObject(bullet);
							}
							if (mario->GetX() < x && mario->GetY() > y)
							{
								CbulletPlant* bullet = new CbulletPlant(x, y - 5, theoY, theoX);
								scene->AddObject(bullet);
							}
							if(mario->GetX() > x && mario->GetY() < y)
							{

								CbulletPlant* bullet = new CbulletPlant(x, y - 5, theoY, theoX);
								scene->AddObject(bullet);
							}*/
							
							
							
							//if (Phai && Duoi)
							//{
								
							//}
							
							/*if (isOnTop && isLeft)
							{
								Cbullet_plant* bullet = new Cbullet_plant(x, y, isLeft, !isOnTop);
								scene->AddObject(bullet);
							}
							if (!isOnTop && isLeft)
							{
								Cbullet_plant* bullet = new Cbullet_plant(x, y, isLeft, !isOnTop);
								scene->AddObject(bullet);
							}
							if (isOnTop && !isLeft)
							{
								Cbullet_plant* bullet = new Cbullet_plant(x, y, isLeft, !isOnTop);
								scene->AddObject(bullet);
							}
							if (!isOnTop && !isLeft)
							{
								Cbullet_plant* bullet = new Cbullet_plant(x, y, isLeft, !isOnTop);
								scene->AddObject(bullet);
							}
							*/
						}
					}
			}
		}
	}
	else if (isDowning) {
		
		if(y < startY +2) //- DISTANCE_PIPE_LONG_SHORT)
		{
			vy = SPEED_GROW_UP;
		}
		else {
			vy = 0;
			y = startY + 2;
			
			if (GetTickCount64() - time_down_pipe > TIME_DOWN_PIPE) {
				SetState(PLANT_STATE_UP);
				//CbulletPlant* bullet = new CbulletPlant(x, y-50);
				//scene->AddObject(bullet);
			}
		}
	}
	else {
		if (y < startY + 2 )
		{
			vy = SPEED_GROW_UP;
		}
		else {
			vy = 0;
			y = startY + 2;
			if (GetTickCount64() - time_down_pipe > TIME_DOWN_PIPE) {
				SetState(PLANT_STATE_UP);
			}


		}
	}
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
			else aniId = ID_ANI_PLANT_LEFT_UNDER_SHOOT;
		else if (LeftORightMario() == 1 && TopOrBottomYMario() == 1)
			if (!isShoot) aniId = ID_ANI_PLANT_LEFT_TOP_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_LEFT_TOP_SHOOT;
		else if (LeftORightMario() == -1 && TopOrBottomYMario() == 1)
			if (!isShoot) aniId = ID_ANI_PLANT_RIGHT_TOP_NOT_SHOOT;
			else aniId = ID_ANI_PLANT_RIGHT_TOP_SHOOT;
		else {
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
		else isUpping = false;
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
	}
	CGameObject::SetState(state);

}



