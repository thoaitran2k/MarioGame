#pragma once
#include "GameObject.h"
#include "AssetIDs.h"
#include "debug.h"


//speed
#define PARA_GOOMBA_GRAVITY 0.0005f
#define PARA_GOOMBA_WALKING_SPEED 0.025f
#define SPEED_PARA_GOOMBA_FLY 0.18f
#define SPEED_GOOMBA_RED_WALKING 0.05f

//bbox
#define PARA_GOOMBA_BBOX_WIDTH 16
#define PARA_GOOMBA_BBOX_HEIGHT 16
#define PARA_GOOMBA_BBOX_HEIGHT_DIE 10
#define GOOMBA_RED_BBOX_HEIGHT 14

//states
#define PARA_GOOMBA_STATE_WALKING 100
#define PARA_GOOMBA_STATE_FLY 200
#define GOOMBA_RED_STATE_DIE 300
#define GOOMBA_RED_STATE_WALKING 400
#define GOOMBA_RED_STATE_FALL 500

//times
#define TIME_WALKING 2000
#define GOOMBA_RED_DIE_TIMEOUT 500
#define PARA_GOOMBA_WALKING_TIME 1500


#define ID_ANI_GOOMBA_RED_FLY_WALKING 5005
#define ID_ANI_GOOMBA_RED_FLY_JUMP 5006
#define ID_ANI_GOOMBA_RED 5003
#define ID_ANI_GOOMBA_RED_DIE 5004




class CPara_Goomba : public CGameObject
{
protected:
	float ax;
	float ay;
	float minY;

	ULONGLONG count_start;
	ULONGLONG die_start_red;
	ULONGLONG time_appear;


	bool isOnPlatForm;
	bool isFly;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);


	virtual void OnCollisionWith(LPCOLLISIONEVENT e);



public:


	CPara_Goomba(float x, float y);
	bool IsFly() { return isFly; }
	virtual void SetState(int state);
};

