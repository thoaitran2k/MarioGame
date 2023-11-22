#pragma once
#include"GameObject.h"

#define ID_ANI_LONG_PIPE 202
#define ID_ANI_MEDIUM_PIPE 201

#define PIPE_BBOX_WIDTH 32
#define PIPE_BBOX_L_HEIGHT 32
#define PIPE_BBOX_M_HEIGHT 48

#define MODEL_L_PIPE 1	//L:LONG
#define MODEL_M_PIPE 2	//M:MEDIUM


class CPipePlantShoot : public CGameObject {
	protected:
		int model;

	public:
		CPipePlantShoot(float x, float y, int model);
		void GetBoundingBox(float& l, float& t, float& r, float& b);
		void Render();
		void Update(DWORD dt) {}
		virtual int IsColliable() { return 0; }
		virtual int IsBlocking() { return 1; }
		void SetModel(int model) { this->model = model; }
		int GetModel() { return model; }

};

