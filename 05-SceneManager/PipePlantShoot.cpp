#include "PipePlantShoot.h"

void CPipePlantShoot::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (model == MODEL_L_PIPE) //L:LONG - M:MEDIUM
	{
		l = x - PIPE_BBOX_WIDTH / 2;
		t = y - PIPE_BBOX_L_HEIGHT / 2;
		r = l + PIPE_BBOX_WIDTH;
		b = t + PIPE_BBOX_L_HEIGHT;
	}
	else { 
		l = x - PIPE_BBOX_WIDTH / 2;
		t = y - PIPE_BBOX_M_HEIGHT / 2;
		r = l + PIPE_BBOX_WIDTH;
		b = t + PIPE_BBOX_M_HEIGHT;
	}
}

void CPipePlantShoot::Render()
{

	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (model == MODEL_L_PIPE) aniId = ID_ANI_LONG_PIPE;
	if (model == MODEL_M_PIPE) aniId = ID_ANI_MEDIUM_PIPE;

	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}
