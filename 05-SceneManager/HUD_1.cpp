#include "HUD_1.h"
#include"PlayScene.h"
#include "Mario.h"

CHUD_1* CHUD_1::__instance = NULL;

CHUD_1* hud = NULL;
//vector<LPGAMEOBJECT> objects;

CHUD_1* CHUD_1::GetInstance() {
	if (__instance == NULL) __instance = new CHUD_1(0, 0);
	return __instance;
}

void CHUD_1::Render() {



	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	CAnimations::GetInstance()->Get(ID_ANI_BLACK_RECTANGEL)->Render(x, y);

	CAnimations::GetInstance()->Get(ID_ANI_HUD)->Render(x, y);

	AniNumber(1, x + POSITION_WORLD_X, y - ADJUST_Y_POWER_POSITION);


	//SPEEDS MARIO

	CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - ADJUST_X_POWER_POSITION, y - ADJUST_Y_POWER_POSITION);
	CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - ADJUST_X_POWER_POSITION + DISTANCE_EVERY_LEVEL_RUN, y - ADJUST_Y_POWER_POSITION);
	CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - ADJUST_X_POWER_POSITION + DISTANCE_EVERY_LEVEL_RUN * 2, y - ADJUST_Y_POWER_POSITION);


	//point
	AniNumber(1, x + POSITION_SCORE_X, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber(2, x + POSITION_SCORE_X + DISTANCE_NUMBER, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber(3, x + POSITION_SCORE_X + DISTANCE_NUMBER * 2, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber(4, x + POSITION_SCORE_X + DISTANCE_NUMBER * 3, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber(5, x + POSITION_SCORE_X + DISTANCE_NUMBER * 4, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber(6, x + POSITION_SCORE_X + DISTANCE_NUMBER * 5, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber(7, x + POSITION_SCORE_X + DISTANCE_NUMBER * 6, y - ADJUST_Y_POWER_POSITION_UNDER);

	//times
	AniNumber(1, x + POSITION_CLOCK_X, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber(0, x + POSITION_CLOCK_X + DISTANCE_NUMBER, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber(0, x + POSITION_CLOCK_X + DISTANCE_NUMBER * 2, y - ADJUST_Y_POWER_POSITION_UNDER);

	//Coin
	int coin; 
	coin = mario->GetCoin();
	if (coin / 10 > 0) {
		AniNumber(coin / 10, x + POSITION_COIN_X, y - ADJUST_Y_POWER_POSITION);
	}
	AniNumber(coin % 10, x + POSITION_COIN_X + DISTANCE_NUMBER, y - ADJUST_Y_POWER_POSITION);
	
}

void CHUD_1::AniNumber(int n, float Xnumber, float Ynumber) {
	if (n == 0) CAnimations::GetInstance()->Get(ID_ANI_0)->Render(Xnumber, Ynumber);
	else if (n == 1) CAnimations::GetInstance()->Get(ID_ANI_1)->Render(Xnumber, Ynumber);
	else if (n == 2) CAnimations::GetInstance()->Get(ID_ANI_2)->Render(Xnumber, Ynumber);
	else if (n == 3) CAnimations::GetInstance()->Get(ID_ANI_3)->Render(Xnumber, Ynumber);
	else if (n == 4) CAnimations::GetInstance()->Get(ID_ANI_4)->Render(Xnumber, Ynumber);
	else if (n == 5) CAnimations::GetInstance()->Get(ID_ANI_5)->Render(Xnumber, Ynumber);
	else if (n == 6) CAnimations::GetInstance()->Get(ID_ANI_6)->Render(Xnumber, Ynumber);
	else if (n == 7) CAnimations::GetInstance()->Get(ID_ANI_7)->Render(Xnumber, Ynumber);
	else if (n == 8) CAnimations::GetInstance()->Get(ID_ANI_8)->Render(Xnumber, Ynumber);
	else  CAnimations::GetInstance()->Get(ID_ANI_9)->Render(Xnumber, Ynumber);

}

void CHUD_1::AniCard(int n, float Xcard, float Ycard) {

}


void CHUD_1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cx = 0.0f;
	float cy = 0.0f;
	//CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CGame* game = CGame::GetInstance();
	

	CGame::GetInstance()->GetCamPos(cx, cy);
	x = cx + 150.0f;
	y = cy + 187.0f;

	//x = cx;
	//y = cy;

}

void CHUD_1::RenderBoundingBox() {
	
}

