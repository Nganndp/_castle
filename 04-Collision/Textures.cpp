#include "Textures.h"

CTextures * CTextures::__instance = NULL;

CTextures::CTextures()
{

}

CTextures *CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}

void CTextures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,			
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	textures[id] = texture;

	DebugOut(L"[INFO] Texture loaded Ok: id=%d, %s \n", id, filePath);
}

LPDIRECT3DTEXTURE9 CTextures::Get(unsigned int i) 
{
	return textures[i];
}
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
void CTextures::Load()
{
	CTextures* textures = CTextures::GetInstance();
	const string texture_name_collection[] = { "ID_TEX_SIMON","ID_TEX_DAGGERR","ID_TEX_DAGGERL","ID_TEX_LHEART","ID_TEX_SHEART","ID_TEX_MSUP","ID_TEX_AXE","ID_TEX_TORCH","ID_TEX_MISC","ID_TEX_ENTRANCESTAGE","ID_TEX_BBOX" };
	const int texture_collection[] = { ID_TEX_SIMON,ID_TEX_DAGGERR,ID_TEX_DAGGERL,ID_TEX_LHEART,ID_TEX_SHEART,ID_TEX_MSUP,ID_TEX_AXE,ID_TEX_TORCH,ID_TEX_MISC,ID_TEX_ENTRANCESTAGE,ID_TEX_BBOX };
	string idtex;
	string pathimage;
	int trans_r;
	int trans_g;
	int trans_b;

	ifstream infile;
	infile.open("textures.txt");
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
				textures->Add(texture_collection[i], image, D3DCOLOR_XRGB(trans_r, trans_g, trans_b));
			}
		}

	}
	infile.close();
}



