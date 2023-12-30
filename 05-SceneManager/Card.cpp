#include "Card.h"

void CCard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	//vy += ay * dt;

	if (!isActive) {
		if (GetTickCount64() - time_Render > 300)
		{
			if (id_mode == 1) id_mode = 2;
			else if (id_mode == 2) id_mode = 3;
			else if (id_mode == 3) id_mode = 1;
			time_Render = GetTickCount64();
		}

	}

	if (isActive) {
		if (GetTickCount64() - time_disappear > 1500)
			isDeleted = true;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CCard::Render()
{
	int aniId = ID_ANI_CARD_MUSHROOM;
	CAnimations* animations = CAnimations::GetInstance();
	if (id_mode == 1) aniId = ID_ANI_CARD_MUSHROOM;
	else if (id_mode == 2) aniId = ID_ANI_CARD_FLOWER;
	else if (id_mode == 3) aniId = ID_ANI_CARD_STAR;
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CARD_BBOX_WIDTH / 2;
	t = y - CARD_BBOX_HEIGHT / 2;
	r = l + CARD_BBOX_WIDTH;
	b = t + CARD_BBOX_HEIGHT;
}

void CCard::SetState(int state) {
	switch (state)
	{
	case STATE_CARD_IS_COLLECTED:
		isActive = true;
		vy = -SPEED_CARD_FLY;
		time_disappear = GetTickCount64();
		break;
	}
}
