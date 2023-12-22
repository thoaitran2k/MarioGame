#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_MAP 999999
//#define ID_ANI_HIDEN_MAP 999991

//#define MODE_1	1
//#define MODE_1_1	2

#define MAP_WIDTH 16
#define MAP_BBOX_WIDTH 16
#define MAP_BBOX_HEIGHT 16

class CMap : public CGameObject {
public:
	CMap(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};
