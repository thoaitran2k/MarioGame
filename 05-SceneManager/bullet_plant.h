#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "debug.h"


#define ID_ANI_BULLET_RIGHT 71
#define ID_ANI_BULLET_LEFT 72
#define ID_ANI_BULLET_BLUE 73


#define BULLET_BBOX_WIDTH 9
#define BULLET_BBOX_HEIGHT 9

#define BULLET_BLUE_BBOX_WIDTH 12
#define BULLET_BLUE_BBOX_HEIGHT 12

#define BULLET_SPEED_X 0.05f
#define BULLET_SPEED_Y 0.07f

#define ADJUST_VECTOR_Y 30
#define CHANGE_DIRECTION 30
#define TIME_BULLET_DELETE 4000

#define BULLET_LEFT 701
#define BULLET_RIGHT 702
#define BULLET_ROI_XUONG 703


class CbulletPlant : public CGameObject {

protected:
		float ax;
		float ay;

		float startY;
		float startX;


		virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
		void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
		virtual int IsCollidable() { return 1; };
		virtual int IsBlocking() { return 0; }
		virtual void OnNoCollision(DWORD dt);

		virtual void OnCollisionWith(LPCOLLISIONEVENT e);
		//ULONGLONG start_deleted;
		//virtual int IsColliable() { return 0; }

	public:

		CbulletPlant(float x, float y);

		//Cbullet_plant(float bx, float by, bool Left, bool Right);

		void Render();
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	


		virtual void SetState(int state);

};

