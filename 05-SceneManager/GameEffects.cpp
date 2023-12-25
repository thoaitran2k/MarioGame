#include "GameEffects.h"
#include"Game.h"
#include"PlayScene.h"


void CGameEffects::Render() {

	int aniId = -1;

	if (type_effect == EFFECT_SCORE_100) aniId = ID_ANI_EFFECT_100_SCORE;

	else if (type_effect == EFFECT_SCORE_200) aniId = ID_ANI_EFFECT_200_SCORE;

	else if (type_effect == EFFECT_UP) aniId = ID_ANI_EFFECT_1UP;

	else if (type_effect == EFFECT_SCORE_1000) aniId = ID_ANI_EFFECT_1000_SCORE;


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);


}

void CGameEffects::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	if ((EFFECT_SCORE_100 <= type_effect) && (type_effect <= EFFECT_UP))
	{
		if (GetTickCount64() - timming > EFFECT_DELETE_TIME) { isDeleted = true; }

		vy = -SPEED_EFFECT;
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}
