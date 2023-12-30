#pragma once
#include "GameObject.h"
#include "CheckKoopaFall.h"
#include "debug.h"
#include "Goomba.h"
#include "Mario.h"

#define KOOPA_GREEN_NOT_WING_GRAVITY 0.002f
#define KOOPA_GREEN_NOT_WING_WALKING_SPEED 0.05f

////speeds
//#define KOOPA_GREEN_GRAVITY 0.002f
//#define KOOPA_GREEN_WALKING_SPEED 0.015f
//#define SPEED_KOOPA_GREEN_TURTLESHELL_IS_KICKED 0.25f


#define KOOPA_GREEN_NOT_WING_BBOX_WIDTH 16
#define KOOPA_GREEN_NOT_WING_BBOX_HEIGHT 20
#define KOOPA_GREEN_NOT_WING_BBOX_HEIGHT_DEFEND 7


//TYPE
#define WING 1
#define NOT_WING 2

////bbox
//#define KOOPA_GREEN_BBOX_WIDTH 16
//#define KOOPA_GREEN_BBOX_HEIGHT 16
//#define KOOPA_GREEN_BBOX_HEIGHT_TURTLESHELL 7


////times
//#define KOOPA_GREEN_DIE_TIMEOUT 500
//#define DISTANCE_MIN_SHELL_EXIST 150
//#define TURTLE_SHELL_TIMEOUT 4000
//#define TURTLE_SHELL_TOTURN_KOOPA 4000
//#define TIME_COMBACK_KOOPA 1500
//
//#define KOOPA_GREEN_NOT_WING_DIE_TIMEOUT 500




////States
//#define KOOPA_GREEN_STATE_WALKING 100
//#define KOOPA_GREEN_STATE_WALKING_LEFT 200
//#define KOOPA_GREEN_STATE_WALKING_RIGHT 600
//#define KOOPA_GREEN_STATE_ISTURTLESHELL 300
//#define KOOPA_GREEN_STATE_ISKICKED 400
//#define KOOPA_GREEN_STATE_TO_RETURN 450
//#define KOOPA_GREEN_WALKING_STATE_TURN 460
//#define KOOPA_GREEN_STATE_WAIT_RESET 470
//#define KOOPA_GREEN_STATE_BE_HELD 478
//#define KOOPA_GREEN_STATE_JUMP_RIGHT 500
//#define KOOPA_GREEN_STATE_JUMP_LEFT 510
//#define KOOPA_GREEN_STATE_FALL 520



////Ani_id
//#define ID_ANI_KOOPA_GREEN_NOT_WING_WALKING_RIGHT 6001
//#define ID_ANI_KOOPA_GREEN_NOT_WING_WALKING_LEFT 6002
//#define ID_ANI_KOOPA_GREEN_NOT_WING_TURTLESHELL 6003
//#define ID_ANI_GREEN_KOOPA_ISKICKED_LEFT_TO_RIGHT 6004
//#define ID_ANI_GREEN_KOOPA_ISKICKED_RIGHT_TO_LEFT 6400
//#define ID_ANI_GREEN_KOOPA_COMEBACK 6006
//
//#define ID_ANI_GREEN_WING_RIGHT 6009
//#define ID_ANI_GREEN_WING_LEFT 6010

/////////////////////////////////////////////////////////////////////////////////////////

//speeds
#define KOOPA_GREEN_GRAVITY 0.0004f
#define KOOPA_GREEN_WALKING_SPEED 0.025f
#define SPEED_KOOPA_GREEN_TURTLESHELL_IS_KICKED 0.12f


//bbox
#define KOOPA_GREEN_BBOX_WIDTH 16
#define KOOPA_GREEN_BBOX_HEIGHT 20
#define KOOPA_GREEN_BBOX_HEIGHT_TURTLESHELL 7

//times
#define KOOPA_GREEN_DIE_TIMEOUT 500
#define DISTANCE_MIN_SHELL_EXIST 150
#define TURTLE_SHELL_TIMEOUT 4000
#define TURTLE_SHELL_TOTURN_KOOPA 4000
#define TIME_COMBACK_KOOPA 1500

//States
#define KOOPA_GREEN_STATE_WALKING 100
#define KOOPA_GREEN_STATE_WALKING_LEFT 200
#define KOOPA_GREEN_STATE_WALKING_RIGHT 600
#define KOOPA_GREEN_STATE_ISTURTLESHELL 300
#define KOOPA_GREEN_STATE_ISKICKED 400
#define KOOPA_GREEN_STATE_TO_RETURN 450
#define KOOPA_GREEN_WALKING_STATE_TURN 460
#define KOOPA_GREEN_STATE_WAIT_RESET 470
#define KOOPA_GREEN_STATE_BE_HELD 478
#define KOOPA_GREEN_STATE_JUMP 500
#define KOOPA_GREEN_STATE_FALL 520
#define KOOPA_GREEN_STATE_BE_WHIPED 530


