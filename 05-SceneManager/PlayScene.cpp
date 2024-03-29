#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "BrickQuestion.h"
#include "MushRoom.h"
#include "Map.h"
#include "Background.h"
#include "PipePlantShoot.h"
#include "PlantShootRed.h"
#include "bullet_plant.h"
#include "Green_Koopa.h"
#include "Red_Koopa.h"
#include "Para_Goomba.h"
#include "Box.h"
#include "CheckKoopaFall.h"
#include "Green_Plant.h"
#include "TailWhipping.h"
#include "glassBrick.h"
#include "FragGlass.h"
#include "GameEffects.h"
#include "HUD_1.h"
#include "WorldMap.h"
#include "Card.h"





#include "SampleKeyEventHandler.h"

using namespace std;



CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}

void CPlayScene::AddObject(LPGAMEOBJECT object)
{
	objects.insert(objects.begin() + 1, object);

}




#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_MAP	3


#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::LoadHUD() {
	
	CHUD_1* hud = CHUD_1::GetInstance();

	//CGame* game = CGame::GetInstance();
	
	//hud = new CHUD_1(game->GetCameraX() + 150.0, game->GetCameraY() + 187.0);

	objects.push_back(hud);
}


void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}
//MAP

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	//switch (object_type)
	//{
	
	//case OBJECT_TYPE_MAP:
	obj = new CMap(x, y);

	//obj = new CWorldMap(x, y);

	

	//case OBJECT_TYPE_HIDEN_MAP: obj = new CMap(x, y, 2); break;
	//}

	

	// General object setup
	obj->SetPosition(x, y);
	MapObjects = obj;
}




/*
	Parse a line in section [OBJECTS] 
*/

CGameObject* CPlayScene::CreateObjectAndReturn(int id, float x, float y, float vx, float vy)
{

	int object_type = id;

	CGameObject* obj = NULL;
	LoadHUD();

	switch (object_type)
	{

	case OBJECT_TYPE_RED_KOOPA_WALKING: obj = new CRed_Koopa(x, y,1); break;

	case OBJECT_TYPE_NEW_RED_KOOPA: obj = new CRed_Koopa(x, y, 2); break;

	//case OBJECT_TYPE_NEW_RED_KOOPA_ON_GLASS_BRICK: obj = new CRed_Koopa(x, y,2); break;

	case OBJECT_TYPE_GREEN_KOOPA_WALKING: obj = new CGreen_Koopa(x, y,1); break;

	case OBJECT_TYPE_PARA_GOOMBA: obj = new CPara_Goomba(x, y); break;

	//case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y, GOOMBA_BASIC); break;

	case OBJECT_TYPE_CHECKFALL_KOOPA: obj = new CCheckFall(x, y,1); break;

	case OBJECT_TYPE_CHECKFALL_KOOPA_ON_GLASS_BRICK: obj = new CCheckFall(x, y, 2); break;

	case OBJECT_TYPE_FIRE_BULLET_OF_PLANT: obj = new CbulletPlant(x, y, 0, 0); break;

	case OBJECT_TYPE_GOOMBA_UNDER_KOOPA: obj = new CGoomba(x, y,GOOMBA_BASIC); break;

	case OBJECT_TYPE_WHIPPING: obj = new CTailWhipping(x, y); break;

	case OBJECT_TYPE_FRAG_GLASS_BRICK: obj = new CFragGlass(x, y, 0, 0); break;

	case OBJECT_TYPE_FRAG_GLASS_BRICK_2: obj = new CFragGlass(x, y, 0, 0); break;

	//case OBJECT_TYPE_NEW_RED_KOOPA: obj = new CRed_Koopa(x, y, 2); break;

	//case OBJECT_TYPE_RED_KOOPA_WALKING: obj = new CRed_Koopa(x, y, 1); break;

	//case OBJECT_TYPE_BUTTON_P: obj = new CButtonP(x, y); break;

	//case OBJECT_TYPE_GLASS_BRICK_CHANGETO_COIN: obj = new CglassBrick(x, y, GLASS_BRICK_MODEL_NORMAL); break;


		


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return NULL;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
	return obj;
	
}

void CPlayScene::CreateEffects() {

}

void CPlayScene::GlassBrickChangeToCoin()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if(dynamic_cast<CglassBrick*>(objects[i]))
			objects[i]->SetState(GLASS_BRICK_STATE_CHANGE_TO_COIN);
	}
}

