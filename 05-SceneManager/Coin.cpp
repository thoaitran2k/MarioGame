#include "Coin.h"
#include "Mario.h"
#include "PlayScene.h"

void CCoin::Render()
{
		int aniId;

		if (state == COIN_STATE_BASIC)
		aniId = ID_ANI_COIN;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (!canCollect) vy += ay * dt;

	//DebugOut(L"[VANTOC] %f\n", vy);
	if (vy > COIN_MAX_SPEED_FALL) {
		
		Delete();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CCoin::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CCoin::SetState(int l) {
	switch (l) {
	case COIN_SUMMON_STATE:
		vy = -OUT_BRICK;
		canCollect = false;
		break;

	case COIN_STATE_BASIC:
		canCollect = true;
		break;
	}
	CGameObject::SetState(l);
}