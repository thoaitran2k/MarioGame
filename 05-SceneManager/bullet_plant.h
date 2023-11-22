#pragma once
#include "GameObject.h"


#define ID_ANI_BULLET_RIGHT 71
#define ID_ANI_BULLET_LEFT 72

#define BULLET_BBOX_WIDTH 9
#define BULLET_BBOX_HEIGHT 9

#define BULLET_SPEED_X 0.05f
#define BULLET_SPEED_Y 0.07f

#define ADJUST_VECTOR_Y 30
#define CHANGE_DIRECTION 30
#define TIME_BULLET_DELETE 4000



class Cbullet_plant : public CGameObject
{
	protected:
		float ay;
		float ax;
		//ULONGLONG start_deleted;
		//virtual int IsColliable() { return 0; }

	public:
		ULONGLONG start_deleted;
		Cbullet_plant(float x, float y);
		virtual int IsColliable() { return 1; }
		//Cbullet_plant(float x, float y) : CGameObject(x, y) {}
			//,bool Up, bool Right);
		virtual void Render();
		//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual void OnNoCollision(DWORD dt)
		{
			x += vx * dt;
			y += vy * dt;
		}
		virtual void OnCollisionWith(LPCOLLISIONEVENT e);
		virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};