CGameObject* CPlayScene::AddObj (int id, float x, float y, float vx, float vy)
{
	
	int object_type = id;

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_FIRE_BULLET_OF_PLANT: obj = new CbulletPlant(x,y,0,0); break;

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return NULL;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object has been created!\n");
		break;

	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x,y, GOOMBA_BASIC); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(x,y, MODEL_BASIC); break;
	case OBJECT_TYPE_BRICK_2: obj = new CBrick(x, y, MODEL_BASIC_2); break;
	case OBJECT_TYPE_BRICK_WHITE_SMILE: obj = new CBrick(x, y, MODEL_WHITE_SMILE); break;
	case OBJECT_TYPE_BRICK_BLUE_HIDDEN_MAP: obj = new CBrick(x, y, MODEL_BLUE); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
	case OBJECT_TYPE_MUSHROOM_GREEN: obj = new CMushRoom(x, y, MODE_GREEN);
	case OBJECT_TYPE_BRICK_Q_COIN: obj = new CBrickQuestion(x, y, QUESTION_BRICK_COIN); break;
	case OBJECT_TYPE_BRICK_Q_ITEM: obj = new CBrickQuestion(x, y, QUESTION_BRICK_NOT_COIN); break;
	//case OBJECT_TYPE_BRICK_Q_ITEM: obj = new CBrickQuestion(x, y, QUESTION_BRICK_NOT_COIN); break;
	case OBJECT_TYPE_LONG_PIPE: obj = new CPipePlantShoot(x, y, MODEL_L_PIPE); break;
	case OBJECT_TYPE_HIDEN_MAP_PIPE: obj = new CPipePlantShoot(x, y, MODE_HIDEN_MAP); break;
	case OBJECT_TYPE_PLANT_SHOOT_RED: obj = new CPlantShootRed(x, y); break;
	case OBJECT_TYPE_GREEN_PLANT_SHOOT: obj = new CGreen_Plant(x, y, PLANT_TYPE_SHOOT); break;
	case OBJECT_TYPE_GREEN_PLANT_NOT_SHOOT: obj = new CGreen_Plant(x, y, PLANT_TYPE_NOT_SHOOT); break;
	case OBJECT_TYPE_PARA_GOOMBA: obj = new CPara_Goomba(x, y); break;
	case OBJECT_TYPE_PIPE_EMPTY: obj = new CPipePlantShoot(x, y, MODEL_EMPTY_PIPE); break;
	case OBJECT_TYPE_PIPE_M_EMPTY: obj = new CPipePlantShoot(x, y, MODEL_EMPTY_M_PIPE); break;
	case OBJECT_TYPE_PIPE_PORTAL: obj = new CPipePlantShoot(x, y, MODEL_EMPTY_PORTAL_PIPE); break;
	case OBJECT_TYPE_PIPE_NOTACTIVE: obj = new CPipePlantShoot(x, y, 6); break;
	case OBJECT_TYPE_KOOPA_GREEN_WALKING: obj = new CGreen_Koopa(x, y,1); break;
	case OBJECT_TYPE_GREEN_KOOPA_INITI_WALKING: obj = new CGreen_Koopa(x, y, 2); break;
	case OBJECT_TYPE_RED_KOOPA_WALKING: obj = new CRed_Koopa(x, y,1); break;
	case OBJECT_TYPE_GLASS_BRICK_NORMAL: obj = new CglassBrick(x, y, GLASS_BRICK_MODEL_NORMAL); break;
	case OBJECT_TYPE_GLASS_BRICK_CONTAIN_BUTTON_P: obj = new CglassBrick(x, y, GLASS_BRICK_MODEL_CONTAIN_BUTTON); break;
	case OBJECT_TYPE_ITEM: obj = new CglassBrick(x, y, GLASS_BRICK_ITEM); break;
	case OBJECT_TYPE_FRAG_GLASS_BRICK: obj = new CFragGlass(x, y, 0,0); break;
	case OBJECT_TYPE_CARD: obj = new CCard(x, y); break;
	//case OBJECT_TYPE_HUD_DISPLAY: obj = new CHUD_1(x, y); break;
	//case OBJECT_TYPE_NEW_RED_KOOPA: obj = new CRed_Koopa(x, y, 2); break;

	
	//case OBJECT_TYPE_GLASS_BRICK_CONTAIN_BUTTON_P: obj = new CglassBrick(x, y, GLASS_BRICK_MODEL_CONTAIN_BUTTON); break;

	case OBJECT_TYPE_BOX:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CBox(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);
		break;
	}
	//case OBJECT_TYPE_BRICK_Q: obj = new CBrickQuestion(x, y); break;
	



	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_PLATFORM1:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CBackground(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[MAP]") { section = SCENE_SECTION_MAP; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx,cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	if (cx < 0) cx = 0;
	if (cy > 410) cy = 450;

	CGame::GetInstance()->SetCamPos(cx,cy);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();


	if (mario->GetLevel() == 3) {
		if (mario->GetMarkFly() >= 6  && !mario->GetIsOnPlatform())
		{
			if(mario->GetY() > 198)
			CGame::GetInstance()->SetCamPos(cx, cy);

			else CGame::GetInstance()->SetCamPos(cx, 45);



		}
		else if (mario->GetY()<205 )
			CGame::GetInstance()->SetCamPos(cx, 45);
		//else if(mario->GetY()<0)
			//CGame::GetInstance()->SetCamPos(cx, 0);

		else if(mario->GetY() > 408 && mario->GetX() > 2870)
			CGame::GetInstance()->SetCamPos(cx, 444);

		else
			CGame::GetInstance()->SetCamPos(cx, 263);
	}

	else {
		if(mario->GetY()>408 && mario->GetX()>2870)
			CGame::GetInstance()->SetCamPos(cx, 444);

		else if (mario->GetY() < 205)
			CGame::GetInstance()->SetCamPos(cx, 45);

		else
		CGame::GetInstance()->SetCamPos(cx, 263);
	}

	

	//else CGame::GetInstance()->SetCamPos(cx, cy-50);



	PurgeDeletedObjects();
}



void CPlayScene::Render()
{
	CGame* game = CGame::GetInstance();
	if (MapObjects)
	{
		MapObjects->Render();
	}




	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}


/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}

