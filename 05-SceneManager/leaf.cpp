#include "leaf.h"
#include "Mario.h"
#include "PlayScene.h"

void CLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_LEAF_RIGHT)->Render(x, y);

	//RenderBoundingBox();
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (!canCollect) vy += ay * dt;

	//DebugOut(L"[VANTOC] %f\n", vy);
	if (vy > LEAF_MAX_SPEED_FALL) {

		Delete();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::SetState(int l) {
	switch (l) {
	case LEAF_SUMMON_STATE:
		vy = -OUT_BRICK;
		canCollect = false;
		break;

	case LEAF_NOT_SUMMON_STATE:
		canCollect = true;
		break;
	}
	CGameObject::SetState(l);
}
