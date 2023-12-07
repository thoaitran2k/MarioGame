#pragma once
#include "GameObject.h"
#include "CheckKoopaFall.h"
#include "debug.h"
#include "Goomba.h"


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
#define KOOPA_RED_STATE_BE_HELD 478

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
	CGoomba* goomba_under_koopa;
	


	
	bool isTurtleShell;
	bool isKicked;
	bool isOntheBox;
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

	void CreateGoomba();
	
	virtual int IsCollidable() { return 1;}
	//virtual int IsColliswithMario() { return isCollis; }
	virtual int IsBlocking() { return 0; }
	
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick_Question(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithOntheBox(LPCOLLISIONEVENT e);



public:
	ULONGLONG GetTimeComback() { return comback_time; }

	ULONGLONG GetTimeDelete() { return time_delete; }


	bool GetIsKick() { return isKicked; }

	bool GetIsTurtleShell() { return isTurtleShell; }

	bool GETwasKicked() { return wasKicked; }

	bool GetIsComback() { return isComback; }
	
	bool GetisDeleted() { return isDeleted; }

	bool GetwasHeld() { return wasHeld; }

	bool GetisOntheBox() { return isOntheBox; }
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

	void AddGoomba(CGameObject* obj) {
		if (!dynamic_cast<CGoomba*>(obj)) return;
		else if (!goomba_under_koopa)
		{
			CGoomba* under_goomba = dynamic_cast<CGoomba*>(obj);
			goomba_under_koopa = under_goomba;
			DebugOut(L">>> Create Goomba phia duoi con koopa >>> \n");
		}
	}

	void checknullGB()
	{
		if (goomba_under_koopa) goomba_under_koopa->Delete();
		goomba_under_koopa = NULL;
	}
	
	
	
	
	

	CRed_Koopa(float x, float y);
	virtual void SetState(int state);
};



