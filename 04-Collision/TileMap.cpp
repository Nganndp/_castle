#include "TileMap.h"
TileMap::TileMap(LPCWSTR picturePath, int id, int translate_y, int translate_x)
{
	this->id = id;
    this->translate_y = translate_y;
	this->translate_x = translate_x;

	textures->Add(id, picturePath, D3DCOLOR_XRGB(255, 255, 255));
	LPDIRECT3DTEXTURE9 tex = textures->Get(this->id);
	//if (id == ID_TEX_ENTRANCESTAGE)
	//{
	//	int t = 0;
	//	int k = 0;
	//	for (int j = 0; j < 4; j++)
	//	{
	//		int l = 0, r = 16;
	//		for (int i = t; i <= t + 15; i++)
	//		{
	//			sprites->Add(i, l, k, r, k + 16, tex);
	//			l += 16;
	//			r += 16;
	//		}
	//		t += 16;
	//		k += 16;
	//	}
	//}
	//else if (id == ID_TEX_CASTLE)
	//{
	//	int t = 0;
	//	int k = 0;
	//	for (int j = 0; j < 7; j++)
	//	{
	//		int l = 0, r = 16;
	//		for (int i = t; i <= t + 15; i++)
	//		{
	//			sprites->Add(i, l, k, r, k + 16, tex);
	//			l += 16;
	//			r += 16;
	//		}
	//		t += 16;
	//		k += 16;
	//	}
	//}
}

void TileMap::LoadMap(const char* filepath)
{
	FILE* pFile;
	pFile = fopen(filepath, "r");

	fscanf(pFile, "%d %d %d %d", &rowTileset, &colTileset, &width, &height);

	for (int i = 0; i < rowTileset; i++)
	{
		for (int j = 0; j < colTileset; j++)
		{
			fscanf(pFile, "%d", &listTile[i][j]);

		}
	}
	fclose(pFile);
}
void TileMap::DrawMap(Camera*camera)
{
	remain_y = fmod(camera->GetPosition().y, height);
	remain_x = fmod(camera->GetPosition().x, width); 


	int colCamLeft = camera->GetPosition().x / width;
	int colCamRight = colCamLeft + SCREEN_WIDTH / width;
	int rowCamTop = camera->GetPosition().y / height;
	int rowCamBottom = rowCamTop + SCREEN_HEIGHT / height;


	for (int j = colCamLeft; j <= colCamRight; j++) 
	{
		for (int i = rowCamTop; i < rowCamBottom; i++)
		{
			float pos_x = (j - colCamLeft) * width - remain_x + translate_x;
			float pos_y = (i - rowCamTop) * height - remain_y + translate_y;

			RECT rectTile;
			int index = listTile[i][j];

			rectTile.left = (index % colTileset) * width;
			rectTile.top = (index / colTileset) * height;
			rectTile.right = rectTile.left + width;
			rectTile.bottom = rectTile.top + height;

			//sprites->Get(index)->Draw(pos_x, pos_y, 255);
			game->Draw(pos_x, pos_y, textures->Get(id), rectTile.left, rectTile.top, rectTile.right, rectTile.bottom, 255);
		}
	}

}
TileMap::~TileMap()
{
}