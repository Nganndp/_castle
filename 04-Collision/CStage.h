#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <algorithm>
#include "debug.h"
#include "Game.h"

using namespace std;
class CStage;
typedef CStage* STAGE;
class CStage
{
public:
	int numofvariable;
	int stagename;
	int startpoint;
	int endpoint;
	int simonposx;
	int simonposy;
	int simonrespawnx;
	int simonrespawny;
	int numoftemp;
	int *temp = new int[10];
	int tempo;
	int tempo2;
	void SetSimonPos(int a, int b)
	{
		tempo = this->simonposx;
		this->simonposx = this->temp[a];
		this->temp[a] = tempo;
		tempo2 = this->simonposy;
		this->simonposy = this->temp[b];
		this->temp[b] = tempo2;
    }
	void AddVariable(int stagename, int startpoint, int endpoint, int simonposx, int simonposy, int simonrespawnx, int simonrespawny)
	{
		this->stagename = stagename;
		this->startpoint = startpoint;
		this->endpoint = endpoint;
		this->simonposx = simonposx;
		this->simonposy = simonposy;
		this->simonrespawnx = simonrespawnx;
		this->simonrespawny = simonrespawny;
	}
	void AddTemp(int temp, int i)
	{
		this->temp[i] = temp;
	}
};

