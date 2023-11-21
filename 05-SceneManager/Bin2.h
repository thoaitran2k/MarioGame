#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_BIN2 778
#define BIN2_WIDTH 16
#define BIN2_BBOX_WIDTH 48
#define BIN2_BBOX_HEIGHT 13

class CBin2 : public CGameObject {
public:

	virtual void OnNoCollision(DWORD dt);


	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	CBin2(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

