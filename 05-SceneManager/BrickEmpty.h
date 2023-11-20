#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK_EMPTY 13000
#define BRICK_EMPTY_WIDTH 16
#define BRICK_EMPTY_BBOX_WIDTH 16
#define BRICK_EMPTY_BBOX_HEIGHT 16

class CBrickEmpty : public CGameObject {
public:
	CBrickEmpty(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};