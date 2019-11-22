#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include "define.h"
#include "Sprites.h"
#include "Textures.h"
#include "Camera.h"
class TileMap
{
public:
	TileMap(LPCWSTR picturePath, int _id, int _translate, int _translate_x);

	CGame *game = CGame::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	CSprites* sprites = CSprites::GetInstance();

	void LoadMap(const char* filepath);
	void DrawMap(Camera* camera);

	~TileMap();

private:
	int listTile[200][200];
	int id;
	int width, height;
	int colTileset, rowTileset;
	float remain_x, remain_y;
	int translate_y, translate_x;
};

