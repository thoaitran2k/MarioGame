#include "Red_Koopa.h"
#include "Platform.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"
#include "Background.h"
#include "MushRoom.h"
#include "CheckKoopaFall.h"




CRed_Koopa::CRed_Koopa(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_RED_GRAVITY;
	count_start =GetTickCount64();
	SetState(KOOPA_RED_STATE_WALKING);
	isTurtleShell = false;
	startX = x;
	//isCollis = false;
	isOnPlatform = false;
	checkfall = NULL;
	isKicked = false;
	HaveOrNotCheckFall = true;
	
}

void CRed_Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (state == KOOPA_RED_STATE_WALKING)
	{
		left = x - KOOPA_RED_BBOX_WIDTH / 2;
		top = y - KOOPA_RED_BBOX_HEIGHT / 2;
		right = left + KOOPA_RED_BBOX_WIDTH;
		bottom = top + KOOPA_RED_BBOX_HEIGHT+4;
	}
	else
	{
		left = x - KOOPA_RED_BBOX_WIDTH / 2;
		top = y - KOOPA_RED_BBOX_HEIGHT / 2;
		right = left + KOOPA_RED_BBOX_WIDTH;
		bottom = top + KOOPA_RED_BBOX_HEIGHT-1;
	}

}

void CRed_Koopa::CreateCheckfall() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

		

	
		if (vx<0)
		{
			CGameObject* add_object_left = scene->CreateObjectAndReturn(OBJECT_TYPE_CHECKFALL_KOOPA, GetX()- KOOPA_RED_BBOX_WIDTH, y,0 /*KOOPA_RED_WALKING_SPEED*/, 0);
			
			AddCheck(add_object_left);
			DebugOut(L">>> check tao obj left >>> \n");
			checkfall->SetState(STATE_LEFT_KOOPA);
			
			
			
			
		}
		else if(vx>0)
		{
			CGameObject* add_object_right = scene->CreateObjectAndReturn(OBJECT_TYPE_CHECKFALL_KOOPA, GetX()+ KOOPA_RED_BBOX_WIDTH, y,0/* KOOPA_RED_WALKING_SPEED*/, 0);
			
			AddCheck(add_object_right);
			DebugOut(L">>> check tao obj right >>> \n");
			checkfall->SetState(STATE_RIGHT_KOOPA);
			
		}

		
		

		
		


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
	if (dynamic_cast<CCheckFall*>(e->obj))
		this->OnCollisionWithCheckFall(e);
}

void CRed_Koopa::OnCollisionWithCheckFall(LPCOLLISIONEVENT e)
{
	CCheckFall* checkfall = dynamic_cast<CCheckFall*>(e->obj);
	//SetState(KOOPA_RED_STATE_ISDEFEND);
}

void CRed_Koopa::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	CBackground* platform = dynamic_cast<CBackground*>(e->obj);
	if (e->ny < 0) {
		isOnPlatform = true;
	}

	if (isOnPlatform)
	{
		isTurtleShell = true;

	}
}

void CRed_Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	

	if (HaveOrNotCheckFall && checkfall == NULL) {
		//count_start = GetTickCount64();


		CreateCheckfall();
		DebugOut(L">>> CHECK TAO OBJ >>> \n");

	}

	if (checkfall->GetIsOnPlatform() && HaveOrNotCheckFall)
	{
		ResetCheck();
		vx = -vx;
		DebugOut(L">>> chi xet con rua di bo >>> \n");
	}
	
	if (!HaveOrNotCheckFall)
	{
		DeleteCheck();
	}

	
	

	

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
	
	if(state == KOOPA_RED_STATE_WALKING){
		if (vx > 0)
		{
			aniId = ID_ANI_KOOPA_RED_WALKING_RIGHT;
		}
		else {
			aniId = ID_ANI_KOOPA_RED_WALKING_LEFT;
		}
	}
	else
	 if (isTurtleShell && !isKicked)
	{
		aniId = ID_ANI_KOOPA_RED_DEFEND;
		DebugOut(L">>> Rua dang bien thanh mai >>> \n");
	}
	 else if(isTurtleShell && isKicked)
	 {
		 aniId = ID_ANI_KOOPA_RED_ISKICKED;
		 DebugOut(L">>> Rua bi da va dang chay >>> \n");
	 }
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CRed_Koopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_RED_STATE_ISDEFEND:
		isKicked = false;
		isTurtleShell = true;
		HaveOrNotCheckFall = false;
		//isCollis = true; 
		vx = 0;
		vy = 0;
		break;
		
	case KOOPA_RED_STATE_ISKICKED:
		isKicked = true;
		isTurtleShell = true;
		HaveOrNotCheckFall = false;
		//isCollis = true;
		vx = 0.05f * LeftOrRightMarrio();
		break;
	case KOOPA_RED_STATE_WALKING:
		vx = -KOOPA_RED_WALKING_SPEED;
		HaveOrNotCheckFall = true;
		isKicked = false;
		
		//vx = 0;
		//isCollis = true;
		break;

	}
}
