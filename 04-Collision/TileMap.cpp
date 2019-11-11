#include "TileMap.h"
TileMap::TileMap(LPCWSTR picturePath, int id)
{
	this->id = id;
	textures->Add(id, picturePath, D3DCOLOR_XRGB(0, 0, 0));
	LPDIRECT3DTEXTURE9 tex = textures->Get(this->id);
	if (id == ID_TEX_ENTRANCESTAGE)
	{
		int l = 0, r = 16;
		for (int i = 0; i <= 15; i++)
		{
			sprites->Add(i, l, 0, r, 16, tex);
			l += 16;
			r += 16;
		}
		l = 0, r = 16;
		for (int i = 16; i <= 31; i++)
		{
			sprites->Add(i, l, 16, r, 32, tex);
			l += 16;
			r += 16;
		}
		l = 0, r = 16;
		for (int i = 32; i <= 47; i++)
		{
			sprites->Add(i, l, 32, r, 48, tex);
			l += 16;
			r += 16;
		}
		l = 0, r = 16;
		for (int i = 48; i <= 63; i++)
		{
			sprites->Add(i, l, 48, r, 64, tex);
			l += 16;
			r += 16;
		}
		//for (int i = 64; i <= 100; i++)
		//{
		//	sprites->Add(i, 0, 0, 0, 0, tex);
		//}
	}
	else if (id == ID_TEX_CASTLE)
	{
		int l = 0, r = 16;
		for (int i = 0; i <= 15; i++)
		{
			sprites->Add(i, l, 0, r, 16, tex);
			l += 16;
			r += 16;
		}
		l = 0, r = 16;
		for (int i = 16; i <= 31; i++)
		{
			sprites->Add(i, l, 16, r, 32, tex);
			l += 16;
			r += 16;
		}
		l = 0, r = 16;
		for (int i = 32; i <= 47; i++)
		{
			sprites->Add(i, l, 32, r, 48, tex);
			l += 16;
			r += 16;
		}
		l = 0, r = 16;
		for (int i = 48; i <= 63; i++)
		{
			sprites->Add(i, l, 48, r, 64, tex);
			l += 16;
			r += 16;
		}
		l = 0, r = 16;
		for (int i = 64; i <= 79; i++)
		{
			sprites->Add(i, l, 64, r, 80, tex);
			l += 16;
			r += 16;
		}
		l = 0, r = 16;
		for (int i = 80; i <= 95; i++)
		{
			sprites->Add(i, l, 80, r, 96, tex);
			l += 16;
			r += 16;
		}
		l = 0, r = 16;
		for (int i = 96; i <= 100; i++)
		{
			sprites->Add(i, l, 96, r, 112, tex);
			l += 16;
			r += 16;
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
	if (id == ID_TEX_ENTRANCESTAGE)
	{
		for (i = 0; i < 10 * 16; i = i + 16)

			for (j = 0; j < 48 * 16; j = j + 16)
			{
				sprites->Get(entr.front())->Draw(j, i, 255);
				entr.pop();
			}
	}
	if (id == ID_TEX_CASTLE)
	{
		for (i = 0; i < 11 * 16; i = i + 16)

			for (j = 0; j < 176 * 16; j = j + 16)
			{
				sprites->Get(entr.front())->Draw(j, i, 255);
				entr.pop();
			}
	}
}