#pragma once
#include "GameObject.h"


#define ID_ANI_BULLET_RIGHT 222
#define ID_ANI_BULLET_LEFT 333

#define BULLET_BBOX_WIDTH 9
#define BULLET_BBOX_HEIGHT 9

#define BULLET_SPEED_X 0.05f
#define BULLET_SPEED_Y 0.07f

#define ADJUST_VECTOR_Y 30
#define CHANGE_DIRECTION 30
#define TIME_BULLET_DELETE 4000



class Cbullet_plant : public CGameObject
{
	//protected:
		//ULONGLONG start_deleted;
		//virtual int IsColliable() { return 0; }

	public:
		Cbullet_plant(float x, float y, bool Up, bool Right);
		//virtual void Render();
		//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		//virtual void OnNoCollision(DWORD dt)
		//{
			//x += vx * dt;
			//y += vy * dt;
		//}
		//virtual void OnCollisionWith(LPCOLLISIONEVENT e);
		virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};

