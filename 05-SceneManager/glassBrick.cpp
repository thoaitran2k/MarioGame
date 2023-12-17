#include "glassBrick.h"
#include "AssetIDs.h"
#include "GameObject.h"
#include "Game.h"
#include "PlayScene.h"


CglassBrick::CglassBrick(float x, float y, int mode) :CGameObject(x,y)
{


	
	this->mode = mode;
	timming = -1;
	mario_collis = false;
	unBox = false;
	Empty = false;
	SetState(GLASS_BRICK_STATE_NORMAL);
	//p = NULL;
	
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

void CglassBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - GLASS_BRICK_BBOX_WIDTH / 2;
	t = y - GLASS_BRICK_BBOX_HEIGHT / 2;
	r = l + GLASS_BRICK_BBOX_WIDTH;
	b = t + GLASS_BRICK_BBOX_HEIGHT;
}

void CglassBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//if (mode == GLASS_BRICK_MODEL_CONTAIN_BUTTON) CreateButtonP();

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	/*if (mario_collis)
	{
		scene->GlassBrickChangeToCoin();
	}*/

	//if (mode == 2) notCoin = 1;
	
	if (state == GLASS_BRICK_STATE_ISTOUCHED)
	{
		SetState(GLASS_BRICK_STATE_CHANGE_TO_COIN);
		}

	if (mario_collis){
		unBox = true;
		Empty = true;
		
	}

	//if (p->GetState() == BUTTON_STATE_BE_COLLIDABLED)
		//SetState(GLASS_BRICK_STATE_CHANGE_TO_COIN);

	

	/* if (state == GLASS_BRICK_STATE_CHANGE_TO_COIN && GetTickCount64() - timming > 10000)
	{
		SetState(GLASS_BRICK_STATE_NORMAL);
	}*/
}

void CglassBrick::SetState(int state)
{
	
	
	switch (state)
	{
	case GLASS_BRICK_STATE_NORMAL:
		notCoin = 1;
		break;
	case GLASS_BRICK_STATE_ISTOUCHED:
		//notCoin = 1;
		break;
	case GLASS_BRICK_STATE_CHANGE_TO_COIN:
		notCoin = 0;
		//mode = GLASS_BRICK_MODEL_NORMAL;
		if (mode == GLASS_BRICK_MODEL_CONTAIN_BUTTON) { notCoin = 1; return; }
		//isDeleted = true;
		timming = GetTickCount64();
		break;
	}
	CGameObject::SetState(state);
	
}
