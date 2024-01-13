#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Sprite.h"
#include "Mario.h"

#define FONT_BBOX_WIDTH	8
#define DEFAULT_TIME	300
#define ID_ANI_HUD 98766
#define ID_ANI_BLACK_RECTANGEL 98765
#define ID_ANI_POWER_HUD 130002
#define ID_ANI_P 130003
#define ID_ANI_M_SYMBOL 130005
#define ID_ANI_0	130010
#define ID_ANI_1	130011
#define ID_ANI_2	130012
#define ID_ANI_3	130013
#define ID_ANI_4	130014
#define ID_ANI_5	130015
#define ID_ANI_6	130016
#define ID_ANI_7	130017
#define ID_ANI_8	130018
#define ID_ANI_9	130019
#define ID_ANI_HUD_CARD_MUSHROOM 130021
#define ID_ANI_HUD_CARD_FLOWER 130022
#define ID_ANI_HUD_CARD_STAR 130023

#define ID_ANI_HUD_GAME_OVER 130025
#define ID_ANI_NULL 130026




#define HUD_CARD_MUSHROOM 1
#define HUD_CARD_FLOWER 2
#define HUD_CARD_STAR 3


#define ADJUST_HUD_X_POSITION 128
#define ADJUST_HUD_Y_POSITION 196

#define ADJUST_X_POWER_POSITION 60
#define ADJUST_X_POWER_POSITION_MAX 8

#define DISTANCE_EVERY_LEVEL_RUN 8
#define ADJUST_Y_POWER_POSITION 4
#define ADJUST_Y_POWER_POSITION_UNDER -5

#define POSITION_WORLD_X -76
#define POSITION_COIN_X 20
#define POSITION_CLOCK_X 12
#define POSITION_SCORE_X -60
#define POSITION_M_SYMBOL_X -104
#define POSITION_UP_X -84
#define DISTANCE_NUMBER 8

#define X_CARD_POSITION 56
#define Y_CARD_POSITION 0
#define CARD_WIDTH 24


class CHUD_1:public CGameObject
{
	static CHUD_1* __instance;
	float x;
	float y;
	vector<int> timesgame;
	ULONGLONG count_start;
	ULONGLONG time_render_card;
	int count_down_time = 0;

public:
	//CHUD_1(float x, float y);
	CHUD_1(float x, float y) : CGameObject(x,y) {
		this->x = 0.0f;
		this->y = 0.0f;
		count_start = -1;
		time_render_card = -1;
	}

	void AniNumber(int n, float Xnumber, float Ynumber);
	void AniCard(int n, float Xcard, float Ycard);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
	static CHUD_1* GetInstance();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void RenderBoundingBox();
	/*void WriteTimes();
	int getAniId(int num);*/
};

