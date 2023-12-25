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

	AniNumber(1, x + POSITION_WORLD_X, y - ADJUST_Y_POWER_POSITION); //MAP 1


	



	//SPEEDS MARIO
	int mark;
	mark = mario->GetMarkFly();

	if (mark > 1) {
		CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - ADJUST_X_POWER_POSITION, y - ADJUST_Y_POWER_POSITION);
	}
	if (mark > 2) {
		CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - ADJUST_X_POWER_POSITION + DISTANCE_EVERY_LEVEL_RUN, y - ADJUST_Y_POWER_POSITION);
	}
	if (mark > 3) {
		CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - ADJUST_X_POWER_POSITION + DISTANCE_EVERY_LEVEL_RUN * 2, y - ADJUST_Y_POWER_POSITION);
	}
	if (mark > 4){
		CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - ADJUST_X_POWER_POSITION + DISTANCE_EVERY_LEVEL_RUN * 3, y - ADJUST_Y_POWER_POSITION);
	}
	if (mark > 5) {
		CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - ADJUST_X_POWER_POSITION + DISTANCE_EVERY_LEVEL_RUN * 4, y - ADJUST_Y_POWER_POSITION);
	}
	if (mark > 6) {
		CAnimations::GetInstance()->Get(ID_ANI_POWER_HUD)->Render(x - ADJUST_X_POWER_POSITION + DISTANCE_EVERY_LEVEL_RUN * 5, y - ADJUST_Y_POWER_POSITION);
	}
	if (mark >= 7) {
		CAnimations::GetInstance()->Get(ID_ANI_P)->Render(x - ADJUST_X_POWER_POSITION_MAX, y - ADJUST_Y_POWER_POSITION);
	}
	


	//point
	int point = mario->GetPoint();
	AniNumber(point/1000000, x + POSITION_SCORE_X, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber((point/100000)%10, x + POSITION_SCORE_X + DISTANCE_NUMBER, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber((point/10000)%10, x + POSITION_SCORE_X + DISTANCE_NUMBER * 2, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber((point/1000)%10, x + POSITION_SCORE_X + DISTANCE_NUMBER * 3, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber((point/100)%10, x + POSITION_SCORE_X + DISTANCE_NUMBER * 4, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber((point/10)%10, x + POSITION_SCORE_X + DISTANCE_NUMBER * 5, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber(point%10, x + POSITION_SCORE_X + DISTANCE_NUMBER * 6, y - ADJUST_Y_POWER_POSITION_UNDER);

	//times


	int times = mario->GetTimeGame();

	AniNumber(times/100, x + POSITION_CLOCK_X, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber((times/10)%10, x + POSITION_CLOCK_X + DISTANCE_NUMBER, y - ADJUST_Y_POWER_POSITION_UNDER);
	AniNumber(times%10, x + POSITION_CLOCK_X + DISTANCE_NUMBER * 2, y - ADJUST_Y_POWER_POSITION_UNDER);

	//Coin
	int coin; 
	coin = mario->GetCoin();
	if (coin / 10 > 0) {
		AniNumber(coin / 10, x + POSITION_COIN_X, y - ADJUST_Y_POWER_POSITION);
	}
	AniNumber(coin % 10, x + POSITION_COIN_X + DISTANCE_NUMBER, y - ADJUST_Y_POWER_POSITION);

	//M
	CAnimations::GetInstance()->Get(ID_ANI_M_SYMBOL)->Render(x + POSITION_M_SYMBOL_X, y - ADJUST_Y_POWER_POSITION_UNDER - 1);
	
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

//int CHUD_1::getAniId(int num) {
//	switch (num)
//	{
//	case 0:
//		return ID_ANI_0;
//	case 1:
//		return ID_ANI_1;
//	case 2:
//		return ID_ANI_2;
//	case 3:
//		return ID_ANI_3;
//	case 4:
//		return ID_ANI_4;
//	case 5:
//		return ID_ANI_5;
//	case 6:
//		return ID_ANI_6;
//	case 7:
//		return ID_ANI_7;
//	case 8:
//		return ID_ANI_8;
//	case 9:
//		return ID_ANI_9;
//	default:
//		return 0;
//	}
//}

void CHUD_1::AniCard(int n, float Xcard, float Ycard) {

}

//void CHUD_1::WriteTimes() {
//
//	timesgame.clear();
//
//	if (count_down_time >= 1 && count_start != -1) {
//		if (GetTickCount64() - count_start > 1000)
//		{
//			count_start = GetTickCount64();
//			count_down_time--;
//		}
//	}
//
//	int times = this->count_down_time;
//
//	for (int i = 2; i >= 0; i--)
//	{
//		if (i == 0) {
//			timesgame.push_back(times % 10);
//		}
//		else {
//			int time = (int)(times / pow(10, i));
//			timesgame.push_back(times);
//			times = times - (int)(time * pow(10, i));
//		}
//	}
//}

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

