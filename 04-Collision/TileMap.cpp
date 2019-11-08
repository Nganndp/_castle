#include "TileMap.h"
TileMap::TileMap(LPCWSTR picturePath, int id)
{
	this->id = id;
	textures->Add(id, picturePath, D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DTEXTURE9 tex = textures->Get(this->id);
	if (id == ID_TEX_ENTRANCESTAGE)
	{
		int l = 0, r = 64;
		for (int i = 0; i <= 11; i++)
		{
			sprites->Add(i, l, 0, r, 64, tex);
			l += 64;
			r += 64;
		}
		l = 0, r = 64;
		for (int i = 12; i <= 23; i++)
		{
			sprites->Add(i, l, 64, r, 128, tex);
			l += 64;
			r += 64;
		}
		l = 0, r = 64;
		for (int i = 24; i <= 35; i++)
		{
			sprites->Add(i, l, 128, r, 192, tex);
			l += 64;
			r += 64;
		}
	}
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
	int i, j;
	for (i = 0; i < 3 * 64; i = i + 64)
	{
		for (j = 0; j < 12 * 64; j = j + 64)
		{
			sprites->Get(entr.front())->Draw(j, i, 255);
			entr.pop();
		}
	}
}