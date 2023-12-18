#include "FragGlass.h"

CFragGlass::CFragGlass(float x, float y, float vx, float vy) :CGameObject(x, y) 
{
	this->ay = GRAVITY;
	this->ax = 0.00004f;
	this->vx = 0.004f;
	this->vy = -0.3f;

	SetState(STATE_BREAK);
}

void CFragGlass::Render()
{

	int aniId;

	if(state == STATE_BREAK)
	aniId = ID_ANI_GLASS_BRICK_BREAK;


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

}


void CFragGlass::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
		l = x - 16 / 2;
		t = y - 16 / 2;
		r = l + 16;
		b = t + 16;
	
}

void CFragGlass::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFragGlass::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CFragGlass::SetState(int state)
{
	//if (this->state == STATE_BREAK && GetTickCount64() - time < 3000) return;

	switch (state)
	{
	case STATE_BREAK:
		time = GetTickCount64();
		break;
	}
	CGameObject::SetState(state);
}