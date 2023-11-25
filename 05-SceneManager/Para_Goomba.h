#pragma once
#include "GameObject.h"
#include "AssetIDs.h"
#include "debug.h"

#define PARA_GOOMBA_GRAVITY 0.05f
#define PARA_GOOMBA_WALKING_SPEED 0.003f


#define PARA_GOOMBA_BBOX_WIDTH 16
#define PARA_GOOMBA_BBOX_HEIGHT 16
#define PARA_GOOMBA_BBOX_HEIGHT_DIE 10

#define PARA_GOOMBA_STATE_WALKING 100
#define PARA_GOOMBA_STATE_FLY 200
#define GOOMBA_RED_STATE_DIE 300
#define GOOMBA_RED_STATE_WALKING 300

#define TIME_WALKING 2000



#define GOOMBA_RED_DIE_TIMEOUT 500


#define ID_ANI_GOOMBA_RED_FLY_WALKING 5005
#define ID_ANI_GOOMBA_RED_FLY_JUMP 5006



class CPara_Goomba : public CGameObject
{
protected:
	float ax;
	float ay;
	float minY;

	ULONGLONG walking_time;

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
	virtual void SetState(int state);
};

