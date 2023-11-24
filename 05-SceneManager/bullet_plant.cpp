#include "bullet_plant.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Animation.h"
#include "PipePlantShoot.h"
#include "PlantShootRed.h"
#include "Platform.h"
#include "Background.h"




CbulletPlant::CbulletPlant(float x, float y) : CGameObject(x ,y ){
	this->ax = 0;
	this->ay = 0;

	vy = 0;
	startY = y;
	startX = x;
	SetState(BULLET_ROI_XUONG);
	
}

void CbulletPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BULLET_BBOX_WIDTH / 2;
	top = y - BULLET_BBOX_HEIGHT / 2;
	right = left + BULLET_BBOX_WIDTH;
	bottom = top + BULLET_BBOX_HEIGHT;
}


//Cbullet_plant::Cbullet_plant(float bx, float by, bool Left, bool Right)
//{
	//CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	/*if (Up)
	{
		y = by - PLANT_BBOX_HEIGHT / 2;
		vy = -BULLET_SPEED_Y;
	}
	else
	{
		y = by + PLANT_BBOX_HEIGHT / 2;
		vy = BULLET_SPEED_Y;
	}

	if (Right)
	{
		x = bx + PLANT_BBOX_WIDTH;
		vx = BULLET_SPEED_X;
	}
	else
	{
		x = bx - PLANT_BBOX_WIDTH;
		vx = -BULLET_SPEED_X;
	}
	start_deleted = GetTickCount64();
	*/

//}


///////////////////////////////////////////////////////////////////////

void CbulletPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (state == BULLET_RIGHT) {
		vx += ax * dt; 
		vy += ay * dt;
	}
	else if (state == BULLET_LEFT)
	{
		vx -= ax * dt;
		vy += ay * dt;
	}


	//if (state = MARIO_STATE_DIE) return;
	//if (GetTickCount64() - start_deleted > TIME_BULLET_DELETE) {
		//isDeleted = true;
	//}

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
	if (dynamic_cast<CbulletPlant* >(e->obj)) return;

		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}
	
	}

void CbulletPlant::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	CBackground* platform = dynamic_cast<CBackground*>(e->obj);
	if (platform->IsBlocking()) {}
	else if (e->ny < 0) {
		SetY(platform->GetY() - 9);
	}
}

void CbulletPlant::Render() {
	CAnimations* animations = CAnimations::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	

	int aniId;
	
	
	if (mario->GetX() > 248)
	{
		state = BULLET_LEFT;
		aniId = ID_ANI_BULLET_LEFT;
		
	}

	else {
		aniId = ID_ANI_BULLET_BLUE;
		state = BULLET_RIGHT;
	}
	
	animations->Get(aniId)->Render(x, y);
}

void CbulletPlant::SetState(int state)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (state)
	{
	case BULLET_LEFT:
		vx = -vx;
		break;
	case BULLET_ROI_XUONG:
		vx = 0;
		vy = 0.005f;
	}
	CGameObject::SetState(state);
}
