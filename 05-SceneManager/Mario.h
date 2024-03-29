﻿#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#include "debug.h"

#include "TailWhipping.h"

#include "PlayScene.h"
#include "Game.h"

#define POSITION_END_MAP_1	2810

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0003f
#define MARIO_ACCEL_RUN_X	0.0004f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.0019f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#define MARIO_STATE_KICK			650
#define MARIO_STATE_HOLDING_RIGHT	660
#define MARIO_STATE_HOLDING_LEFT	670
#define MARIO_STATE_ATTACK			680
#define MARIO_STATE_ATTACK_LEFT		690
#define MARIO_STATE_ATTACK_RIGHT	700

#define MARIO_STATE_DOWN_PIPE		710
#define MARIO_STATE_UP_PIPE			720

#define RACOON_STATE_FLY_DOWN_RELEASE	800

#define RACOON_STATE_FLY	810
#define RACOON_STATE_END_FLY	820
#define RACOON_STATE_START_FLY	830
#define RACOON_STATE_RELEASE_FLY_HIGH	840

#define MARIO_STATE_UNCONTROL	888



#pragma region ANIMATION_ID

//BIG_MARIO////////////////

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_BIG_HOLD_RUNNING_RIGHT 1011
#define ID_ANI_MARIO_BIG_HOLD_RUNNING_LEFT 1010

#define ID_ANI_MARIO_BIG_HOLD_IDLE_RIGHT 1041
#define ID_ANI_MARIO_BIG_HOLD_IDLE_LEFT 1040

#define ID_ANI_MARIO_BIG_HOLD_JUMP_RIGHT 1051
#define ID_ANI_MARIO_BIG_HOLD_JUMP_LEFT 1050

#define ID_ANI_MARIO_KICK_RIGHT 1802
#define ID_ANI_MARIO_KICK_LEFT 1801

#define ID_ANI_MARIO_DIE 999

#define ID_ANI_BIG_MARIO_DOWN_UP	33334

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#define ID_ANI_MARIO_SMALL_HOLD_RUNNING_RIGHT 1611
#define ID_ANI_MARIO_SMALL_HOLD_RUNNING_LEFT 1610

#define ID_ANI_MARIO_SMALL_KICK_RIGHT 1702
#define ID_ANI_MARIO_SMALL_KICK_LEFT 1701

#define ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT 1641
#define ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT 1640

#define ID_ANI_MARIO_SMALL_HOLD_JUMP_RIGHT 1651
#define ID_ANI_MARIO_SMALL_HOLD_JUMP_LEFT 1650
// 

//////MARIO RACOON/////////////
#define ID_ANI_RACOON_IDLE_RIGHT 2401
#define ID_ANI_RACOON_IDLE_LEFT 2400

#define ID_ANI_RACOON_WALKING_RIGHT 2501
#define ID_ANI_RACOON_WALKING_LEFT 2500

#define ID_ANI_RACOON_RUNNING_RIGHT 2601
#define ID_ANI_RACOON_RUNNING_LEFT 2600

#define ID_ANI_RACOON_RUNNING_PREPARE_RIGHT 2603
#define ID_ANI_RACOON_RUNNING_PREPARE_LEFT 2602

#define ID_ANI_RACOON_JUMP_WALK_RIGHT 2701
#define ID_ANI_RACOON_JUMP_WALK_LEFT 2700

#define ID_ANI_RACOON_JUMP_RUN_RIGHT 2801
#define ID_ANI_RACOON_JUMP_RUN_LEFT 2800

#define ID_ANI_RACOON_SIT_RIGHT 2901
#define ID_ANI_RACOON_SIT_LEFT 2900

#define ID_ANI_RACOON_BRACE_RIGHT 3001
#define ID_ANI_RACOON_BRACE_LEFT 3000

#define ID_ANI_RACOON_HOLD_RUNNING_RIGHT 3011
#define ID_ANI_RACOON_HOLD_RUNNING_LEFT 3010

#define ID_ANI_RACOON_KICK_RIGHT 3021
#define ID_ANI_RACOON_KICK_LEFT 3020

#define ID_ANI_RACOON_HOLD_IDLE_RIGHT 3041
#define ID_ANI_RACOON_HOLD_IDLE_LEFT 3040

