#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BIN1 777
#define BIN1_WIDTH 48
#define BIN1_BBOX_WIDTH 48
#define BIN1_BBOX_HEIGHT 48


class CBin1 : public CGameObject {
public:



	CBin1(float x, float y) : CGameObject(x, y) {}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};