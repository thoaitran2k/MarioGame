#include "bullet_plant.h"
#include "Mario.h"
#include "PlayScene.h"

void Cbullet_plant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + BULLET_BBOX_WIDTH;
	b = t + BULLET_BBOX_HEIGHT;
}


/*Cbullet_plant::Cbullet_plant(float x, float y, bool Up, bool R)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();


}

void Cbullet_plant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

}

void Cbullet_plant::Render() {

}
*/