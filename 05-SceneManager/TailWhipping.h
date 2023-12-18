#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_TAIL_WHIPPING	3070		

#define SPEED_WHIP 0.1f
#define SPEED_WHIP_LEFT 0.1f

#define BBOX_WIDTH	12
#define BBOX_HEIGHT	4
#define	WIDTH		10

#define WHIP_STATE_DELETE	100
#define WHIP_STATE_LEFT_MARIO	200
#define WHIP_STATE_RIGHT_MARIO	300

class CTailWhipping : public CGameObject
{
protected:

	bool attack;
	bool attackBrick;

	ULONGLONG timming;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithGlassBrick(LPCOLLISIONEVENT e);


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