//Ani_id
#define ID_ANI_KOOPA_GREEN_WALKING_RIGHT 6001
#define ID_ANI_KOOPA_GREEN_WALKING_LEFT 6002
#define ID_ANI_KOOPA_GREEN_TURTLESHELL 6003
#define ID_ANI_KOOPA_GREEN_ISKICKED_LEFT_TO_RIGHT 6004
#define ID_ANI_KOOPA_GREEN_ISKICKED_RIGHT_TO_LEFT 6400
#define ID_ANI_GREEN_KOOPA_COMBACK 6006
#define ID_ANI_GREEN_WING_RIGHT 6009
#define ID_ANI_GREEN_WING_LEFT 6010

//UPSIDE
#define ID_ANI_GREEN_TURTLESHELL_UPSIDE 6030
#define ID_ANI_GREEN_TURTLESHELL_UPSIDE_COMBACK 6060
#define ID_ANI_GREEN_TURTLESHELL_UPSIDE_ISKICKED 6007



class CGreen_Koopa : public CGameObject
{
protected:

	int count_Fly;
	float ax;
	float ay;

	float startX;
	float startY;

	float rangeFly;

	CCheckFall* checkfall;
	CGreen_Koopa* newkoopa;




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
	bool flagHeldKick;
	bool isActive;

	bool Jump;
	bool Fall;

	bool KickByTail;

	int type_koopa;
	//int collis;

	ULONGLONG count_start;
	ULONGLONG comback_time;
	ULONGLONG time_delete;
	ULONGLONG time_rs;
	ULONGLONG isheld_time;
	ULONGLONG timeFly;
	ULONGLONG timeisWhiped;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();



	



	void CreateCheckfall();

	void CreateNewKoopa();

	void CreateGoomba();

	virtual int IsCollidable() { return 1; }


	void Green_Koopa_Active() {
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

		if (abs(mario->GetX() - x) < 150)
			isActive = true;
	}



	//virtual int IsColliswithMario() { return isCollis; }
	virtual int IsBlocking() { return 0; }

	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick_Question(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithOntheBox(LPCOLLISIONEVENT e);



public:


	ULONGLONG GetTimeHold() { return isheld_time; }

	ULONGLONG GetTimeComback() { return comback_time; }

	ULONGLONG GetTimeDelete() { return time_delete; }

	ULONGLONG GetCount_time() { return count_start; }

	void SetTailKick(bool b) { b = KickByTail; }

	bool GetTailKick() { return KickByTail;}

	void SetCombackTimes(ULONGLONG b) { b = comback_time; }

	bool GetIsJump() { return Jump; }
	bool GetIsFall() { return Fall; }

	void SetJump(bool b) { b = Jump; }
	void SetFall(bool b) { b = Fall; }

	int LeftOrRightMarrio();

	void SetTimeHold(ULONGLONG b) { b = isheld_time; }

	void SetCount_Start(ULONGLONG b) { b = count_start; }

	void SetisTurn(bool b) { b = isTurn; }

	void SetDead(bool b) { b = isDead; }

	void SetShell(bool b) { b = isTurtleShell; }

	void SETay(float b) { b = ay; }

	bool GetIsKick() { return isKicked; }

	void SetIsKick(bool b) { isKicked = b; }

	bool GetIsTurtleShell() { return isTurtleShell; }

	bool GETwasKicked() { return wasKicked; }


	bool GetIsComback() { return isComback; }

	bool GetisDeleted() { return isDeleted; }

	bool GetwasHeld() { return wasHeld; }

	bool GetisOntheBox() { return isOntheBox; }

	void SetIsDelete(bool b) { isDeleted = b; }
	//bool GetIsCollis() { return isCollis; }

	int DistanceTurtleShellisKickedWithMario();


	void Addnew_koopa(CGameObject* obj) {
		if (!dynamic_cast<CGreen_Koopa*>(obj)) return;
		else if (!newkoopa)
		{
			CGreen_Koopa* newKP = dynamic_cast<CGreen_Koopa*>(obj);
			newkoopa = newKP;
			DebugOut(L">>> check tao bullet >>> \n");

		}
	}

	void ResetKP()
	{
		if (newkoopa) newkoopa->Delete();
		newkoopa = NULL;
	}




	void AddCheck(CGameObject* obj) {
		if (!dynamic_cast<CCheckFall*>(obj)) return;
		else if (!checkfall)
		{
			CCheckFall* cfall_obj = dynamic_cast<CCheckFall*>(obj);
			checkfall = cfall_obj;
			DebugOut(L">>> check >>> \n");

		}
	}

	void ResetCheck()
	{
		if (checkfall) checkfall->Delete();
		checkfall = NULL;
	}

	void DeleteCheck()
	{
		checkfall->GetDeleted();
	}









	CGreen_Koopa(float x, float y, int type);
	virtual void SetState(int state);
};



