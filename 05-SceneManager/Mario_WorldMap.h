//#include "GameObject.h"
//
//
//#define MARIO_WALKING_SPEED		0.04f
//
//#define MARIO_STATE_LEFT	100
//#define MARIO_STATE_RIGHT	200
//#define MARIO_STATE_UP		300
//#define MARIO_STATE_DOWN	400
//
//
//#define ID_ANI_MARIO_IDLE_RIGHT_1 400
//#define ID_ANI_MARIO_IDLE_LEFT_2 401
//
//#define ID_ANI_MARIO_WALKING_RIGHT_1 500
//#define ID_ANI_MARIO_WALKING_LEFT_2 501
//
//class CMario_WorldMap : public CGameObject
//{
//	//float startX;
//	//float startY;
//
//	float ax;
//	float ay;
//
//
//public:
//	CMario_WorldMap(float x, float y) : CGameObject(x,y)
//	{
//		ax = 0.0f;
//	}
//
//	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
//
//	virtual void Render();
//
//	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
//	int IsCollidable() { return 1; }
//
//	int IsBlocking() { return 1; }
//	virtual void OnNoCollision(DWORD dt);
//	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
//
//	virtual void SetState(int state);
//
//};
//
