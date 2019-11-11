#include "TileMap.h"
TileMap::TileMap(LPCWSTR picturePath, int id)
{
	this->id = id;
	textures->Add(id, picturePath, D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DTEXTURE9 tex = textures->Get(this->id);
	if (id == ID_TEX_ENTRANCESTAGE)
	{
		int t = 0;
		int k = 0;
		for (int j = 0; j < 4; j++)
		{
			int l = 0, r = 16;
			for (int i = t; i <= t + 15; i++)
			{
				sprites->Add(i, l, k, r, k + 16, tex);
				l += 16;
				r += 16;
			}
			t += 16;
			k += 16;
		}
	}
	else if (id == ID_TEX_CASTLE)
	{
		int t = 0;
		int k = 0;
		for (int j = 0; j < 7; j++)
		{
			int l = 0, r = 16;
			for (int i = t; i <= t + 15; i++)
			{
				sprites->Add(i, l, k, r, k + 16, tex);
				l += 16;
				r += 16;
			}
			t += 16;
			k += 16;
		}
	}
}
TileMap::~TileMap()
{
}
void TileMap::LoadTile(const char* filepath)
{
	ifstream file_entrance(filepath);
	if (file_entrance.is_open())
	{
		while (!file_entrance.eof())
		{
			file_entrance >> number;
			entr.push(number);
		}
	}
}
void TileMap::DrawTile()
{
	int i, j, t, k;
	if (id == ID_TEX_ENTRANCESTAGE)
	{
		t = 10;
		k = 48;
		for (i = 0; i < t * 16; i = i + 16)

			for (j = 0; j < k * 16; j = j + 16)
			{
				sprites->Get(entr.front())->Draw(j, i, 255);
				entr.pop();
			}
	}
	else if (id == ID_TEX_CASTLE)
	{
		t = 11;
		k = 176;
		for (i = 0; i < t * 16; i = i + 16)

			for (j = 0; j < k * 16; j = j + 16)
			{
				sprites->Get(entr.front())->Draw(j, i, 255);
				entr.pop();
			}
	}

}