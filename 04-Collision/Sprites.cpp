#include "Sprites.h"


CSprite::CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha = 255)
{
	CGame * game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, alpha);
}

void CSprites::Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}
void CSprites::Load()
{
	CSprites* sprites = CSprites::GetInstance();
	CTextures* textures = CTextures::GetInstance();
	vector<int> numbers;
	int flag = 0;
	int number;
	int arr[6];
	ifstream file_Simon("ReadFile\\sprite.txt");
	if (file_Simon.is_open())
	{
		while (!file_Simon.eof())
		{
			while (file_Simon >> number)
			{
				arr[flag] = number;
				flag++;
				if (flag == 6)
				{
					LPDIRECT3DTEXTURE9 tex = textures->Get(arr[0]);
					sprites->Add(arr[1], arr[2], arr[3], arr[4], arr[5], tex);
					flag = 0;
				}
			}
		}
	}
}
void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t=this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}
void CAnimation::Render(D3DXVECTOR2 pos, int alpha)
{
	Render(pos.x, pos.y, alpha);
}
void CAnimation::Render(float x, float y, int alpha)
{
	//alpha = 255;
	DWORD now = GetTickCount();
	if (currentFrame == -1) 
	{
		currentFrame = 0; 
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
		
	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}