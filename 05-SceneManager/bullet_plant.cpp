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


CbulletPlant::CbulletPlant(float bx, float by, bool top_bottom, bool left_right)
{

	/*CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (top_bottom)
	{
		y = by + PLANT_BBOX_HEIGHT / 2;
		vy = BULLET_SPEED_Y;
	}
	else
	{
		y = by - PLANT_BBOX_HEIGHT / 2;
		vy = -BULLET_SPEED_Y;
	}

	if (left_right)
	{
		x = bx + PLANT_BBOX_WIDTH;
		vx = BULLET_SPEED_X*2;
	}
	else
	{
		x = bx - PLANT_BBOX_WIDTH;
		vx = -BULLET_SPEED_X*2;
	}*/
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
