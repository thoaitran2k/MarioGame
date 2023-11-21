#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "debug.h"





#define ID_ANI_MUSHROOM 99



#define MUSHROOM_GRAVITY 0.001f
#define MUSHROOM_SPEED 0.055f
#define OUT_BRICK -0.016f
#define	MUSHROOM_WIDTH 10
#define MUSHROOM_BBOX_WIDTH 10
#define MUSHROOM_BBOX_HEIGHT 16
#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_OUTSIDE 200

class CMushRoom : public CGameObject {
	float ax;
	float ay;
	float startY;

	
	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);

public:
	CMushRoom(float x, float y);
	
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual int IsCollidable() { return 1; }
	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);


	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual void SetState(int state);
};

