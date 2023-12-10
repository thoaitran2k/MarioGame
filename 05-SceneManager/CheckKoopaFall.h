#pragma once
#include "GameObject.h"



#define BOX_BBOX_WIDTH 16
#define BOX_BBOX_HEIGHT 16

#define STATE_LEFT_KOOPA 100
#define STATE_RIGHT_KOOPA 200

#define SPEED_PREVIOUS_KOOPA 0.015f

// 
// The most popular type of object in Mario! 
// 
class CCheckFall : public CGameObject
{
protected:
	float ax;
	float ay;

	bool OnTheBox;
	bool isOnPlatformCheck;

	

	

	



	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	


public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


	virtual void SetState(int state);

	//void SetIsOnPlatform(bool b) { isOnPlatformCheck = b; }

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	bool GetNoOntheBox() { return OnTheBox; }

	//bool GetIsOnPlatForm2() { return isOnPlatformCheck; };

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
	void OnCollisionWithBox(LPCOLLISIONEVENT e);
	CCheckFall(float x, float y);

	void GetDeleted() {
		isDeleted = true;
	}

	
	bool GetIntheBox() { return OnTheBox; }
	bool GetIsOnPlatform() { return isOnPlatformCheck; }

	
	void SetIsOnPlatform(bool b) { b = isOnPlatformCheck; }

	//set ay
	void SETay(float y) { y = ay; }

	/*bool checkfalling()
	{
		if (vy > 0.0004f) return true;
	}*/
};


