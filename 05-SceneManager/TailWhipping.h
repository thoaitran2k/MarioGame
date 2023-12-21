#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_TAIL_WHIPPING	3070
#define ID_ANI_GLASS_BRICK_BREAK 10125

#define SPEED_WHIP 0.07f
#define SPEED_WHIP_LEFT 0.07f

#define BBOX_WIDTH	12
#define BBOX_HEIGHT	4
#define	WIDTH		10

#define WHIP_STATE_DELETE	100
#define WHIP_STATE_LEFT_MARIO	200
#define WHIP_STATE_RIGHT_MARIO	300
#define WHIP_STATE_BREAK_BRICK	400

class CTailWhipping : public CGameObject
{
protected:

	bool attack;
	bool attackBrick;

	ULONGLONG timming;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithGlassBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGreenPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithGreen_Koopa(LPCOLLISIONEVENT e);
	void OnCollisionWithRed_Koopa(LPCOLLISIONEVENT e);


public:
	CTailWhipping(float x, float y);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	void SetResetWhip(bool b) { b = attackBrick; }

	virtual int IsCollidable() { return 1; };

	bool GetTailAttack() { return attack; }

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void SetState(int state);

	bool GetDelete() { return isDeleted; }
};





