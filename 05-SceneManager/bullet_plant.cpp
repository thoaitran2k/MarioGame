#include "bullet_plant.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Animation.h"
#include "PipePlantShoot.h"
#include "PlantShootRed.h"
#include "Platform.h"




Cbullet_plant::Cbullet_plant(float x, float y) : CGameObject(x ,y ){
	this->ax = 0;
	this->ay = 0.00001f;

	vy = 0;
	startX = x;
	startY = y;
	SetState(BULLET_ROI_XUONG);
	
}

void Cbullet_plant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y ;
	r = l + BULLET_BBOX_WIDTH;
	b = t + BULLET_BBOX_HEIGHT;
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

void Cbullet_plant::Update(DWORD dt, vector<LPGAMEOBJECT>*coObjects) {

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (state == BULLET_ROI_XUONG) {
		vx = 0;
		vy += ay * dt;
	}
	else if (state == BULLET_LEFT)
	{
		if (startX > mario->GetX())
		{
			vx = -vx;
		}
		else  SetState(BULLET_RIGHT);
	}





	//if (state = MARIO_STATE_DIE) return;
	//if (GetTickCount64() - start_deleted > TIME_BULLET_DELETE) {
		//isDeleted = true;
	//}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}




void Cbullet_plant::OnCollisionWith(LPCOLLISIONEVENT e) {
	{
		if (!e->obj->IsBlocking() && !e->obj->IsPlatform()) return;
		if (!e->obj->IsPlayer()) {
			if (e->ny != 0)
			{
				vy = 0;
			}
			else if (e->nx != 0)
			{
				vx = -vx;
			}
		}

		if (dynamic_cast<Cbullet_plant*>(e->obj)) {}
		else if (dynamic_cast<CPlatform*>(e->obj))
			OnCollisionWithPlatForm(e);

	}
}

void Cbullet_plant::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	if (platform->IsBlocking()) {}
	else if (e->ny < 0) {
		SetY(platform->GetY() - BULLET_BBOX_HEIGHT);
	}
}

void Cbullet_plant::Render() {
	CAnimations* animations = CAnimations::GetInstance();

	int aniId = ID_ANI_BULLET_RIGHT;
	if (state == BULLET_ROI_XUONG)
	{
		aniId = ID_ANI_BULLET_RIGHT;
	}
	else aniId = ID_ANI_BULLET_LEFT;
	/*if (vx > 0)
	{
		aniId = ID_ANI_BULLET_RIGHT;
	}*/
	//else aniId = ID_ANI_BULLET_RIGHT;
	animations->Get(aniId)->Render(x, y);
}

void Cbullet_plant::SetState(int state)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (state)
	{
	case BULLET_RIGHT:
		if (x < mario->GetX()) vx = vx;
		break;
	}
	CGameObject::SetState(state);
}
