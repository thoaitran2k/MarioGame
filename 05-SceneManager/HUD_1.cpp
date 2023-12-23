#include "HUD_1.h"
#include"PlayScene.h"
#include "Mario.h"

CHUD_1* CHUD_1::__instance = NULL;

CHUD_1* hud = NULL;
vector<LPGAMEOBJECT> objects;

CHUD_1* CHUD_1::GetInstance() {
	if (__instance == NULL) __instance = new CHUD_1(0, 0);
	return __instance;
}

void CHUD_1::Render() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	CAnimations::GetInstance()->Get(ID_ANI_BLACK_RECTANGEL)->Render(x, y);

	CAnimations::GetInstance()->Get(ID_ANI_HUD)->Render(x, y);

	AniNumber(1, x + POSITION_WORLD_X, y - ADJUST_Y_POWER_POSITION);

	
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

void CHUD_1::LoadHUD() {
	hud = new CHUD_1(1209, 408);
	objects.push_back(hud);
}

void CHUD_1::RenderBoundingBox() {
	
}