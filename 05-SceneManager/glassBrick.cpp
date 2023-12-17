#include "glassBrick.h"
#include "AssetIDs.h"

CglassBrick::CglassBrick(float x, float y, int model) :CGameObject(x,y)
{
	this->mode = model;
	timming = -1;
	mario_collis = false;
	unBox = false;
	Empty = false;
	SetState(GLASS_BRICK_STATE_NORMAL);
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
	default:
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


	if (mario_collis) {
		unBox = true;
		Empty = true;
	}

	

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
		break;
	case GLASS_BRICK_STATE_ISTOUCHED:
		break;
	case GLASS_BRICK_STATE_CHANGE_TO_COIN:
		if (mode == GLASS_BRICK_MODEL_CONTAIN_BUTTON) return;
		timming = GetTickCount64();
		break;
	default:
		break;
	}
	CGameObject::SetState(state);
}
