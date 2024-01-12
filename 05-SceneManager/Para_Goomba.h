#pragma once
#include "GameObject.h"
#include "AssetIDs.h"
#include "debug.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Game.h"


//speed
#define PARA_GOOMBA_GRAVITY 0.0005f
#define PARA_GOOMBA_WALKING_SPEED 0.025f
#define SPEED_PARA_GOOMBA_FLY 0.22f
#define SPEED_GOOMBA_RED_WALKING 0.05f

//bbox
#define PARA_GOOMBA_BBOX_WIDTH 16
#define PARA_GOOMBA_BBOX_HEIGHT 16
#define PARA_GOOMBA_BBOX_HEIGHT_DIE 10
#define GOOMBA_RED_BBOX_HEIGHT 14
#define GOOMBA_RED_BBOX_HEIGHT_DIE 7

//states
#define PARA_GOOMBA_STATE_WALKING 100
#define PARA_GOOMBA_STATE_FLY 200
#define GOOMBA_RED_STATE_DIE 300
#define GOOMBA_RED_STATE_WALKING 400
#define GOOMBA_RED_STATE_FALL 500
#define GOOMBA_RED_STATE_BE_WHIPED 600
#define PARA_STATE_BE_WHIPED 700

//times
#define TIME_WALKING 2000
#define GOOMBA_RED_DIE_TIMEOUT 200
#define PARA_GOOMBA_WALKING_TIME 1500


#define ID_ANI_GOOMBA_RED_FLY_WALKING 5005
#define ID_ANI_GOOMBA_RED_FLY_JUMP 5006
#define ID_ANI_GOOMBA_RED 5003
#define ID_ANI_GOOMBA_RED_DIE 5004
#define ID_ANI_GOOMBA_RED_DIE_UPSIDE 50007




class CPara_Goomba : public CGameObject
{
protected:

	float startX;
	float startY;

	float ax;
	float ay;
	float minY;

	CPara_Goomba* para;

	ULONGLONG count_start;
	ULONGLONG die_start_red_goomba;
	ULONGLONG die_start_red_goomba_upside;
	ULONGLONG time_appear;
	ULONGLONG time_whip;


	bool isOnPlatForm;
	bool isFly;
	bool isActive;
	bool beWhip;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);


	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void Para_Goomba_Appear();
	
	void Para_Goomba_Active() {
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

		if (abs(mario->GetX() - x) < 150)
			isActive = true;
	}
 
public:


	void AddPara_Goomba(CGameObject* obj) {
		if (!dynamic_cast<CPara_Goomba*>(obj)) return;
		if (!para)
		{
			CPara_Goomba* para_appaear = dynamic_cast<CPara_Goomba*>(obj);
			para = para_appaear;
			DebugOut(L">>> PARA GOOMBA XUAT HIEN >>> \n");

		}
	}

	void ResetKP()
	{
		if (para) para->Delete();
		para = NULL;
	}




	CPara_Goomba(float x, float y);
	bool IsFly() { return isFly; }
	void SetIsFly(bool b) { b = isFly; }
	bool GetActive() { return isActive; }
	virtual void SetState(int state);
};

