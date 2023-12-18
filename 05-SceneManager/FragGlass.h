#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_GLASS_BRICK_BREAK 10125

#define GRAVITY 0.00075f

#define FRAG_BBOX_WIDTH 4
#define FRAG_BBOX_HEIGHT 4

#define SPEED_Y 0.35f
#define SPEED_X 0.04f

#define STATE_BREAK	100

class CFragGlass :public CGameObject
{
	float vx, vy;
	float ay, ax;

	ULONGLONG time;
public:
	CFragGlass(float x, float y, float vx, float vy);

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnNoCollision(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual void SetState(int state);

};

