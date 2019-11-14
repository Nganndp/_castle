#pragma once
#include "Scene.h"
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
#include "StageChanger.h"
#include "Stair.h"

#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include "define.h"
class SceneManager : public Scene
{
public:
	SceneManager();
	void KeyState(BYTE* state);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);

	void LoadResources();
	void Update(DWORD dt);
	void Render();
	void LoadObjectFromFile(string source);
	void LoadSceneObject(int a);
	void ChangeScene();

	~SceneManager();
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
	StageChanger* SC;
	Stair* stair;
	CAnimations* animations;
	CSprites* sprites;
	LPANIMATION ani;
	vector<LPGAMEOBJECT> mapobjects;
	vector<LPGAMEOBJECT> stairs;
	vector<LPGAMEOBJECT> stagechanger;
	vector<LPGAMEOBJECT> objects;

	bool castle = false;
	int scene;
	float cx, cy;

};

