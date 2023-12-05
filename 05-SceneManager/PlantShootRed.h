#pragma once
#include "Gameobject.h"
#include "bullet_plant.h"


#define SPEED 0.025f

#define TIME_OUT_PIPE 5000
#define TIME_CONDITION_TO_SHOOT 1500
#define TIME_IN_PIPE 4000
#define TIME_IN_PIPE_START 4500

#define DISTANCE_PLANT_ENEMIS_MAYBE_SHOW_UP 150
#define DISTANCE_MIN_MARIO_PLANT 24


#define PLANT_BBOX_WIDTH 12
#define PLANT_BBOX_HEIGHT_SMALL 24
#define PLANT_BBOX_HEIGHT 32

#define PLANT_STATE_UP 100
#define PLANT_STATE_DOWN 200
#define PLANT_STATE_NOT_TOUCH 300
#define PLANT_STATE_NOT_UP 400

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
		float loacationX;
		float startY;
		float minY;
		bool isShoot = false;
		bool isUpping, isDowning;
		float range;
		bool IsActive;
		

		CbulletPlant* bullet;

		float distanceMario_PlantEnemies();
		BOOLEAN isNotCollisMario = false;

		ULONGLONG time_out_pipe;
		ULONGLONG time_wait_plant_return;
		ULONGLONG time_shoot;
		ULONGLONG time_down_pipe;

		virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual void Render();
		int LeftORightMario();
		int TopOrBottomYMario();

		void CreateBullet();

	


		virtual int IsBlocking() { return 0; }

		virtual void OnNoCollision(DWORD dt);

	public:
		CPlantShootRed(float x, float y);
		
		bool GETUp() { return isUpping; }
		bool GETDown() { return isDowning; }
		bool StateActive() { return IsActive; }

		
		void create_bullet(CGameObject* obj) {
			if (!dynamic_cast<CbulletPlant*>(obj)) return;
			else if (!bullet)
			{
				CbulletPlant* new_bullet = dynamic_cast<CbulletPlant*>(obj);
				bullet = new_bullet;
				DebugOut(L">>> check tao bullet >>> \n");

			}
		}

		void Reset() {
			if (bullet) bullet->Delete();
			bullet = NULL;
		}


		
		virtual void SetState(int state);
		//void SetModel (int model) { this->model = model; }
		//int GetModel() { return model ; }
};

