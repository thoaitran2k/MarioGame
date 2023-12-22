#include "Brick.h"

void CBrick::Render()
{

	int aniId;

	if (model == 1) { aniId = ID_ANI_BRICK; }

	else if(model == 2) { aniId = ID_ANI_BRICK_2; }

	else if (model == 3) { aniId = ID_ANI_BRICK_WHITE_SMILE; }

	else if (model == 4) { aniId = ID_ANI_BRICK_BLUE_HIDDEN_MAP; }



	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{

	if (model == 1)
	{
		l = x - BRICK_BBOX_WIDTH / 2;
		t = y - BRICK_BBOX_HEIGHT / 2;
		r = l + BRICK_BBOX_WIDTH;
		b = t + BRICK_BBOX_HEIGHT;
	}
	else if (model == 2)
	{
		l = x - BRICK_BBOX_WIDTH / 2+2;
		t = y - BRICK_BBOX_HEIGHT / 2;
		r = l + BRICK_BBOX_WIDTH-1 ;
		b = t + BRICK_BBOX_HEIGHT;
	}
	else if(model == 3)
	{
		l = x - BRICK_BBOX_WIDTH / 2;
		t = y - BRICK_BBOX_HEIGHT / 2;
		r = l + BRICK_BBOX_WIDTH;
		b = t + BRICK_BBOX_HEIGHT;
	}
	else if (model == 4)
	{
		l = x - BRICK_BBOX_WIDTH / 2;
		t = y - BRICK_BBOX_HEIGHT / 2;
		r = l + BRICK_BBOX_WIDTH;
		b = t + BRICK_BBOX_HEIGHT;
	}
}

