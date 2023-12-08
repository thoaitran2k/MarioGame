#include "Green_Plant.h"
#include "Game.h"
#include "PlayScene.h"
#include "GameObject.h"
#include "bullet_plant.h"



CGreen_Plant::CGreen_Plant(float x, float y, int type) :CGameObject(x, y)
{

	startY = y;
	loacationX = x;
	minY = startY - PLANT_BBOX_HEIGHT;
	SetState(PLANT_STATE_UP);
	IsActive = true;
	this->type = type;


}

void CGreen_Plant::CreateBullet() {

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	CGameObject* bullet = scene->CreateObjectAndReturn(OBJECT_TYPE_FIRE_BULLET_OF_PLANT, x, y - 4, BULLET_SPEED_X, BULLET_SPEED_Y);
	create_bullet(bullet);

	//DebugOut(L">>> check tao ra vien dan >>> \n");


}

void CGreen_Plant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	/*if ((distanceMario_PlantEnemies() < 50))
	{
		DebugOut(L">>> CAY O DUOI CONG MARIO KHONG BI DUNG >>>endl>>CAY KHONG TROI LEN VI MARIO DUNG KE BEN>>> \n");
		return;
	}*/
	if (!IsActive)
	{
		DebugOut(L">>> die or not die >>> \n");
		return;


	}
	else {

		l = x - PLANT_BBOX_WIDTH / 2;
		t = y - PLANT_BBOX_HEIGHT / 3;
		r = l + PLANT_BBOX_WIDTH;
		b = t + PLANT_BBOX_HEIGHT;
	}

}

void CGreen_Plant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();




	if (abs(mario->GetX() - x) < 25)
	{
		if (y == startY) {
			IsActive = false;
			time_wait_plant_return = GetTickCount64();
		}


	}
	else
		IsActive = true;

	if (IsActive && GetTickCount64() - time_wait_plant_return > 2000) {
		//DebugOut(L">>> CAY DANG HOAT DONG >>> \n");
		if (isUpping) {
			if (y > minY)
			{
				vy = -SPEED;
			}
			else {

				vy = 0;
				y = minY;
				time_shoot = GetTickCount64();
				if (GetTickCount64() - time_out_pipe > TIME_OUT_PIPE)
				{


					//DebugOut(L">>> CAY LAN XUONG lan thu n >>> \n");

					SetState(PLANT_STATE_DOWN);

				}
				else {
					if (!isShoot && type == PLANT_TYPE_SHOOT) {



						isShoot = true;
						//bool theoX = true, theoY = true;


						CreateBullet();

						/*if (mario->GetX() < x)
						{
							CreateBullet();
							bullet->SetVx(-BULLET_SPEED_X);

						}
						else
						{
							CreateBullet();
							bullet->SetVx(BULLET_SPEED_X);

						}


						if (mario->GetY() < y)
						{
							CreateBullet();
							bullet->SetVy(BULLET_SPEED_Y);

						}
						else
						{
							CreateBullet();
							bullet->SetVy(-BULLET_SPEED_Y);

						}*/



						//DebugOut(L">>> SINH RA VIEN DAN>>> \n");

						//if (mario->GetX() < x && mario->GetY() < y)
						//{
						//	CreateBullet();
						//	bullet->SetVx(-BULLET_SPEED_X);
						//	bullet->SetVy(-BULLET_SPEED_Y);

						//	//CbulletPlant* bullet = new CbulletPlant(x, y, !theoY, !theoX);
						//	//scene->AddObject(bullet);
						//	
						//}
						//else if (mario->GetX() < x && mario->GetY() > y)
						//	{
						//		CreateBullet();
						//		bullet->SetVx(-BULLET_SPEED_X);
						//		bullet->SetVy(BULLET_SPEED_Y);

						//		//CbulletPlant* bullet = new CbulletPlant(x + 2, y - PLANT_BBOX_HEIGHT / 2, theoY, !theoX);
						//		//scene->AddObject(bullet);
						//	}


						//if (mario->GetX() > x && mario->GetY() > y)
						//{
						//	CreateBullet();
						//	bullet->SetVx(BULLET_SPEED_X);
						//	bullet->SetVy(BULLET_SPEED_Y);

						//	//CbulletPlant* bullet = new CbulletPlant(x, y, !theoY, !theoX);
						//	//scene->AddObject(bullet);

						//}
						//else if (mario->GetX() > x && mario->GetY() < y)
						//{
						//	CreateBullet();
						//	bullet->SetVx(-BULLET_SPEED_X);
						//	bullet->SetVy(BULLET_SPEED_Y);

						//	//CbulletPlant* bullet = new CbulletPlant(x + 2, y - PLANT_BBOX_HEIGHT / 2, theoY, !theoX);
						//	//scene->AddObject(bullet);
						//}


						//if (mario->GetX() < x && mario->GetY() < y)
						//{
						//	CreateBullet();
						//	bullet->SetVx(-BULLET_SPEED_X);
						//	bullet->SetVy(BULLET_SPEED_Y);
						//	//CbulletPlant* bullet = new CbulletPlant(x, y, theoY, theoX);
						//	//scene->AddObject(bullet);
						//}
						//else if(mario->GetX() < x && mario->GetY() < y)
						//	{
						//		CreateBullet();
						//		bullet->SetVx(BULLET_SPEED_X);
						//		bullet->SetVy(-BULLET_SPEED_Y);
						//		//CbulletPlant* bullet = new CbulletPlant(x, y, !theoY, theoX);
						//		//scene->AddObject(bullet);
						//	}
					}
				}
			}
		}
		else if (isDowning) {

			if (y < startY)
			{
				vy = SPEED;
			}
			else {
				//IsActive = false;
				vy = 0;
				y = startY;
				if (GetTickCount64() - time_down_pipe > TIME_IN_PIPE) {

					if ((distanceMario_PlantEnemies() > DISTANCE_MIN_MARIO_PLANT))
					{

						//DebugOut(L">>> CAY SE TROI LEN >>> \n");
						SetState(PLANT_STATE_UP);
					}
					else {
						//DebugOut(L">>> MARIO CO THE DI TREN MIENG CONG DUNG NAM TRONG PHAM VI CAY KHONG HOAT DONG >>> \n");
						SetState(PLANT_STATE_NOT_TOUCH);
					}

					//else IsActive = true;
				}
			}
		}
		else {
			/*{
				DebugOut(L">>> KIEM TRA SETSTATE>>> \n");
				SetState(PLANT_STATE_NOT_TOUCH);
			}*/
			if (y < startY)
			{
				vy = SPEED;
			}
			else {
				vy = 0;
				y = startY;
				//IsActive = false;
				if (GetTickCount64() - time_down_pipe > TIME_IN_PIPE_START) {
					//DebugOut(L">>> NGOAI PHAM VI CAY HOAT DONG >>> \n");
					SetState(PLANT_STATE_UP);
				}
			}
		}
	}
	else {
		//DebugOut(L">>> CAY DANG NGUNG HOAT DONG >>> \n");
		return;
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGreen_Plant::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

float CGreen_Plant::distanceMario_PlantEnemies() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	return abs(mario->GetX() - x);

}

