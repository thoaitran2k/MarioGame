#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK_Q 110000
#define BRICK_Q_WIDTH 16
#define BRICK_Q_BBOX_WIDTH 16
#define BRICK_Q_BBOX_HEIGHT 16
#define BRICK_Q_SPEED_UP 0.04f
#define BRICK_Q_STATE_UP 100
#define BRICK_Q_SPEED_DOWN 0.01f

#define ADJUST_UP_DOWN 13

class CBrickQuestion : public CGameObject {
protected:
	float ay;
	float minY;
	float startX;
	float startY;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CBrickQuestion(float x, float y);
	virtual void SetState(int state);
	void Update(DWORD dt) {}
};
