#pragma once
#include "Gameobject.h"

#define SPEED_GROW_UP 0.025f

#define TIME_OUT_PIPE 3000
#define TIME_SHOOT 100
#define TIME_DOWN_PIPE 2000

#define PLANT_SHOOT_RED 1


#define PLANT_BBOX_WIDTH 12
#define PLANT_BBOX_HEIGHT_SMALL 24
#define PLANT_BBOX_HEIGHT 32

#define PLANT_STATE_UP 100
#define PLANT_STATE_DOWN 200

#define ID_ANI_PLANT_LEFT_UNDER_NOT_SHOOT	301
#define ID_ANI_PLANT_LEFT_UNDER_SHOOT 302
#define ID_ANI_PLANT_LEFT_TOP_NOT_SHOOT 303
#define ID_ANI_PLANT_LEFT_TOP_SHOOT 304
#define ID_ANI_PLANT_RIGHT_UNDER_NOT_SHOOT	305
#define ID_ANI_PLANT_RIGHT_UNDER_SHOOT 306
#define ID_ANI_PLANT_RIGHT_TOP_NOT_SHOOT 307
#define ID_ANI_PLANT_RIGHT_TOP_SHOOT 308

#define DISTANCE_PIPE_LONG_SHORT 8



class CPlantShootRed : public CGameObject
{
	protected:
		float startY;
		float minY;
		bool isShoot = false;
		int model;
		bool isUpping, isDowning;
		ULONGLONG time_out_pipe;
		ULONGLONG time_shoot;
		ULONGLONG time_down_pipe;

		virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual void Render();
		int PosWithXMario();
		int PosWithYMario();

		virtual int IsBlocking() { return 0; }

		virtual void OnNoCollision(DWORD dt);

	public:
		CPlantShootRed(float x, float y, int model);

		
		virtual void SetState(int state);
		void SetModel (int model) { this->model = model; }
		int GetModel() { return model ; }
};

