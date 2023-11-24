#pragma once
#include "GameObject.h"

#define KOOPA_RED_GRAVITY 0.002f
#define KOOPA_RED_WALKING_SPEED 0.05f


#define KOOPA_RED_BBOX_WIDTH 16
#define KOOPA_RED_BBOX_HEIGHT 16
#define KOOPA_RED_BBOX_HEIGHT_DEFEND 7


#define KOOPA_RED_DIE_TIMEOUT 500

#define KOOPA_RED_STATE_WALKING 100
#define KOOPA_RED_STATE_WALKING_LEFT 200
#define KOOPA_RED_STATE_ISDEFEND 300
#define KOOPA_RED_STATE_ISKICKED 400


#define ID_ANI_KOOPA_RED_WALKING_RIGHT 6101
#define ID_ANI_KOOPA_RED_WALKING_LEFT 6102
#define ID_ANI_KOOPA_RED_DEFEND 6103


class CRed_Koopa : public CGameObject
{
protected:
	float ax;
	float ay;

	bool isTurtleShell;
	bool isCollis;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	int LeftOrRightMarrio();
	
	virtual int IsCollidable() { return 1;}
	virtual int IsColliswithMario() { return isCollis; }
	//virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:

	bool GetIsTurtleShell() { return isTurtleShell; }
	bool GetIsCollis() { return isCollis; }

	

	CRed_Koopa(float x, float y);
	virtual void SetState(int state);
};



