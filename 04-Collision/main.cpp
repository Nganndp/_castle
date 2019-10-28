/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions:
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox

================================================================ */

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
CGame * game;

CSimon* SIMON;
CMS* MS;
CDagger* dagger;
CAxe* Axe;
vector<LPGAMEOBJECT> objects;

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander* keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (SIMON->GetState() == SIMON_STATE_DIE || SIMON->GetChangeColorTime() != 0) return;
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (SIMON->GetOnGround())
		{
			SIMON->SetState(SIMON_STATE_JUMP);
			SIMON->StartJump();
		}
		break;
	case DIK_A:
		if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT))
		{
			return;
		}
		if (game->IsKeyDown(DIK_UP))
		{
			if (SIMON->GetThrowDagger())
			{
				if (SIMON->GetAttackTime() == 0)
				{
					dagger->StartAttack();
					dagger->SetActive(true);
				}
				dagger->nx = SIMON->nx;
				MS->SetActive(false);
				SIMON->SetState(SIMON_STATE_ATTACK);
				SIMON->StartAttack();
			}
			else if (SIMON->GetThrowAxe())
			{
				if (SIMON->GetAttackTime() == 0)
				{
					Axe->StartAttack();
					Axe->SetActive(true);
				}
				Axe->nx = SIMON->nx;
				MS->SetActive(false);
				SIMON->SetState(SIMON_STATE_ATTACK);
				SIMON->StartAttack();
				
			}
		}
		if (!game->IsKeyDown(DIK_UP))
		{
			MS->StartAttack();
			MS->SetState(MS_STATE_ATTACK);
			MS->SetActive(true);
			SIMON->SetState(SIMON_STATE_ATTACK);
			SIMON->StartAttack();
			SIMON->SetJump(0);
			if (SIMON->GetLevel() == SIMON_LEVEL_MS_2)
			{
				MS->SetState(MS_STATE_ATTACK_2);
			}
        }
		break;
	case DIK_Q:
		if (SIMON->GetActive() == true)
		{
			SIMON->SetActive(false);
		}
		else SIMON->SetActive(true);
		break;
	case DIK_R: 
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Setbboxcolor();
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	if (KeyCode == 208) {
		SIMON->StandUp();
	}
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE* states)
{
	// disable control key when SIMON die 
	if (SIMON->GetState() == SIMON_STATE_DIE || SIMON->GetChangeColorTime() != 0) return;
	if (game->IsKeyDown(DIK_RIGHT) && !game->IsKeyDown(DIK_DOWN))
	{
		SIMON->SetState(SIMON_STATE_WALKING_RIGHT);
		SIMON->SetRight(1);
	}
	else if (game->IsKeyDown(DIK_LEFT) && !game->IsKeyDown(DIK_DOWN))
	{
		SIMON->SetState(SIMON_STATE_WALKING_LEFT);
		SIMON->SetRight(0);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		SIMON->SetState(SIMON_STATE_SIT);
		SIMON->SetSit(true);
	}
	else
		SIMON->SetState(SIMON_STATE_IDLE);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and SIMON object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{

	//Textures
	CTextures* textures = CTextures::GetInstance();
	textures->Load();

	//Sprites
	CSprites* sprites = CSprites::GetInstance();
	sprites->Load();
	CAnimations* animations = CAnimations::GetInstance();

 
   //Animations
	LPANIMATION ani;
	//simon
	ani = new CAnimation(100);	// idle right
	ani->Add(10001);
	animations->Add(400, ani);
	ani = new CAnimation(100);	// idle left
	ani->Add(10011);
	animations->Add(401, ani);

	ani = new CAnimation(100);	// walk right
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);
    ani = new CAnimation(100);	//  walk left
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	ani = new CAnimation(100);	// attack right
	ani->Add(10004);
	ani->Add(10005);
	ani->Add(10006);
	animations->Add(402, ani);
	ani = new CAnimation(100);	// attack left
	ani->Add(10014);
	ani->Add(10015);
	ani->Add(10016);
	animations->Add(502, ani);

	ani = new CAnimation(100);	// jump right
	ani->Add(10007);
	animations->Add(403, ani);
	ani = new CAnimation(100);	// jump right
	ani->Add(10017);
	animations->Add(503, ani);

	ani = new CAnimation(100);	// sit right
	ani->Add(10008);
	animations->Add(404, ani);
	ani = new CAnimation(100);	// sit right
	ani->Add(10018);
	animations->Add(504, ani);

	ani = new CAnimation(100);	// eat item right
	ani->Add(30001);
	ani->Add(30002);
	ani->Add(30003);
	ani->Add(30004);
	animations->Add(405, ani);
	ani = new CAnimation(100);	// eat item right
	ani->Add(30011);
	ani->Add(30012);
	ani->Add(30013);
	ani->Add(30014);
	animations->Add(505, ani);
	
	//weapon
	ani = new CAnimation(100);		//mornig star
	ani->Add(20001);
	ani->Add(20002);
	ani->Add(20003);
	animations->Add(600, ani);
	ani = new CAnimation(100);       //left morning starr
	ani->Add(20011);
	ani->Add(20012);
	ani->Add(20013);
	animations->Add(601, ani);
	ani = new CAnimation(100);		//mornig star #2
	ani->Add(20101);
	ani->Add(20102);
	ani->Add(20103);
	animations->Add(602, ani);
	ani = new CAnimation(100);       //left morning star #2
	ani->Add(20111);
	ani->Add(20112);
	ani->Add(20113);
	animations->Add(603, ani);
  
	ani = new CAnimation(100);		// dagger right
	ani->Add(99999);
	animations->Add(610, ani);
	ani = new CAnimation(100);		// dagger left
	ani->Add(99998);
	animations->Add(611, ani);

	ani = new CAnimation(100);		// Axe
	ani->Add(11000);
	ani->Add(11001);
	ani->Add(11002);
	ani->Add(11003);
	animations->Add(615, ani);

    //item
	ani = new CAnimation(100);		// Lheart
	ani->Add(99997);
	animations->Add(612, ani);
	ani = new CAnimation(100);		// Sheart
	ani->Add(99996);
	animations->Add(613, ani);
	ani = new CAnimation(100);		// MS Up
	ani->Add(99995);
	animations->Add(614, ani);
	ani = new CAnimation(100);      // Axe
	ani->Add(11000);
	animations->Add(616, ani);

    //map
	ani = new CAnimation(100);		// brick
	ani->Add(90001);
	animations->Add(1000, ani);

	ani = new CAnimation(100);		// torch
	ani->Add(90002);
	ani->Add(90003);
	animations->Add(1001, ani);

	//declare simon-animations
	SIMON = new CSimon();

	SIMON->AddAnimation(400);		// idle right 
	SIMON->AddAnimation(401);		// idle left 
    SIMON->AddAnimation(500);		// walk right 
	SIMON->AddAnimation(501);		// walk left 
	SIMON->AddAnimation(402);       //attack right
	SIMON->AddAnimation(502);       //attack left
	SIMON->AddAnimation(403);       //jump right
	SIMON->AddAnimation(503);       //jump left
	SIMON->AddAnimation(404);       //sit right
	SIMON->AddAnimation(504);       //sit left
	SIMON->AddAnimation(405);       //eat item right
	SIMON->AddAnimation(505);       //eat item left

    SIMON->SetPosition(25.0f, 0);

	//declare weapon-animations
	MS = new CMS();
	MS->GetSimon(SIMON);
	MS->SetPosition(-100, -100);
	MS->AddAnimation(600);
	MS->AddAnimation(601);
	MS->AddAnimation(602);
	MS->AddAnimation(603);
	
	dagger = new CDagger();
    dagger->GetSimon(SIMON);
	dagger->AddAnimation(610);
	dagger->AddAnimation(611);

	Axe = new CAxe();
	Axe->GetSimon(SIMON);
	Axe->AddAnimation(615);
	
	//draw map-animations
	for (int i = 0; i < 5; i++)
	{
		CTorch* torch = new CTorch();
		torch->AddAnimation(1001);
		torch->AddAnimation(612);
		torch->AddAnimation(613);
		torch->AddAnimation(614);
		torch->AddAnimation(611);
		torch->AddAnimation(616);
		torch->SetPosition(100 + i * 120.0f, 113);
	    objects.push_back(torch);
	}
	for (int i = 0; i < 100; i++)
	{
		CBrick* brick = new CBrick();
		brick->AddAnimation(1000);
		brick->SetPosition(0 + i * 8.0f, 144);
		objects.push_back(brick);

	}

	//push back to list objects
	objects.push_back(SIMON);
	objects.push_back(MS);
	objects.push_back(dagger);
	objects.push_back(Axe);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that SIMON is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> Torch;
	for (int i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	// Update camera to follow SIMON
	float cx, cy;

	SIMON->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;
	if (cx < 900/ 2 && cx>0)
	{
		CGame::GetInstance()->SetCamPos(cx, 0.0f);///cy
	}
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		CSprites* sprites = CSprites::GetInstance();
		int x=0, y=0;
		int flag = 1;

		//draw map
		int i, j;
		ifstream file_entrance("entrance_test.txt");
		int number;
		queue<int>entr;
		if (file_entrance.is_open())
		{
			while (!file_entrance.eof())
			{
				file_entrance >> number;
				entr.push(number);
			}
		}
		for (i = 0; i < 3*64; i=i+64)
		{
			for (j = 0; j < 12*64; j=j+64)
				{
					sprites->Get(entr.front())->Draw(j, i, 255);
					entr.pop();
				}
		}
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();
		
		spriteHandler->End();
		

		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}