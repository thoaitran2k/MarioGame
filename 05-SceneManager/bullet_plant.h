#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "debug.h"


#define ID_ANI_BULLET_RIGHT 71
#define ID_ANI_BULLET_LEFT 72

#define BULLET_BBOX_WIDTH 9
#define BULLET_BBOX_HEIGHT 9

#define BULLET_SPEED_X 0.05f
#define BULLET_SPEED_Y 0.07f

#define ADJUST_VECTOR_Y 30
#define CHANGE_DIRECTION 30
#define TIME_BULLET_DELETE 4000

#define BULLET_LEFT 701
#define BULLET_RIGHT 702
#define BULLET_ROI_XUONG 703


class Cbullet_plant : public CGameObject
{
	float ax;
	float ay;

	float startX;
	float startY;

		void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
		//ULONGLONG start_deleted;
		//virtual int IsColliable() { return 0; }

	public:
		Cbullet_plant(float x, float y);

		//Cbullet_plant(float bx, float by, bool Left, bool Right);
		virtual void Render();
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual int IsColliable() { return 0; }
		virtual void OnNoCollision(DWORD dt)
		{
			x += vx * dt;
			y += vy * dt;
		}
		virtual void OnCollisionWith(LPCOLLISIONEVENT e);
		virtual void SetState(int state);
		virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};

