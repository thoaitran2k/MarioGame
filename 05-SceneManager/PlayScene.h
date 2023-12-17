#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "BrickQuestion.h"

//#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					

	vector<LPGAMEOBJECT> objects;

	LPGAMEOBJECT MapObjects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);


	void LoadAssets(LPCWSTR assetFile);
	
public: 

	
	CPlayScene(int id, LPCWSTR filePath);

	virtual void GlassBrickChangeToCoin();

	CGameObject* AddObj(int id, float x, float y, float vx, float vy);
	CGameObject* CreateObjectAndReturn(int id, float x, float y, float vx, float vy);
	void AddObject(LPGAMEOBJECT object);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

