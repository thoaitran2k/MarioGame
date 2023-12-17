#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "glassBrick.h"



#define ID_ANI_BUTTON_P 10126
#define ID_ANI_BUTTON_P_COL 10127

#define BUTTON_BBOX_WIDTH 10
#define BUTTON_BBOX_HEIGHT 16

#define BUTTON_STATE_BE_COLLIDABLED	100

class CButtonP :public CGameObject
{

	//CglassBrick* glassbrick;

	//void Change_Coin(CGameObject* obj) {
	//	if (!dynamic_cast<CglassBrick*>(obj)) return;
	//		else if (!glassbrick)
	//		{
	//		CglassBrick* coin = dynamic_cast<CglassBrick*>(obj);
	//		glassbrick = coin;
	//		DebugOut(L">>> ADD OBJECT BUTTON P >>> \n");
	//		}
	//	}
	//

public:
	
	/*void BrickToCoin();*/

	CButtonP(float x, float y);
	void Render();
	void Update(DWORD dt) {};

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }

	void SetState(int state);

	//void ChangeToCoin() {
	//	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	//	
	//	//scene->AddObject(glassbrick);

	//	//glassbrick->SetState(GLASS_BRICK_STATE_CHANGE_TO_COIN);
	//	
	//		//CGameObject* coin = scene->CreateObjectAndReturn(OBJECT_TYPE_GLASS_BRICK_CHANGETO_COIN, x-16, y - 16, 0, 0);
	//		//Change_Coin(coin);
	//		//glassbrick->Delete();
	//	

	//}

	/*void Reset() {
		if (glassbrick) glassbrick->Delete();
	}*/

	

};

