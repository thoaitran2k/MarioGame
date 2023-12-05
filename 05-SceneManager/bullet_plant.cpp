#include "bullet_plant.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Animation.h"
#include "PipePlantShoot.h"
#include "PlantShootRed.h"
#include "Platform.h"
#include "Background.h"




void CbulletPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BULLET_BBOX_WIDTH / 2;
	top = y - BULLET_BBOX_HEIGHT / 2;
	right = left + BULLET_BBOX_WIDTH;
	bottom = top + BULLET_BBOX_HEIGHT;
}

//CbulletPlant::CbulletPlant(float x, float y, float vx, float vy) {
//	
//	vx = BULLET_SPEED_X;
//	vy = BULLET_SPEED_Y;
//}


CbulletPlant::CbulletPlant(float x, float y,float nx,float ny) 
{

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();


	if (mario->GetX() < x && mario->GetY() < y)
	{
		if (abs(mario->GetX() - x) <= 60)
			SetState(1);

		if (abs(mario->GetX() - x) <= 150 && abs(mario->GetX() - x) >= 60) {
			SetState(6);
		}
		
		if (abs(mario->GetY() - y) < 20)
			SetVy(-0.01f);


		
		//CbulletPlant* bullet = new CbulletPlant(x, y, !theoY, !theoX);
		//scene->AddObject(bullet);

	}
	else if (mario->GetX() < x && mario->GetY() > y)
	{
		if (abs(mario->GetX() - x) <= 60)
			SetState(2);

		 if (abs(mario->GetX() - x) <= 150 && abs(mario->GetX() - x) >= 60) {
			 SetState(5);
		}
		 if (abs(mario->GetY() - y) < 40)
			 SetVy(-0.01f);
		//SetVx(-BULLET_SPEED_X);
		//SetVy(BULLET_SPEED_Y);

		//CbulletPlant* bullet = new CbulletPlant(x + 2, y - PLANT_BBOX_HEIGHT / 2, theoY, !theoX);
		//scene->AddObject(bullet);
	}


	if (mario->GetX() > x && mario->GetY() > y)
	{
		SetState(3);

		if (abs(mario->GetX() - x) <= 70)
			SetState(3);

		if (abs(mario->GetX() - x) <= 150 && abs(mario->GetX() - x) >= 70) {
			SetState(8);
		}
		if (abs(mario->GetY() - y) < 40)
			SetVy(-0.01f);
		//SetVx(BULLET_SPEED_X);
		//SetVy(BULLET_SPEED_Y);

		//CbulletPlant* bullet = new CbulletPlant(x, y, !theoY, !theoX);
		//scene->AddObject(bullet);

	}
	else if (mario->GetX() > x && mario->GetY() < y)
	{
		//SetState(4);

		if (abs(mario->GetX() - x) <= 70)
			SetState(4);

		if (abs(mario->GetX() - x) <= 150 && abs(mario->GetX() - x) >= 70) {
			SetState(7);
		}

		if (abs(mario->GetY() - y) < 20)
			SetVy(0.01f);
		//SetVx(BULLET_SPEED_X);
		//SetVy(-BULLET_SPEED_Y);

		//CbulletPlant* bullet = new CbulletPlant(x + 2, y - PLANT_BBOX_HEIGHT / 2, theoY, !theoX);
		//scene->AddObject(bullet);
	}

	start_deleted = GetTickCount64();
	//SetState(BULLET_LEFT_BOT);
	//this->x = x;
	//this->y = y;
	

}


///////////////////////////////////////////////////////////////////////

void CbulletPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {


	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (GetTickCount64() - start_deleted > TIME_BULLET_DELETE) {
		isDeleted = true;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CbulletPlant::OnNoCollision(DWORD dt)
{
	
		x += vx * dt;
		y += vy * dt;
	
};


void CbulletPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (e->obj->IsPlatform() && e->obj->IsBlocking()) isDeleted = true;
}


void CbulletPlant::Render() {
	CAnimations* animations = CAnimations::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	
	int aniId = 0;
	if (vx > 0)
		aniId = ID_ANI_BULLET_RIGHT;
	else
		aniId = ID_ANI_BULLET_LEFT;

		
	
	
	animations->Get(aniId)->Render(x, y);
}

//void CbulletPlant::SetState(int state)
//{
//	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
//
//	switch (state)
//	{
//	case BULLET_LEFT_BOT:
//		//if (mario->GetX() < x && mario->GetY() < y)
//		//{
//			//y = y + PLANT_BBOX_HEIGHT / 2;
//			vy = BULLET_SPEED_Y;
//			//x = x + PLANT_BBOX_WIDTH;
//			vx = -BULLET_SPEED_X;
//		//}
//		break;
//	/*case BULLET_LEFT_TOP:
//		y = y - PLANT_BBOX_HEIGHT / 2;
//		vy = -BULLET_SPEED_Y;
//		x = x + PLANT_BBOX_WIDTH;
//		vx = -BULLET_SPEED_X;
//		break;
//	case BULLET_RIGHT_BOT:
//		x = x + PLANT_BBOX_WIDTH;
//		vx = BULLET_SPEED_X;
//		y = y - PLANT_BBOX_HEIGHT / 2;
//		vy = -BULLET_SPEED_Y;
//		
//		break;
//	case BULLET_RIGHT_TOP:
//		x = x + PLANT_BBOX_WIDTH;
//		vx = BULLET_SPEED_X;
//		y = y - PLANT_BBOX_HEIGHT / 2;
//		vy = -BULLET_SPEED_Y;
//		break;*/
//	}
//	CGameObject::SetState(state);
//}

void CbulletPlant::SetState(int b) {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	//huong 1
	switch (b)
	{
	case BULLET_LEFT_TOP: //1
		SetVx(-BULLET_SPEED_X);
		SetVy(-BULLET_SPEED_Y);
		break;

	case 6:
		SetVx(-0.06f);
		SetVy(-0.03f);
		break;

	case BULLET_LEFT_BOT: //2
		SetVx(-BULLET_SPEED_X);
		SetVy(BULLET_SPEED_Y);
		break;

	case 5:
		SetVx(-0.06f);
		SetVy(0.035);
		break;

	case BULLET_RIGHT_BOT:
		SetVx(BULLET_SPEED_X);
		SetVy(BULLET_SPEED_Y);
		break;

	case 8:
		SetVx(0.06f);
		SetVy(0.03f);
		break;
	case 7:
		SetVx(0.06f);
		SetVy(-0.02f);
		break;

	case BULLET_RIGHT_TOP:
		SetVx(BULLET_SPEED_X);
		SetVy(-BULLET_SPEED_Y);
		break;

	
	}
	
	CGameObject::SetState(state);
}
