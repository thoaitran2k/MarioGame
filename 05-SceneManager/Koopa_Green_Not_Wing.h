#pragma once
#include "GameObject.h"

#define KOOPA_GREEN_NOT_WING_GRAVITY 0.002f
#define KOOPA_GREEN_NOT_WING_WALKING_SPEED 0.05f


#define KOOPA_GREEN_NOT_WING_BBOX_WIDTH 16
#define KOOPA_GREEN_NOT_WING_BBOX_HEIGHT 14
#define KOOPA_GREEN_NOT_WING_BBOX_HEIGHT_DEFEND 7


#define KOOPA_GREEN_NOT_WING_DIE_TIMEOUT 500

#define KOOPA_GREEN_NOT_WING_STATE_WALKING 100
#define KOOPA_GREEN_NOT_WING_STATE_WALKING_LEFT 200
#define KOOPA_GREEN_NOT_WING_STATE_ISDEFEND 300


#define ID_ANI_KOOPA_GREEN_NOT_WING_WALKING_RIGHT 6001
#define ID_ANI_KOOPA_GREEN_NOT_WING_WALKING_LEFT 6002

#define ID_ANI_KOOPA_GREEN_NOT_WING_DEFEND 6003


class CKoopa_Green_Not_Wing : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopa_Green_Not_Wing(float x, float y);
	virtual void SetState(int state);
};