#define ID_ANI_RACOON_HOLD_JUMP_RIGHT 3051
#define ID_ANI_RACOON_HOLD_JUMP_LEFT 3050

#define ID_ANI_RACOON_ATTACK 3100 ////////////QUAY DUOI

#define ID_ANI_RACOON_ATTACK_LEFT 3371
#define ID_ANI_RACOON_ATTACK_RIGHT 3370

#define ID_ANI_RACOON_FLY_DOWN_RIGHT 3061
#define ID_ANI_RACOON_FLY_DOWN_LEFT 3060


#define ID_ANI_RACOON_FLY_RIGHT 3300
#define ID_ANI_RACOON_FLY_LEFT 3200

#define ID_ANI_DOWN_UP_PIPE	33333

#define ID_ANI_RACOON_HOLD_GO_RIGHT	33334
#define ID_ANI_RACOON_HOLD_GO_LEFT	33335

#define ID_ANI_RACOON_FLY_HOLD_RIGHT 33336
#define ID_ANI_RACOON_FLY_HOLD_LEFT 33337





#pragma endregion

#define GROUND_Y 160.0f



////LEVEL////////
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACOON	3

#define MARIO_BIG_BBOX_WIDTH  16
#define MARIO_BIG_BBOX_HEIGHT 24
#define RACOON_BBOX_HEIGHT 18
#define RACOON_BBOX_WIDTH 20
#define MARIO_BIG_SITTING_BBOX_WIDTH  16
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16
#define RACOON_SITTING_BBOX_WIDTH  19
#define RACOON_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  16
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2000

class CMario : public CGameObject
{
	int coin;
	BOOLEAN isSitting;
	BOOLEAN Kicking;
	bool Holding;
	bool isHold;
	bool TailAttack;
	bool flyLowDown;
	bool GetRenderFly;
	float rangFlyStart;
	float rangeUpPipe;
	bool LoadRenderDownPipe;
	bool contact_door;

	bool Enter_map;

	int effect;

	int markFly;
	int UP_M;
	int id_card;
	bool goEndMap;

	bool FlyHigh;
	bool Fly;

	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 


	int clocktime;  
	int score;//TIMESGAME
	bool Run;
	bool EnterPipe;
	bool StandOnPipe;
	bool HitHeadPipe;
	float rangeEnterPipe;
	bool waitDownPipe;
	bool waitUpPipe;

	int level; 
	
	int untouchable; 
	ULONGLONG untouchable_start;
	ULONGLONG timing;
	BOOLEAN isOnPlatform;
	ULONGLONG timedownupPipe;
	ULONGLONG start_speed;
	ULONGLONG stop_speed;
	ULONGLONG start_prepare;
	ULONGLONG time_relase_fly_high;
	ULONGLONG count_seconds;
	ULONGLONG time_maintain_fly_high;
	ULONGLONG time_maintain_fly_low;
	ULONGLONG time_fly_max;
	ULONGLONG time_wait_up_pipe;
	ULONGLONG time_fly_start;
	ULONGLONG time_uncontrol;


