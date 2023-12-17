#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_BUTTON_P 10126
#define ID_ANI_BUTTON_P_COL 10127

#define BUTTON_BBOX_WIDTH 10
#define BUTTON_BBOX_HEIGHT 16

#define BUTTON_STATE_BE_COLLIDABLED	100

class CButtonP :public CGameObject
{
public:
	CButtonP(float x, float y);
	void Render();
	void Update(DWORD dt) {};

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }

	void SetState(int state);

};

