#include "PlantShootRed.h"
#include "Game.h"
#include "PlayScene.h"
#include "GameObject.h"
#include "bullet_plant.h"


CPlantShootRed::CPlantShootRed(float x, float y) :CGameObject(x, y)
{
	startY = y;
	minY = startY - PLANT_BBOX_HEIGHT;
	SetState(PLANT_STATE_UP);
	
}

void CPlantShootRed::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PLANT_BBOX_WIDTH / 2;
	t = y - PLANT_BBOX_HEIGHT / 2 + 4;
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
				if (!isShoot) 
				{
					if (GetTickCount64() - time_shoot < TIME_SHOOT)
					{
						isShoot = true;
						bool atTop = false, atLeft = false;
						if(PosWithXMario() ==1)
						{
							atTop = true;
						}
						if (PosWithYMario() == 1)
						{
							atLeft = true;
						}
						/*if (atTop && atLeft)
						{
							Cbullet_plant* bullet = new Cbullet_plant(x,y, atLeft, !atTop);
							scene->AddObject(bullet);
						}
						if (!atTop && atLeft)
						{
							Cbullet_plant* bullet = new Cbullet_plant(x, y, atLeft, !atTop);
							scene->AddObject(bullet);
						}
						if(atTop && !atLeft)
						{
							Cbullet_plant* bullet = new Cbullet_plant(x, y, atLeft, !atTop);
							scene->AddObject(bullet);
						}
						if(!atTop && !atLeft)
						{
							Cbullet_plant* bullet = new Cbullet_plant(x, y, atLeft, !atTop);
							scene->AddObject(bullet);
						}*/
						
					}
				}
			}
		}
	}
	else if (isDowning) {
		if(y < startY +2 - DISTANCE_PIPE_LONG_SHORT)
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
	else {
		if (y < startY + 2 - DISTANCE_PIPE_LONG_SHORT) {
			vy = SPEED_GROW_UP;
		}
		else {
			vy = 0;
			y = startY + 2 - DISTANCE_PIPE_LONG_SHORT;
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

int CPlantShootRed::PosWithXMario() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetX() < GetX()) //Mario ben trai cai cay
	{
		return 1;
	}
	else return - 1;
}

int CPlantShootRed::PosWithYMario() {
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
	if (PosWithXMario() == 1 && PosWithYMario() == -1)
		if (!isShoot) aniId = ID_ANI_PLANT_LEFT_UNDER_NOT_SHOOT;
		else aniId = ID_ANI_PLANT_LEFT_UNDER_SHOOT;
	else if (PosWithXMario() == 1 && PosWithYMario() == 1)
		if (!isShoot) aniId = ID_ANI_PLANT_LEFT_TOP_NOT_SHOOT;
		else aniId = ID_ANI_PLANT_LEFT_TOP_SHOOT;
	else if (PosWithXMario() == -1 && PosWithYMario() == 1)
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
	switch (state)
	{
	case PLANT_STATE_UP:
		isUpping = true;
		isDowning = false;
		isShoot = true;
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



