#include "bullet_plant.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Animation.h"
#include "PipeplantShoot.h"
#include "PlantShootRed.h"


Cbullet_plant::Cbullet_plant(float x, float y)
{
	this->x = 0;
	this->y = 0; 
}

void Cbullet_plant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BULLET_BBOX_WIDTH / 2;
	t = y - BULLET_BBOX_HEIGHT / 2;
	r = l + BULLET_BBOX_WIDTH;
	b = t + BULLET_BBOX_HEIGHT;
}

/*
Cbullet_plant::Cbullet_plant(float bx, float by, bool Up, bool Right)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (Up)
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

}
*/

///////////////////////////////////////////////////////////////////////

//void Cbullet_plant::Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects) {

	//vx -= ax * dt;
	//vy += ay * dt;


	/*CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (GetTickCount64() - start_deleted > TIME_BULLET_DELETE) {
		isDeleted = true;
	}*/

	//CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);

//}


void Cbullet_plant::Render() {
	CAnimations* animations = CAnimations::GetInstance();

	int aniId = 0;
	//if (vx > 0)
	//{
		//aniId = ID_ANI_BULLET_RIGHT;
	//}
	//else
	aniId = ID_ANI_BULLET_RIGHT;
	animations->Get(aniId)->Render(x,y);
}

void Cbullet_plant::OnCollisionWith(LPCOLLISIONEVENT e) {
	// if (e->obj->IsPlatform() && e->obj->IsBlocking()) isDeleted = true;
}
