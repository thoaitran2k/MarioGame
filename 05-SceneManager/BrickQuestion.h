#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK_Q 113000

#define BRICK_Q_WIDTH 16
#define BRICK_Q_BBOX_WIDTH 16
#define BRICK_Q_BBOX_HEIGHT 16
#define BRICK_Q_SPEED_UP 0.04f
#define BRICK_Q_STATE_UP 100
#define BRICK_Q_SPEED_DOWN 0.01f
#define QUESTION_BRICK_STATE_UP 100
#define QUESTION_BRICK_SPEED_UP 0.04f

#define QUESTION_BRICK_COIN 1
#define QUESTION_BRICK_ITEM 2

#define ADJUST_UP_DOWN 13

class CBrickQuestion : public CGameObject {

protected:
	float ay;

	float minY;
	float startY;
	float startX;
	int model;
	BOOLEAN isUnbox = false;
	BOOLEAN isEmpty = false;

	

	virtual void Render();
	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 1; }
	virtual void OnNoCollision(DWORD dt);
	

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CBrickQuestion(float x, float y) : CGameObject(x, y) {}

	CBrickQuestion(float x, float y, int model);

	

	BOOLEAN GetIsUnbox() { return isUnbox; }
	BOOLEAN GetIsEmpty() { return isEmpty; }
	virtual void SetState(int state);
	void SetIsUnbox(BOOLEAN b) { isUnbox = b; }
	void SetIsEmpty(BOOLEAN b) { isEmpty = b; }
	void SetModel(int model) { this->model = model; }
	int GetModel() { return model; }

	
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	float GetMinY() { return minY; }
	CGameObject* item = NULL;
};