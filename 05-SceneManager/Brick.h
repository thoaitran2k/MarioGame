#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_BRICK_2 10002
#define ID_ANI_BRICK_WHITE_SMILE 10003

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define MODEL_BASIC	1
#define MODEL_BASIC_2 2
#define MODEL_WHITE_SMILE 3

#define modehithox 77


class CBrick : public CGameObject {

protected:
	int model;

public:
	CBrick(float x, float y, int model) : CGameObject(x, y) {
		this->model = model;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void OnCollisionWithKoopa(LPCOLLISIONEVENT e);
};