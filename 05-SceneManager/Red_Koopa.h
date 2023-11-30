#pragma once
#include "GameObject.h"
#include "CheckKoopaFall.h"
#include "debug.h"

#define KOOPA_RED_GRAVITY 0.002f
#define KOOPA_RED_WALKING_SPEED 0.015f


#define KOOPA_RED_BBOX_WIDTH 16
#define KOOPA_RED_BBOX_HEIGHT 16
#define KOOPA_RED_BBOX_HEIGHT_DEFEND 7


#define KOOPA_RED_DIE_TIMEOUT 500

#define KOOPA_RED_STATE_WALKING 100
#define KOOPA_RED_STATE_WALKING_LEFT 200
#define KOOPA_RED_STATE_WALKING_RIGHT 600
#define KOOPA_RED_STATE_ISDEFEND 300
#define KOOPA_RED_STATE_ISKICKED 400


#define ID_ANI_KOOPA_RED_WALKING_RIGHT 6101
#define ID_ANI_KOOPA_RED_WALKING_LEFT 6102
#define ID_ANI_KOOPA_RED_DEFEND 6103


class CRed_Koopa : public CGameObject
{
protected:
	float ax;
	float ay;

	float startX;

	CCheckFall* checkfall;

	bool isTurtleShell;
	//bool isCollis;
	bool isOnPlatform;
	bool HaveOrNotCheckFall;

	ULONGLONG count_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	int LeftOrRightMarrio();

	void CreateCheckfall();
	
	virtual int IsCollidable() { return 1;}
	//virtual int IsColliswithMario() { return isCollis; }
	//virtual int IsBlocking() { return 0; }
	
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
	void OnCollisionWithCheckFall(LPCOLLISIONEVENT e);

public:

	bool GetIsTurtleShell() { return isTurtleShell; }
	//bool GetIsCollis() { return isCollis; }

	

	void AddCheck(CGameObject* obj) {
		if (!dynamic_cast<CCheckFall*>(obj)) return;
		else if (!checkfall)
		{
			CCheckFall* cfall_obj = dynamic_cast<CCheckFall*>(obj);
			checkfall = cfall_obj;
			DebugOut(L">>> check >>> \n");
			


			//checkfall->isOnPlatformCheck = true;
		}
	}

	void ResetCheck()
	{
			checkfall->Delete();
			checkfall = NULL;
	}
	
	
	
	
	
	

	CRed_Koopa(float x, float y);
	virtual void SetState(int state);
};



