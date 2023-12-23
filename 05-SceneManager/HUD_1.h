#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Mario.h"

#define FONT_BBOX_WIDTH	8
#define DEFAULT_TIME	300
#define ID_ANI_HUD 30000
#define ID_ANI_BLACK_RECTANGEL 30001
#define ID_ANI_POWER_HUD 30002
#define ID_ANI_POWER_HUD_MAX 30003
#define ID_ANI_M_SYMBOL 30005
#define ID_ANI_0	30010
#define ID_ANI_1	30011
#define ID_ANI_2	30012
#define ID_ANI_3	30013
#define ID_ANI_4	30014
#define ID_ANI_5	30015
#define ID_ANI_6	30016
#define ID_ANI_7	30017
#define ID_ANI_8	30018
#define ID_ANI_9	30019
#define ID_ANI_HUD_CARD_MUSHROOM 30021
#define ID_ANI_HUD_CARD_FLOWER 30022
#define ID_ANI_HUD_CARD_STAR 30023

#define ID_ANI_HUD_GAME_OVER 30025
#define ID_ANI_NULL 30026
#define ID_ANI_ARROW 30027
#define ID_ANI_HUD_SUB 30028


#define ID_ANI_HUD_CARD_MUSHROOM_END_SCENE 30031
#define ID_ANI_HUD_CARD_FLOWER_END_SCENE 30032
#define ID_ANI_HUD_CARD_STAR_END_SCENE 30033


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


class CHUD_1
{
protected:
	float x;
	float y;

public:
	//CHUD_1(float x, float y);
	CHUD_1(float x, float y) {
		this->x = x;
		this->y = y;
	}

	void AniNumber(int n, float Xnumber, float Ynumber);
	void AniCard(int n, float Xcard, float Ycard);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {}
};

