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
#include "InviObjects.h"
#include "Grid.h"

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

	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void LoadObjectFromFile(string source);
	void LoadSceneObject(int a);

	~SceneGame();
	CGame* game;
	Camera* camera;
    CSimon* SIMON;
	CMS* MS;
	CDagger* dagger;
	CAxe* Axe;
	TileMap* Tile;
	CBrick* brick;
	CTorch* torch;
	TileMap* tile;
	InviObjects* InOb;
	Grid* grid;
	CAnimations* animations;
	CSprites* sprites;
	LPANIMATION ani;
	vector<LPGAMEOBJECT> mapobjects;
	vector<LPGAMEOBJECT> stairs;
	vector<LPGAMEOBJECT> stagechanger;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> ObjectsFromGrid;

	bool castle = false;
	bool SimonMove = false;
	int scene;
	int stage;
	float cx, cy;

};

