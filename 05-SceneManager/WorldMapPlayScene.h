//#include "GameObject.h"
//#include "Map.h"
//#include "GameObject.h"
//#include "Scene.h"
//#include "Mario_WorldMap.h"
//
//// similar CPlayScene
//class CWorldMapPlayScene :public CScene
//{
//	LPGAMEOBJECT player = NULL;
//	vector<LPGAMEOBJECT> objects;
//	CMap* standing_at_map = NULL;
//
//	LPGAMEOBJECT WorldMapObjects;
//
//	void _ParseSection_SPRITES(string line);
//	void _ParseSection_ANIMATIONS(string line);
//
//	void _ParseSection_ASSETS(string line);
//	void _ParseSection_OBJECTS(string line);
//	//void _ParseSection_TILEMAP_DATA(string line);
//
//	void _ParseSection_WORLDMAP(string line);
//
//	void LoadAssets(LPCWSTR assetFile);
//
//public:
//
//	CWorldMapPlayScene(int id, LPCWSTR filePath);
//	LPGAMEOBJECT GetPlayer() { return player; }
//	virtual void Load();
//	virtual void Update(DWORD dt);
//	virtual void Render();
//	virtual void Unload();
//	void Clear();
//	bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
//
//	void PurgeDeletedObjects();
//};
//
//typedef CWorldMapPlayScene* LPWORLDSCENE;
//
//
