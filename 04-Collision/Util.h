#pragma once
#include <windows.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include <cstdlib>
#include <ctime>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "TileMap.h"

#include "SIMON.h"
#include "MS.h"
#include "Torch.h"
#include "Brick.h"
#include "Dagger.h"
#include "Axe.h"

#include<iostream>
#include<fstream>
#include<string>
#include<queue>
#include "define.h"
CGame* game;

CSimon* SIMON;
CMS* MS;
CDagger* dagger;
CAxe* Axe;
TileMap* Tile;
CBrick* brick;
CTorch* torch;
vector<LPGAMEOBJECT> mapobjects;
vector<LPGAMEOBJECT> objects;
bool castle = false;
int scene = 1;
float cx, cy;

void LoadSimon()
{
	
}
void LoadObjectFromFile(string source)
{
	vector<int> numbers;
	int flag = 0;
	int number;
	int arr[4];
	ifstream file_objects(source);
	if (file_objects.is_open())
	{
		while (!file_objects.eof())
		{
			while (file_objects >> number)
			{
				CGameObject* tmp = nullptr;
				arr[flag] = number;
				flag++;
				if (flag == 4)
				{
					switch (arr[0])
					{
					case 0:
						brick = new CBrick();
						brick->SetType(BRICK_TYPE_GROUND);
						brick->SetMulwidth(arr[3]);
						brick->SetPosition(arr[1], arr[2]);
						mapobjects.push_back(brick);
						break;
					case 1:
						torch = new CTorch();
						torch->SetPosition(arr[1], arr[2]);
						mapobjects.push_back(torch);
						break;
					case 2:
						brick = new CBrick();
						brick->SetType(BRICK_TYPE_NORMAL);
						brick->SetMulwidth(arr[3]);
						brick->SetPosition(arr[1], arr[2]);
						mapobjects.push_back(brick);
						break;
					}

					flag = 0;
				}
			}
		}
	}
}

void LoadSceneObject(int a)
{
	if (a == 1)
	{
		LoadObjectFromFile("Objects\\ObjectsStage1.txt");
	}
	if (a == 2)
	{
		LoadObjectFromFile("Objects\\ObjectsStage2.txt");
	}
}
