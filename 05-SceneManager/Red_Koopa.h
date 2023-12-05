#pragma once
#include "GameObject.h"
#include "CheckKoopaFall.h"
#include "debug.h"


//speeds
#define KOOPA_RED_GRAVITY 0.002f
#define KOOPA_RED_WALKING_SPEED 0.015f
#define SPEED_KOOPA_RED_TURTLESHELL_IS_KICKED 0.25f


//bbox
#define KOOPA_RED_BBOX_WIDTH 16
#define KOOPA_RED_BBOX_HEIGHT 16
#define KOOPA_RED_BBOX_HEIGHT_TURTLESHELL 7

//times
#define KOOPA_RED_DIE_TIMEOUT 500
#define DISTANCE_MIN_SHELL_EXIST 150
#define TURTLE_SHELL_TIMEOUT 4000
#define TURTLE_SHELL_TOTURN_KOOPA 4000
#define TIME_COMBACK_KOOPA 1500

//States
#define KOOPA_RED_STATE_WALKING 100
#define KOOPA_RED_STATE_WALKING_LEFT 200
#define KOOPA_RED_STATE_WALKING_RIGHT 600
#define KOOPA_RED_STATE_ISTURTLESHELL 300
#define KOOPA_RED_STATE_ISKICKED 400
#define KOOPA_RED_STATE_TO_RETURN 450
#define KOOPA_RED_WALKING_STATE_TURN 460
#define KOOPA_RED_STATE_WAIT_RESET 470

//Ani_id
#define ID_ANI_KOOPA_RED_WALKING_RIGHT 6101
#define ID_ANI_KOOPA_RED_WALKING_LEFT 6102
#define ID_ANI_KOOPA_RED_TURTLESHELL 6103
#define ID_ANI_KOOPA_RED_ISKICKED_LEFT_TO_RIGHT 6104
#define ID_ANI_KOOPA_RED_ISKICKED_RIGHT_TO_LEFT 6401
#define ID_ANI_RED_KOOPA_COMBACK 6106


class CRed_Koopa : public CGameObject
{
protected:
	float ax;
	float ay;

	float startX;
	float startY;

	CCheckFall* checkfall;
	CRed_Koopa* newkoopa;

	bool isTurtleShell;
	bool isKicked;
	bool isOnPlatform;
	bool HaveOrNotCheckFall;
	bool isComback;
	bool wasKicked;
	bool isDead;
	bool isTurn;
	bool wasHeld;

	ULONGLONG count_start;
	ULONGLONG comback_time;
	ULONGLONG time_delete;
	ULONGLONG time_rs;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	int LeftOrRightMarrio();

	

	void CreateCheckfall();

	void CreateNewKoopa();
	
	virtual int IsCollidable() { return 1;}
	//virtual int IsColliswithMario() { return isCollis; }
	virtual int IsBlocking() { return 0; }
	
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick_Question(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);



public:
	ULONGLONG GetTimeComback() { return comback_time; }

	ULONGLONG GetTimeDelete() { return time_delete; }


	bool GetIsKick() { return isKicked; }

	bool GetIsTurtleShell() { return isTurtleShell; }

	bool GETwasKicked() { return wasKicked; }

	bool GetIsComback() { return isComback; }
	
	bool GetisDeleted() { return isDeleted; }
	//bool GetIsCollis() { return isCollis; }

	int DistanceTurtleShellisKickedWithMario();
	

	void Addnew_koopa(CGameObject* obj) {
		if (!dynamic_cast<CRed_Koopa*>(obj)) return;
		else if (!newkoopa)
		{
			CRed_Koopa* newKP = dynamic_cast<CRed_Koopa*>(obj);
			newkoopa = newKP;
			DebugOut(L">>> check tao bullet >>> \n");

		}
	}

	void ResetKP()
	{
		if(newkoopa) newkoopa->Delete();
		newkoopa = NULL;
	}



	void AddCheck(CGameObject* obj) {
		if (!dynamic_cast<CCheckFall*>(obj)) return;
		else if (!checkfall )
		{
			CCheckFall* cfall_obj = dynamic_cast<CCheckFall*>(obj);
			checkfall = cfall_obj;
			DebugOut(L">>> check >>> \n");
			
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



