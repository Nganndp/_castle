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
vector<LPGAMEOBJECT> mapobjects;
vector<LPGAMEOBJECT> objects;

void LoadObjectFromFile(string source, int a)
{
	vector<int> numbers;
	int flag = 0;
	int number;
	int arr[3];
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
				if (flag == 3)
				{
					switch (arr[0])
					{
					case 0:
						for (int i = 0; i < a; i++)
						{
							tmp = new CBrick();
							tmp->SetPosition(0 + i * 8.0f, 143);
							mapobjects.push_back(tmp);

						}
					case 1:
						tmp = new CTorch();
						tmp->SetPosition(arr[1], arr[2]);
						mapobjects.push_back(tmp);
						break;
					case 2:
						tmp = new CBrick();
						tmp->SetPosition(arr[1], arr[2]);
						mapobjects.push_back(tmp);
						break;
					}

					flag = 0;
				}
			}
		}
	}
}

void DrawObject(int a)
{
	if (a == 1)
	{
		LoadObjectFromFile("Objects\\ObjectsStage1.txt", 95);
	}
}
