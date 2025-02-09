#include "LoadResourceHelper.h"
#include<fstream>
#include"../sample/textures.h"
#include <string>
using namespace std;
LoadResourceHelper::LoadResourceHelper()
{
}

void LoadResourceHelper::Loadspritefromfile(string arrsource, int texnumber)
{
	int idsprite, left, top, right, bottom;
	//string arrsource[] = { "characters\\player\\player_sprites.txt" };
	ifstream infile;
	CSprites * sprites = CSprites::GetInstance();
	CTextures * textures = CTextures::GetInstance();

	LPDIRECT3DTEXTURE9 tex = textures->Get(texnumber);
		infile.open(arrsource);
		if (!infile)
			return;
		while (!infile.eof())
		{
			infile >> idsprite >> left >> top >> right >> bottom;
			sprites->Add(idsprite, left, top, right, bottom, tex);
		}
}

void LoadResourceHelper::Loadanimationfromfile(string arrsource[],int numofsource,CGameObject *object)
{
	
	int idani, time, idsprite;
	string all;
	ifstream infile;
	CSprites * sprites = CSprites::GetInstance();
	CAnimations *anis =CAnimations::GetInstance();
	LPANIMATION ani;
	for (int i = 0; i < numofsource; i++)
	{
		idani = 0;
		infile.open(arrsource[i]);
		while (!infile.eof())
		{

			infile >> idani;
			ani = new CAnimation(100);
			while (!infile.eof())
			{
				infile >> idsprite >> time;
				ani->Add(idsprite, time);
			}
			anis->Add(idani,ani);

			object->AddAnimation(idani);
			
		}
		//infile.clear();
		infile.close();
	}
}

void LoadResourceHelper::loadtileset()
{
}
//copy ,i don't know
wstring s2ws(string s) {

	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
};

void LoadResourceHelper::loadtextures(string path)
{
	//string sourcepath = "content\\textures\\";
	CTextures * textures = CTextures::GetInstance();
	const string texture_name_collection[] = { "ID_TEX_MARIO","ID_TEX_ENEMY","ID_TEX_MISC","ID_TEX_SIMON","ID_TEX_WHIP","ID_TEX_MAP1","ID_TEX_BBOX","ID_TEX_BRATIZER","ID_TEX_LARGE_HEART","ID_TEX_WHIP_POWER_UP","ID_TEX_SWORD" };
	const int texture_collection[] = { ID_TEX_MARIO,ID_TEX_ENEMY,ID_TEX_MISC,ID_TEX_SIMON,ID_TEX_WHIP,ID_TEX_MAP1,ID_TEX_BBOX,ID_TEX_BRATIZER,ID_TEX_LARGE_HEART,ID_TEX_WHIP_POWER_UP,ID_TEX_SWORD };
	string idtex;
	string pathimage;
	int trans_r;
	int trans_g;
	int trans_b;
	
	ifstream infile;
	infile.open(path);
	if (!infile)
		return;
	while (!infile.eof())
	{
		infile >> idtex >> pathimage >> trans_r >> trans_g >> trans_b;
		for (unsigned int i = 0; i <= texture_name_collection->size(); i++)
		{
			if (idtex == texture_name_collection[i])
			{
				wstring stemp = s2ws(pathimage);
				LPCWSTR image = stemp.c_str();
				textures->Add(texture_collection[i],image, D3DCOLOR_XRGB(trans_r, trans_g, trans_b));
			}
		}
		
	}
	infile.close();
}

LoadResourceHelper ::~LoadResourceHelper()
{
}
