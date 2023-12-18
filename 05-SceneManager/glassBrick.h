#pragma once

#include "debug.h"
#include "PlayScene.h"
#include "Game.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
//#include "ButtonP.h"


#define ID_ANI_GLASS_BRICK 10124
//#define ID_ANI_GLASS_BRICK_BREAK 10125
#define ID_ANI_BRICK_CONTAIN_BUTTON_P 10103
#define ID_ANI_BREAK_BRICK_TRANSFORM_TO_COIN 110102

#define GLASS_BRICK_BBOX_WIDTH 16
#define GLASS_BRICK_BBOX_HEIGHT 16

#define GLASS_BRICK_MODEL_NORMAL 1
#define GLASS_BRICK_MODEL_CONTAIN_BUTTON 2
#define GLASS_BRICK_MODEL_BREAK 3

#define GLASS_BRICK_STATE_NORMAL 100
#define GLASS_BRICK_STATE_ISTOUCHED 200
#define GLASS_BRICK_STATE_CHANGE_TO_COIN 300
#define GLASS_BRICK_STATE_BREAK 400





class CglassBrick : public CGameObject
{
	int mode;
	int notCoin;
	bool mario_collis;

	float ay;
	float vy;
	//float vx;

	bool unBox;
	bool Empty;
	ULONGLONG timming;


	virtual void OnNoCollision(DWORD dt);

	//CButtonP* p;

	
	
		/*void Add_button(CGameObject* obj) {
		if (!dynamic_cast<CButtonP*>(obj)) return;
		else if (!p)
		{
			CButtonP* button = dynamic_cast<CButtonP*>(obj);
			p = button;
			DebugOut(L">>> ADD OBJECT BUTTON P >>> \n");
		}
		}*/



	

	

public:
	
	CglassBrick(float x, float y, int mode);

	//void SetButtonP(CButtonP* b) { b = p; }

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void GetBoundingBox(float& l, float& t, float& r, float& b);

	bool GetCollision() { return mario_collis; }

	void SetCollision(bool b) { b = mario_collis; }

	bool GetUnBox() { return unBox; }

	bool GetEmpty() { return Empty; }

	void SetUnBox(bool b) { b = unBox; }

	void SetEmpty(bool b) { b = Empty; }

	

	virtual void SetState(int state);

	int IsBlocking() { return notCoin; }

	int GetModel() { return mode; }

	
	//void CreateButtonP() {
	//	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	//	if (unBox)
	//	{
	//		CGameObject* p = scene->CreateObjectAndReturn(OBJECT_TYPE_GREEN_KOOPA_WALKING, x, y - 16, 0, 0);
	//		Add_button(p);
	//	}

	//}

};

