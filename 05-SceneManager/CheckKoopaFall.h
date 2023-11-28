#pragma once
#include "GameObject.h"


#define BOX_BBOX_WIDTH 16
#define BOX_BBOX_HEIGHT 16


// 
// The most popular type of object in Mario! 
// 
class CCheckFall : public CGameObject
{
protected:
	float ax;
	float ay;

	



	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	


public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();




	void SetIsOnPlatform(bool b) { isOnPlatformCheck = b; }

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	bool GetIsOnPlatForm2() { return isOnPlatformCheck; };

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithPlatForm(LPCOLLISIONEVENT e);
	CCheckFall(float x, float y);

	bool isOnPlatformCheck;
	BOOLEAN GetIsOnPlatform() { return isOnPlatformCheck; }

	
};


