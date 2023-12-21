#pragma once
#include "GameObject.h"
#include "CheckKoopaFall.h"
#include "debug.h"
#include "Goomba.h"
#include "Game.h"
#include "PlayScene.h"

//Model
#define KOOPA_RED_NORMAL 1
#define KOOPA_RED_ON_THE_BRICK 2




//speeds
#define KOOPA_RED_GRAVITY 0.002f
#define KOOPA_RED_WALKING_SPEED 0.015f
#define SPEED_KOOPA_RED_TURTLESHELL_IS_KICKED 0.09f


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
#define KOOPA_RED_WALKING_STATE_TURN_ON_GLASS 480
#define KOOPA_RED_STATE_WALKING_ON_GLASS 481

#define KOOPA_RED_STATE_RESET_AFTER_KICKED 482

#define KOOPA_RED_STATE_TURTLESHELL_UPSIDE_TAIL_ATTACK 483

//Ani_id
#define ID_ANI_KOOPA_RED_WALKING_RIGHT 6101
#define ID_ANI_KOOPA_RED_WALKING_LEFT 6102
#define ID_ANI_KOOPA_RED_TURTLESHELL 6103
#define ID_ANI_KOOPA_RED_ISKICKED_LEFT_TO_RIGHT 6104
#define ID_ANI_KOOPA_RED_ISKICKED_RIGHT_TO_LEFT 6401
#define ID_ANI_RED_KOOPA_COMBACK 6106

//UPSIDE
#define ID_ANI_RED_KOOPA_COMBACK_UPSIDE 6108
#define ID_ANI_RED_KOOPA_KICKED_UPSIDE 6107
#define ID_ANI_RED_KOOPA_TURTLESHELL_UPSIDE 6105


//GREEN_WALKING Ani_id
#define ID_ANI_KOOPA_GREEN_WALKING_RIGHT 6001
#define ID_ANI_KOOPA_GREEN_WALKING_LEFT 6002



class CRed_Koopa : public CGameObject
{
protected:

	int typeKoopa;
	float ax;
	float ay;

	float startX;
	float startY;

	bool KoopaOnGlassActive;

	bool TailAttack;

	

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
	bool flagHeldKick;
	bool OntheGlassBrick;
	//int collis;

	ULONGLONG count_start;
	ULONGLONG comback_time;
	ULONGLONG time_delete;
	ULONGLONG time_rs;
	ULONGLONG isheld_time;
	ULONGLONG timeWhiped;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	

	int LeftOrRightMarrio();

	

	void CreateCheckfall();

	void CreateCheckfallSmall();

	void CreateNewKoopa();

	void CreateNewKoopa2();

	void CreateGoomba();

	void CreateKoopaOnGlassBrick();


	
	virtual int IsCollidable() { return 1;}


	
	//virtual int IsColliswithMario() { return isCollis; }
	virtual int IsBlocking() { return 0; }
	
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick_Question(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithOntheBox(LPCOLLISIONEVENT e);
	void OnCollisionWithGlassBrick(LPCOLLISIONEVENT e);

	void Koopa_onGlassBrick_Active() {
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

		if (abs(mario->GetX() - x) < 50)
			KoopaOnGlassActive = true;
	}



public:
	ULONGLONG GetTimeHold() { return isheld_time; }

	ULONGLONG GetTimeComback() { return comback_time; }

	ULONGLONG GetTimeDelete() { return time_delete; }

	ULONGLONG GetCount_time() { return count_start; }

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
		if (newkoopa) newkoopa->Delete();
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
	
	
	

	

	CRed_Koopa(float x, float y,int typeKoopa);
	virtual void SetState(int state);
};



