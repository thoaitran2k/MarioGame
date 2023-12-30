#include "GameObject.h"

#define SPEED_CARD_FLY 0.04f

#define CARD_BBOX_HEIGHT 16
#define CARD_BBOX_WIDTH 16


#define ID_ANI_CARD_MUSHROOM 24781
#define ID_ANI_CARD_FLOWER 24786
#define ID_ANI_CARD_STAR 24791

#define TIME_RENDER_CARD 200
#define ID_MODE_CARD_MUSHROOM 1
#define ID_MODE_CARD_FLOWER 2
#define ID_MODE_CARD_STAR 3

#define STATE_CARD_IS_COLLECTED	100
class CCard : public CGameObject
{
	int id_mode;
	bool isActive;
	ULONGLONG time_Render;
	ULONGLONG time_disappear;

public:
	CCard(float, float y) :CGameObject(x, y) {
		id_mode = ID_MODE_CARD_MUSHROOM;
		isActive = false;
		time_Render = GetTickCount64();
		time_disappear = -1;
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void OnNoCollision(DWORD dt) {
		x += vx * dt;
		y += vy * dt;
	}

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 1; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);


	int GetCard() { return id_mode; }
	void SetCard(int card) { card = id_mode; }
	bool GetCollect() { return isActive; }
	void SetState(int state);

};

