#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include "define.h"
#include "Sprites.h"
#include "Textures.h"
class TileMap
{
private:
	int id;
	int number;
	queue<int>entr;
public:
	CGame* game = CGame::GetInstance();
	CTextures* textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	TileMap(LPCWSTR picturePath, int _id);
	void LoadTile(const char* filepath);
	void DrawTile();
	~TileMap();
};

