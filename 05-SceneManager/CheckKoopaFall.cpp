#include "CheckKoopaFall.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"
#include "Platform.h"
#include "PlayScene.h"
#include "Game.h"
#include "Goomba.h"
#include "Background.h"



#define OBJ_BBOX_WIDTH 16
#define OBJ_BBOX_HEIGHT 16


CCheckFall::CCheckFall(float x, float y) :CGameObject(x, y)
{

	this->ax = 0;
	this->ay = 0.003f;
	isOnPlatformCheck = false;


}

void CCheckFall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - OBJ_BBOX_WIDTH / 2;
	t = y - OBJ_BBOX_HEIGHT / 2;
	r = l + OBJ_BBOX_WIDTH;
	b = t + OBJ_BBOX_HEIGHT;
}

void CCheckFall::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CCheckFall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	//if (!e->obj->IsBlocking()) return;
	//if (dynamic_cast<CCheckFall*>(e->obj)) return;


	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<CBackground*>(e->obj))
		this->OnCollisionWithPlatForm(e);
}

void CCheckFall::OnCollisionWithPlatForm(LPCOLLISIONEVENT e) {
	CBackground* platform = dynamic_cast<CBackground*>(e->obj);
	if (e->ny < 0) {
		isOnPlatformCheck = true;
	}
	else isOnPlatformCheck = false;


}

void CCheckFall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (isOnPlatformCheck) isDeleted = true;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

//void CCheckFall::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
//{
//
//}





void CCheckFall::Render()
{

	RenderBoundingBox();
}
