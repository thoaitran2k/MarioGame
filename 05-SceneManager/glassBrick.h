#pragma once

#include "debug.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_GLASS_BRICK 10124
#define ID_ANI_BRICK_CONTAIN_BUTTON_P 10103
#define ID_ANI_BREAK_BRICK_TRANSFORM_TO_COIN 110102

#define GLASS_BRICK_BBOX_WIDTH 16
#define GLASS_BRICK_BBOX_HEIGHT 16

#define GLASS_BRICK_MODEL_NORMAL 1
#define GLASS_BRICK_MODEL_CONTAIN_BUTTON 2

#define GLASS_BRICK_STATE_NORMAL 100
#define GLASS_BRICK_STATE_ISTOUCHED 200
#define GLASS_BRICK_STATE_CHANGE_TO_COIN 300




class CglassBrick : public CGameObject
{
	int mode;
	int notCoin;
	bool mario_collis;

	bool unBox;
	bool Empty;
	ULONGLONG timming;

public:
	CglassBrick(float x, float y, int mode);

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void GetBoundingBox(float& l, float& t, float& r, float& b);

	bool GetCollision() { return mario_collis; }

	void SetCollision(bool b) { b = mario_collis; }

	bool GetUnBox() { return unBox; }

	bool GetEmpty() { return Empty; }

	virtual void SetState(int state);

	int IsBlocking() { return notCoin; }

	float GetModel() { return mode; }

};

