#pragma once
#include "SceneManager.h"
#include <windows.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include <cstdlib>
#include <ctime>

#include "debug.h"
#include "Game.h"
#include "Camera.h"
#include "GameObject.h"
#include "Textures.h"
#include "TileMap.h"

#include "SIMON.h"
#include "MS.h"
#include "Torch.h"
#include "Brick.h"
#include "Dagger.h"
#include "Axe.h"
#include "HolyWater.h"
#include "InviObjects.h"
#include "Grid.h"
#include "Ghoul.h"
#include "Bat.h"
#include "Fishman.h"
#include "Panther.h"
#include "FireBullet.h"
#include "CEffect.h"

#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include "define.h"
class SceneGame : public SceneManager
{
public:
	SceneGame();
	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	virtual void LoadResources(LPCWSTR picturePath, int idTex, const char* filepath, int scene) override;
	void Update(DWORD dt);
	void Render();
	void LoadObjectFromFile(string source);
	void LoadSceneObject(int a);
	void SpawnDelayGhoulStart() { spawndelayghoul = 1;  spawndelayghoultimer_start = GetTickCount(); }
	void SpawnDelayBatStart() { spawndelaybat = 1;  spawndelaybattimer_start = GetTickCount(); }
	void SpawnDelayFishmanStart() { spawndelayfishman = 1;  spawndelayfishmantimer_start = GetTickCount(); }
	void SpawnDelayPantherStart() { spawndelaypanther = 1;  spawndelaypanthertimer_start = GetTickCount(); }
	void StopEnemyStart() { stopenemy = 1; stopenemytimer_start = GetTickCount(); }
	~SceneGame();
	CGame* game;
	Camera* camera;
    CSimon* SIMON;
	CMS* MS;
	CDagger* dagger;
	CAxe* Axe;
	CHolyWater* Holywater;
	TileMap* Tile;
	CBrick* brick;
	CTorch* torch;
	CTorch* hiddenmoney;
	CGhoul* ghoul;
	CBat* bat;
	CFishman* fishman;
	CPanther* panther;
	CFireBullet* firebullet;
	CEffect* effect;
	TileMap* tile;
	InviObjects* InObj;
	Grid* grid;
	CAnimations* animations;
	CSprites* sprites;
	LPANIMATION ani;
	vector<LPGAMEOBJECT> weapon;
	vector<LPGAMEOBJECT> torches;
	vector<LPGAMEOBJECT> invisibleobjects;
	vector<LPGAMEOBJECT> bricks;
	vector<LPGAMEOBJECT> enemy;
	vector<LPGAMEOBJECT> effects;
    vector<LPGAMEOBJECT> ObjectsFromGrid;

	bool castle = false;
	bool SimonMove = false;
	bool isChangeColor;
	bool isGrey;
	int scene;
	int stage;
	int countChangeColor;
	int spawndelayghoul = 0;
	int spawndelaybat = 0;
	int spawndelayfishman = 0;
	int spawndelaypanther = 0;
	int stopenemy;
	float cx, cy;
	float startpoint, endpoint, camstoppoint;
    DWORD timerChangeColor;
	DWORD spawndelayghoultimer_start;
	DWORD spawndelaybattimer_start;
	DWORD spawndelayfishmantimer_start;
	DWORD spawndelaypanthertimer_start;
	DWORD stopenemytimer_start;



	//read from file
	int simonposstartx;
	int simonposstarty;
	int simonposundergroundtoland1x;
	int simonposundergroundtoland1y;
    int simonposlandtounderground1x;
	int simonposlandtounderground1y;
	int simonposundergroundtoland2x;
	int simonposundergroundtoland2y;
	int simonposlandtounderground2x;
	int simonposlandtounderground2y;
	int hiddenmoneyposx;
	int hiddenmoneyposy;
	int ghouly;
	int panther1x;
	int panther1y;
	int panther2x;
	int panther2y;
	int panther3x;
	int panther3y;
	int startstage1;
	int endstage1;
	int startstage2;
	int endstage2;
	int startstage3;
	int endstage3;
	int startstage4;
	int endstage4;
};

