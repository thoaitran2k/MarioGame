#include "glassBrick.h"
#include "AssetIDs.h"
#include "GameObject.h"
#include "Game.h"
#include "PlayScene.h"
#include "FragGlass.h"


CglassBrick::CglassBrick(float x, float y, int mode) :CGameObject(x,y)
{

	//this->vy = 0.035f;
	this->ay = 0.00075f;
	this->mode = mode;
	timming = -1;
	mario_collis = false;
	unBox = false;
	Empty = false;
	SetState(GLASS_BRICK_STATE_NORMAL);
	frag = NULL;
	CreateNewKoopa();
	//p = NULL;
	
}

void CglassBrick::CreateAniFragGlass1() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CGameObject* frag_glass = scene->CreateObjectAndReturn(OBJECT_TYPE_FRAG_GLASS_BRICK, x-6,y+1, -0.004f, 0);
	
	AddFrag_Glass(frag_glass);
	CGameObject* frag_glass2 = scene->CreateObjectAndReturn(OBJECT_TYPE_FRAG_GLASS_BRICK, x +6, y-1, 0.004f, 0);
	AddFrag_Glass(frag_glass2);
	

}
void CglassBrick::CreateAniFragGlass2() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	
	
	CGameObject* frag_glass3 = scene->CreateObjectAndReturn(OBJECT_TYPE_FRAG_GLASS_BRICK_2, x-8, y-4, 0.001f, 0);
	CGameObject* frag_glass1 = scene->CreateObjectAndReturn(OBJECT_TYPE_FRAG_GLASS_BRICK_2, x+10, y+6, -0.008f, 0);
	AddFrag_Glass(frag_glass3);
	AddFrag_Glass(frag_glass1);
	

}

void CglassBrick::Render()
{
	
	int aniId = 0;

	switch(state)
	{
	case GLASS_BRICK_STATE_NORMAL:
		aniId = ID_ANI_GLASS_BRICK;
		break;

	case GLASS_BRICK_STATE_ISTOUCHED:
		aniId = ID_ANI_BRICK_CONTAIN_BUTTON_P;
		break;

	case GLASS_BRICK_STATE_CHANGE_TO_COIN:
		if(mode != GLASS_BRICK_MODEL_CONTAIN_BUTTON)
		aniId = ID_ANI_BREAK_BRICK_TRANSFORM_TO_COIN;
		break;

	/*case GLASS_BRICK_STATE_BREAK:
		if(mode != GLASS_BRICK_MODEL_CONTAIN_BUTTON)
		aniId = ID_ANI_GLASS_BRICK_BREAK;
		break;*/
	}
	/*switch (state)
	{
	case GLASS_BRICK_STATE_NORMAL:
		aniId = ID_ANI_GLASS_BRICK;
		break;
	case GLASS_BRICK_STATE_ISTOUCHED:
		if (mode == GLASS_BRICK_MODEL_CONTAIN_BUTTON)	
			aniId = ID_ANI_BRICK_CONTAIN_BUTTON_P;
		break;
	case GLASS_BRICK_STATE_CHANGE_TO_COIN:
		aniId = ID_ANI_BREAK_BRICK_TRANSFORM_TO_COIN;
		break;
	default:
		break;
	}*/

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	
	//RenderBoundingBox();
}


void CglassBrick::CreateNewKoopa(){
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (mode == 2) {
		CGameObject* new_koopa = scene->CreateObjectAndReturn(OBJECT_TYPE_NEW_RED_KOOPA, x+64, y-50, 0, 0);
		Addnew_koopa(new_koopa);
		DebugOut(L">>> koopa duoc rs >>> \n");
		new_koopa->SetState(KOOPA_RED_STATE_WALKING);
	}
	
}


void CglassBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	//if (state == GLASS_BRICK_STATE_CHANGE_TO_COIN) return;

	//else {
		l = x - GLASS_BRICK_BBOX_WIDTH / 2;
		t = y - GLASS_BRICK_BBOX_HEIGHT / 2;
		r = l + GLASS_BRICK_BBOX_WIDTH;
		b = t + GLASS_BRICK_BBOX_HEIGHT;
	//}
}


void CglassBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CglassBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vy += ay * dt;
	//if (mode == GLASS_BRICK_MODEL_CONTAIN_BUTTON) CreateButtonP();

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	/*if (mario_collis)
	{
		scene->GlassBrickChangeToCoin();
	}*/

	//if (mode == 2) notCoin = 1;
	
	

	 if (mario_collis){
		unBox = true;
		Empty = true;
		
	}

	//if (p->GetState() == BUTTON_STATE_BE_COLLIDABLED)
		//SetState(GLASS_BRICK_STATE_CHANGE_TO_COIN);
	 /*if (state == GLASS_BRICK_STATE_ISTOUCHED)
	 {
		 SetState(GLASS_BRICK_STATE_CHANGE_TO_COIN);
	 }*/

	 else if (state == GLASS_BRICK_STATE_BREAK)
	{
		 //Reset();
		 isDeleted = true;
		// CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		 //CFragGlass* frag = new CFragGlass(x + 50, y - 80, 0, 0);
		// scene->AddObject(frag);
		
	}


	else if (state == GLASS_BRICK_STATE_CHANGE_TO_COIN && GetTickCount64() - timming > 14000)
	{
		SetState(GLASS_BRICK_STATE_NORMAL);
	}
}

void CglassBrick::SetState(int state)
{
	
	
	switch (state)
	{
	case GLASS_BRICK_STATE_NORMAL:
		ay = 0;
		notCoin = 1;
		break;
	case GLASS_BRICK_STATE_ISTOUCHED:
		ay = 0;
		//notCoin = 1;
		break;
	case GLASS_BRICK_STATE_CHANGE_TO_COIN:
		ay = 0;
		notCoin = 0;
		//mode = GLASS_BRICK_MODEL_NORMAL;
		if (mode == GLASS_BRICK_MODEL_CONTAIN_BUTTON) { notCoin = 1; return; }
		//isDeleted = true;
		timming = GetTickCount64();
		break;

	case GLASS_BRICK_STATE_BREAK:
		//CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		//CFragGlass* frag = new CFragGlass(x,y, 0.004f, -0.00035f);
		//scene->AddObject(frag);

		//vy = -0.35f;
		//ay = 0.00075f;
		if (mode == GLASS_BRICK_MODEL_CONTAIN_BUTTON) { notCoin = 1; return; }

		timming = GetTickCount64();
		break;
	}
	CGameObject::SetState(state);
	
}