	CTailWhipping* tail;
	

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithBrickQuestion(LPCOLLISIONEVENT e);
	void OnCollisionWithMushRoom(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopa_Green(LPCOLLISIONEVENT e);
	void OnCollisionWithRed_Koopa(LPCOLLISIONEVENT e);
	void OnCollisionWithPara_Goomba(LPCOLLISIONEVENT e);
	void OnCollisionWithFire_Bullet(LPCOLLISIONEVENT e);
	void OnCollisionWithPlantShootRed(LPCOLLISIONEVENT e);
	void OnCollisionWithGreenPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithGlassBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithButtonP(LPCOLLISIONEVENT e);	
	void OnCollisionWithPipe(LPCOLLISIONEVENT e);
	void OnCollisionWithPlatform(LPCOLLISIONEVENT e);
	void OnCollisionWithCard(LPCOLLISIONEVENT e);
	


	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();

	
	

	

	

public:

	void AddTail(CGameObject* obj) {
		if (!dynamic_cast<CTailWhipping*>(obj)) return;
		else if (!tail)
		{
			CTailWhipping* newTail = dynamic_cast<CTailWhipping*>(obj);
			tail = newTail;
			DebugOut(L">>> check tao tail >>> \n");

		}
	}

	

	void CreateWhippingofTail();




	
	int GetCoin() { return this->coin; }
	CMario(float x, float y) : CGameObject(x, y)
	{
		
		isSitting = false;
		Kicking = false;
		Holding = false;
		isHold = false;
		HitHeadPipe = false;
		TailAttack = false;
		flyLowDown = false;
		waitDownPipe = false;
		waitUpPipe = false;
		Enter_map = false;
		contact_door = false;
		goEndMap = false;
		rangFlyStart = -1;
		
		Fly = false;
		clocktime = 300;
		score = 0;
		//count_seconds = GetTickCount64();
		FlyHigh = false;
		timedownupPipe = -1;
		time_relase_fly_high = -1;
		tail = NULL;
		rangeEnterPipe = 0;
		rangeUpPipe = 0;
		UP_M = 0;
		EnterPipe = false;
		StandOnPipe = false;
		LoadRenderDownPipe = false;
		maxVx = 0.0f;
		ax = 0.0f;

		ay = MARIO_GRAVITY;
		

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		time_fly_max = -1;
		time_maintain_fly_low = -1;
		time_maintain_fly_high = -1;

		time_wait_up_pipe = -1;
		time_fly_start = -1;
		time_uncontrol = -1;


		isOnPlatform = false;
		coin = 0;
		id_card = -1;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void SetMario() {
		if (level > MARIO_LEVEL_SMALL)
		{
			if (level > MARIO_LEVEL_BIG)

				level = MARIO_LEVEL_BIG;

			else level = MARIO_LEVEL_SMALL;
			StartUntouchable();
			DebugOut(L">>> Mario biến nhỏ >>> \n");
		}
	}

	void SetCoin(int coin) { this->coin = coin; }

	void CountDownTimes();

	//void CountDownTimeGame();


	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);

	void SetPoint(int b);



	int GetLevel() { return level; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	//get
	ULONGLONG GetTimeFlyMax() { return time_fly_max; }

	int GetUp_M() { return UP_M; }

	bool GetIsHolding() { return Holding; }

	int GetMarkFly() { return markFly; }

	bool GetIsHold() { return isHold; }

	bool GetAttack() { return TailAttack; }

	bool GetFly() { return Fly; }

	int GetPoint() { return score; }

	int GetTimeGame() { return clocktime; }

	bool GetIsOnPlatform() { return isOnPlatform; }

	bool GetUpPipe() { return HitHeadPipe; }

	void SetPositionPlayer(float x, float y) { this->x = x; this->y = y; }

	bool GetEnterPipe() { return EnterPipe; }

	bool GetIsStandOnPipi() { return StandOnPipe; }

	float GetRangeEnterPipe() { return rangeEnterPipe; }

	bool GetFlyHigh() { return FlyHigh; }

	bool GetContactDoor() { return contact_door; }

	int GetIDCard() { return id_card;}

	bool GetGoEndMap() { return goEndMap; }

	ULONGLONG GetTimeUnControl() { return time_uncontrol; }

	//set
	void SetUnControl(bool b) { b = goEndMap; }

	void SetUp_M(int m) { m = UP_M; }

	void SetFlyLowDown(bool b) {b = flyLowDown;}

	void SetTimeFlyHigh(ULONGLONG b) { b = time_relase_fly_high; }

	void SetTimeFlyLow(ULONGLONG t) { t = time_maintain_fly_low; }

	void SetHolding(bool b) { Holding = b; }

	void SetIsHold(bool b) { isHold = b; }

	void SetAttack(bool b) { TailAttack = b; }

	void SETay(float b) { b = this->ay; }

	void CreatEffectMario(int effect);

	void SetRacoonFlying();

	void SetEnterPipe(bool b) { b = EnterPipe; }

	void SetStandOnPipe(bool b) { b = StandOnPipe; }

	void SetFlyTF(bool b) { b = Fly; }

	void SetFlyHigh(bool b) { b = FlyHigh; }

	void SetEnterMap(bool b) { b = Enter_map; }

	void SetIdCard(int card) { card = id_card; }


};