int CGreen_Plant::LeftORightMario() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetX() < GetX()) //Mario ben trai cai cay
	{
		return 1;
	}
	else return -1;
}

int CGreen_Plant::TopOrBottomYMario()
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetY() < GetY()) //Mario o phia tren cai cay 
	{
		return 1;
	}
	else return -1;
}

void CGreen_Plant::Render()
{

	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (type == PLANT_TYPE_SHOOT) {

		if (LeftORightMario() == 1 && TopOrBottomYMario() == -1)
			if (!isShoot) aniId = ID_ANI_GREEN_PLANT_LEFT_UNDER_NOT_SHOOT;
			else {
				aniId = ID_ANI_GREEN_PLANT_LEFT_UNDER_SHOOT;
			}
		else if (LeftORightMario() == 1 && TopOrBottomYMario() == 1)
			if (!isShoot) aniId = ID_ANI_GREEN_PLANT_LEFT_TOP_NOT_SHOOT;
			else aniId = ID_ANI_GREEN_PLANT_LEFT_TOP_SHOOT;
		else if (LeftORightMario() == -1 && TopOrBottomYMario() == 1)
			if (!isShoot) aniId = ID_ANI_GREEN_PLANT_RIGHT_TOP_NOT_SHOOT;
			else aniId = ID_ANI_GREEN_PLANT_RIGHT_TOP_SHOOT;
		else {
			if (!isShoot) aniId = ID_ANI_GREEN_PLANT_RIGHT_UNDER_NOT_SHOOT;
			else aniId = ID_ANI_GREEN_PLANT_RIGHT_UNDER_SHOOT;
		}
	}

	else if (type == PLANT_TYPE_NOT_SHOOT) aniId = ID_ANI_GREEN_PLANT_NOT_SHOOT;

	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGreen_Plant::SetState(int state)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (state)
	{
	case PLANT_STATE_UP:
		if (distanceMario_PlantEnemies() < DISTANCE_PLANT_ENEMIS_MAYBE_SHOW_UP)
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
	case PLANT_STATE_NOT_TOUCH:
		y = startY;
		vy = 0;
		break;
	}
	CGameObject::SetState(state);

}
