#include "Red_Koopa.h"
#include "Platform.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
#include "Background.h"
#include "MushRoom.h"



CRed_Koopa::CRed_Koopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_RED_GRAVITY;
	die_start = -1;
	SetState(KOOPA_RED_STATE_WALKING);
	isTurtleShell = false;
	isCollis = false;
	isOnPlatform = false;
	
}

void CRed_Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{


	left = x - KOOPA_RED_BBOX_WIDTH / 2;
	top = y - KOOPA_RED_BBOX_HEIGHT / 2;
	right = left + KOOPA_RED_BBOX_WIDTH;
	bottom = top + KOOPA_RED_BBOX_HEIGHT+3;

}

void CRed_Koopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};


void CRed_Koopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CRed_Koopa*>(e->obj)) return;

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

void CRed_Koopa::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	CBackground* platform = dynamic_cast<CBackground*>(e->obj);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	if (e->ny < 0) {
		isOnPlatform = true;
	}

	if (isOnPlatform)
	{
		isDeleted = true;

	}
}

void CRed_Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

int CRed_Koopa::LeftOrRightMarrio() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetX() < GetX()) return 1;
	else return -1;
}

void CRed_Koopa::Render()
{
	int aniId;
	
		if (vx > 0)
		{
			aniId = ID_ANI_KOOPA_RED_WALKING_RIGHT;
		}
		else if (vx < 0) {
			aniId = ID_ANI_KOOPA_RED_WALKING_LEFT;
		}
	
	 if (isTurtleShell)
	{
		aniId = ID_ANI_KOOPA_RED_DEFEND;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CRed_Koopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_RED_STATE_ISDEFEND:
		isTurtleShell = true;
		isCollis = true; 
		vx = 0;
		vy = 0;
		break;
		
	case KOOPA_RED_STATE_ISKICKED:
		isTurtleShell = true;
		isCollis = true;
		vx = 0.05f * LeftOrRightMarrio();
		break;

	case KOOPA_RED_STATE_WALKING:
		vx = -KOOPA_RED_WALKING_SPEED;
		isCollis = true;
		break;
 

	}
	

}
