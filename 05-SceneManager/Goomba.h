#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_THROWN_BY_KOOPA 300
#define GOOMBA_STATE_DIE_UPSIDE 400

#define GOOMBA_BASIC 1
#define GOOMBA_RED 2
#define GOOMBA_UNDER_KOOPA 3



#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

#define ID_ANI_GOOMBA_RED 5003
#define ID_ANI_GOOMBA_RED_DIE 5004
#define ID_ANI_GOOMBA_DIE_UPSIDE 5007
#define ID_ANI_GOOMBA_UPSIDE 5008

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay;
	float range;
	int model;
	ULONGLONG die_start;



	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	


	void SetIsBlocking(int b) { b; }
	CGoomba(float x, float y, int model);

	void SetModel(int model) { this->model = model; }
	int GetModel() { return model; }
	virtual void SetState(int state);

};