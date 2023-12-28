//#include "Mario_WorldMap.h"
//#include "Game.h"
//#include "debug.h"
//
//
//void CMario_WorldMap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
//	
//	vx += ax * dt;
//	vy += ay * dt;
//
//
//}
//
//void CMario_WorldMap::Render() {
//	
//
//	int aniId = ID_ANI_MARIO_IDLE_RIGHT_1;
//	if (vx == 0) {
//		if (nx > 0)
//			aniId = ID_ANI_MARIO_IDLE_RIGHT_1;
//		else
//			aniId = ID_ANI_MARIO_IDLE_LEFT_2;
//	}
//	else {
//		if (vx > 0) aniId = ID_ANI_MARIO_WALKING_RIGHT_1;
//		else aniId = ID_ANI_MARIO_WALKING_LEFT_2;
//	}
//	
//	CAnimations* animations = CAnimations::GetInstance();
//	animations->Get(aniId)->Render(x, y);
//}
//
//void CMario_WorldMap::OnNoCollision(DWORD dt) {
//	x += vx * dt;
//	y += vy * dt;
//}
//
//void CMario_WorldMap::OnCollisionWith(LPCOLLISIONEVENT e) {
//	if (e->obj->IsBlocking()) {
//		vx = 0;
//		vy = 0;
//	}
//}
//
//void CMario_WorldMap::SetState(int state) {
//	switch (state) {
//	case MARIO_STATE_LEFT:
//		vy = 0.0f;
//		vx = -MARIO_WALKING_SPEED;
//		break;
//	case MARIO_STATE_RIGHT:
//		vy = 0.0f;
//		vx = MARIO_WALKING_SPEED;
//		break;
//	/*case MARIO_STATE_GO_TOP:
//		vy = -SPEED_MARIO;
//		vx = 0.0f;
//		break;
//	case MARIO_STATE_GO_UNDER:
//		vy = SPEED_MARIO;
//		vx = 0.0f;
//		break;
//	case MARIO_STATE_GO_WORLD_1:
//		isCanGoWorld = true;
//		break;*/
//	}
//}