#include "WorldMap.h"

void CWorldMap::Render()
{
	//if (model == 1) {
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_WORLD_MAP)->Render(x, y);
	//}
	//else {
	//	CAnimations* animations = CAnimations::GetInstance();
	//	animations->Get(ID_ANI_HIDEN_MAP)->Render(x, y);
	//}
}

void CWorldMap::GetBoundingBox(float& l, float& t, float& r, float& b) {}
