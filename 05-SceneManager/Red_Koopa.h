#pragma once
#include "GameObject.h"
#include "CheckKoopaFall.h"
#include "debug.h"

#define KOOPA_RED_GRAVITY 0.002f
#define KOOPA_RED_WALKING_SPEED 0.015f
#define SPEED_KOOPA_RED_TURTLESHELL_IS_KICKED 0.025f



#define KOOPA_RED_BBOX_WIDTH 16
#define KOOPA_RED_BBOX_HEIGHT 16
#define KOOPA_RED_BBOX_HEIGHT_DEFEND 7


#define KOOPA_RED_DIE_TIMEOUT 500

#define KOOPA_RED_STATE_WALKING 100
#define KOOPA_RED_STATE_WALKING_LEFT 200
#define KOOPA_RED_STATE_WALKING_RIGHT 600
#define KOOPA_RED_STATE_ISDEFEND 300
#define KOOPA_RED_STATE_ISKICKED 400
#define KOOPA_RED_STATE_TO_RETURN 450


#define ID_ANI_KOOPA_RED_WALKING_RIGHT 6101
#define ID_ANI_KOOPA_RED_WALKING_LEFT 6102
#define ID_ANI_KOOPA_RED_DEFEND 6103
#define ID_ANI_KOOPA_RED_ISKICKED_LEFT_TO_RIGHT 6104
#define ID_ANI_KOOPA_RED_ISKICKED_RIGHT_TO_LEFT 6401
#define ID_ANI_RED_KOOPA_COMBACK 6106


class CRed_Koopa : public CGameObject
{
protected:
	float ax;
	float ay;

	float startX;

	CCheckFall* checkfall;

	bool isTurtleShell;
	bool isKicked;
	bool isOnPlatform;
	bool HaveOrNotCheckFall;
	bool isComback;
	bool wasKicked;
	bool isDead;

	ULONGLONG count_start;
	ULONGLONG comback_time;

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
	ULONGLONG GetTimeComback() { return comback_time; }

	bool GetIsKick() { return isKicked; }

	bool GetIsTurtleShell() { return isTurtleShell; }

	bool GETwasKicked() { return wasKicked; }

	bool GetIsComback() { return isComback; }
	//bool GetIsCollis() { return isCollis; }

	

	void AddCheck(CGameObject* obj) {
		if (!dynamic_cast<CCheckFall*>(obj)) return;
		else if (!checkfall )
		{
			CCheckFall* cfall_obj = dynamic_cast<CCheckFall*>(obj);
			checkfall = cfall_obj;
			DebugOut(L">>> check >>> \n");
			


			//checkfall->isOnPlatformCheck = true;
		}
	}

	void ResetCheck()
	{
		if(checkfall) checkfall->Delete();
			checkfall = NULL;
	}
	
	void DeleteCheck()
	{
		checkfall->GetDeleted();
	}
	
	
	
	
	

	CRed_Koopa(float x, float y);
	virtual void SetState(int state);
};



